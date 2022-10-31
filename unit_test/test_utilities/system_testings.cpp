#include <thread>
#include <chrono>
#include <iostream>

#include "system_testings.h"

#include "Utilities/exceptions.h"
#include "test_utilities.h"

#include "../../dev/Model/model_main.h"
#include "../../dev/Controller/controller_main.h"

#include "../../Network/network_main.h"
#ifdef _WIN32
#include <Windows.h>
#include "../../Network/system_interfaces/windows_network_interface.h"
#endif // _WIN32
#ifdef __linux__
#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include <linux/uhid.h>
#include <sstream>
#include "../../Network/system_interfaces/linux_network_interface.h"

int fd = 0;
#endif

Message_Consumer* message_consumer = 0;
bool stale;

bool system_utilities::CI = false;
#ifdef _WIN32
bool system_utilities::LINUX = false;
bool system_utilities::WINDOWS = true;
#endif
#ifdef __linux__
bool system_utilities::LINUX = true;
bool system_utilities::WINDOWS = false;
#endif

void system_utilities::setup()
{
	try
	{
		model::initalize();
		controller::initalize();
	}
	catch(NetworkErrorException)
	{
		printf("Caught network exception");
		testing_utilities::network_utilities::exception_handle();
	}
	setup_messaging();
}

void system_utilities::setup_messaging()
{
	if(message_consumer == 0)
	{
		message_consumer = new Message_Consumer(new Logging_Message());
		Message_Relay::get_instance()->register_consumer(message_consumer);
	}
}

void system_utilities::teardown_messaging()
{
	print_log_messages();
	Message_Relay::get_instance()->deregister_consumer(message_consumer);
	message_consumer = 0;
}

void system_utilities::print_log_messages()
{
	for(Logging_Message* mess = dynamic_cast<Logging_Message*>(Message_Relay::get_instance()->pop(message_consumer)); mess != 0; mess = dynamic_cast<Logging_Message*>(Message_Relay::get_instance()->pop(message_consumer)))
	{
		int level = (int) MESSAGE_PRIORITY::INFO_MESSAGE;
	#ifdef DEBUG
		level = (int) MESSAGE_PRIORITY::DEBUG_MESSAGE;
	#endif // DEBUG

		if((int) mess->get_priority() < level)
		{
			continue;
		}
		std::string priority_string;
		if(mess->get_priority() == MESSAGE_PRIORITY::ERROR_MESSAGE)
		{
			std::cout << "[  \u001b[33m" + mess->get_priority_string() + "\u001b[0m   ]";
		}
		else if(mess->get_priority() == MESSAGE_PRIORITY::INFO_MESSAGE)
		{
			std::cout << "[  " + mess->get_priority_string() + "    ]";
		}
		else
		{
			std::cout << "[  " << mess->get_priority_string() << "   ]";
		}
		std::cout << " (" << mess->get_location() << ")  " << mess->get_message() << std::endl << std::flush;
	}
}

void system_utilities::cleanup()
{
	controller::clean_up();
	model::clean_up();
	teardown_messaging();
}

void system_utilities::step(int steps)
{
	for(int i = 0; i < steps; i++)
	{
		controller::step();
		model::step();
	}
}

void system_utilities::sleep_thread(int time_to_sleep)
{
	std::this_thread::sleep_for(std::chrono::seconds(time_to_sleep));
}

void system_utilities::model_utilities::start()
{
	model::start_loop();
}

void system_utilities::model_utilities::stop()
{
	model::stop_loop();
}

void system_utilities::network_utilities::setup()
{
	try
	{
		system_utilities::setup();
		std::string i;
		if(std::getenv("CI") != NULL)
		{
			LOG_INFO("On a CI machine", "Test Setup");
		#ifdef __linux__
			network::init_network_interfaces("nat");
		#endif // __linux
		#ifdef _WIN32
			network::init_network_interfaces("vEthernet (nat)");
		#endif
		}
		else
		{
			LOG_INFO("Not on a CI machine", "Test Setup");
			network::init_network_interfaces();
		}
	}
	catch(NetworkErrorException e)
	{
		testing_utilities::network_utilities::exception_handle();
	}
}

#ifdef __linux__
void enable_keys(int fd)
{
	ioctl(fd, UI_SET_EVBIT, EV_KEY);
	ioctl(fd, UI_SET_KEYBIT, KEY_A);
}
#endif

void system_utilities::keyboard_utilities::setup()
{
	system_utilities::setup();
#ifdef __linux__
	struct uinput_setup usetup;
	if((fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK)) > 0)
	{
		enable_keys(fd);
		memset(&usetup, 0, sizeof(usetup));
		usetup.id.bustype = BUS_USB;
		usetup.id.vendor = 0x03f0; /* sample vendor */
		usetup.id.product = 0x050c; /* sample product */
		strcpy(usetup.name, "5219 Wireless Keyboard");

		ioctl(fd, UI_DEV_SETUP, &usetup);
		ioctl(fd, UI_DEV_CREATE);
		sleep(1);
		testing_utilities::input_utilities::connect_keyboard("/dev/input/event0");
		return;
	}
	else
	{
		int why_i_failed = errno;
		if(why_i_failed == EACCES)
		{
			LOG_ERROR("Permission Denied", "Connect UInput");
		}
		else
			LOG_INFO("Direct connect failed cause of : " + std::to_string(why_i_failed), "Connect Keyboard");
	}
#endif
}

void system_utilities::keyboard_utilities::tear_down()
{
	system_utilities::cleanup();
#ifdef __linux__
	ioctl(fd, UI_DEV_DESTROY);
	close(fd);
#endif
}

#ifdef _WIN32
void system_utilities::keyboard_utilities::press_button(int key)
{
	// This structure will be used to create the keyboard
// input event.
	INPUT ip;
	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press the "A" key
	ip.ki.wVk = key; 
	ip.ki.dwFlags = 0;
//	SendInput(1, &ip, sizeof(INPUT));
	std::this_thread::sleep_for(std::chrono::milliseconds(40));

	ip.ki.dwFlags = KEYEVENTF_KEYUP;
//	SendInput(1, &ip, sizeof(INPUT));
}
#endif

#ifdef __linux__

#define EV_PRESSED 1
#define EV_RELEASED 0
#define EV_REPEAT 2

static unsigned char rdesc [] = {
	0x05, 0x01,	/* USAGE_PAGE (Generic Desktop) */
	0x09, 0x02,	/* USAGE (Mouse) */
	0xa1, 0x01,	/* COLLECTION (Application) */
	0x09, 0x01,		/* USAGE (Pointer) */
	0xa1, 0x00,		/* COLLECTION (Physical) */
	0x85, 0x01,			/* REPORT_ID (1) */
	0x05, 0x09,			/* USAGE_PAGE (Button) */
	0x19, 0x01,			/* USAGE_MINIMUM (Button 1) */
	0x29, 0x03,			/* USAGE_MAXIMUM (Button 3) */
	0x15, 0x00,			/* LOGICAL_MINIMUM (0) */
	0x25, 0x01,			/* LOGICAL_MAXIMUM (1) */
	0x95, 0x03,			/* REPORT_COUNT (3) */
	0x75, 0x01,			/* REPORT_SIZE (1) */
	0x81, 0x02,			/* INPUT (Data,Var,Abs) */
	0x95, 0x01,			/* REPORT_COUNT (1) */
	0x75, 0x05,			/* REPORT_SIZE (5) */
	0x81, 0x01,			/* INPUT (Cnst,Var,Abs) */
	0x05, 0x01,			/* USAGE_PAGE (Generic Desktop) */
	0x09, 0x30,			/* USAGE (X) */
	0x09, 0x31,			/* USAGE (Y) */
	0x09, 0x38,			/* USAGE (WHEEL) */
	0x15, 0x81,			/* LOGICAL_MINIMUM (-127) */
	0x25, 0x7f,			/* LOGICAL_MAXIMUM (127) */
	0x75, 0x08,			/* REPORT_SIZE (8) */
	0x95, 0x03,			/* REPORT_COUNT (3) */
	0x81, 0x06,			/* INPUT (Data,Var,Rel) */
	0xc0,			/* END_COLLECTION */
	0xc0,		/* END_COLLECTION */
	0x05, 0x01,	/* USAGE_PAGE (Generic Desktop) */
	0x09, 0x06,	/* USAGE (Keyboard) */
	0xa1, 0x01,	/* COLLECTION (Application) */
	0x85, 0x02,		/* REPORT_ID (2) */
	0x05, 0x08,		/* USAGE_PAGE (Led) */
	0x19, 0x01,		/* USAGE_MINIMUM (1) */
	0x29, 0x03,		/* USAGE_MAXIMUM (3) */
	0x15, 0x00,		/* LOGICAL_MINIMUM (0) */
	0x25, 0x01,		/* LOGICAL_MAXIMUM (1) */
	0x95, 0x03,		/* REPORT_COUNT (3) */
	0x75, 0x01,		/* REPORT_SIZE (1) */
	0x91, 0x02,		/* Output (Data,Var,Abs) */
	0x95, 0x01,		/* REPORT_COUNT (1) */
	0x75, 0x05,		/* REPORT_SIZE (5) */
	0x91, 0x01,		/* Output (Cnst,Var,Abs) */
	0xc0,		/* END_COLLECTION */
};
void emit(int fd, int type, int code, int val)
{
	struct input_event ie;
	memset(&ie, 0, sizeof(ie));

	ie.type = type;
	ie.code = code;
	ie.value = val;
	/* timestamp values below are ignored */
	ie.time.tv_sec = 0;
	ie.time.tv_usec = 0;

	int ret = write(fd, &ie, sizeof(ie));
	if(ret < 0)
	{
		int err = errno;
		LOG_ERROR(std::to_string(err), "Virtual keyboard emit");
	}
}
static int uhid_write(int fd, const struct uhid_event* ev)
{
	ssize_t ret;

	ret = write(fd, ev, sizeof(*ev));
	if(ret < 0)
	{
		fprintf(stderr, "Cannot write to uhid: %m\n");
		return -errno;
	}
	else if(ret != sizeof(*ev))
	{
		fprintf(stderr, "Wrong size written to uhid: %zd != %zu\n",
				ret, sizeof(ev));
		return -EFAULT;
	}
	else
	{
		return 0;
	}
}
static int create(int fd)
{
	struct uhid_event ev;

	memset(&ev, 0, sizeof(ev));
	ev.type = UHID_CREATE;
	strcpy((char*) ev.u.create.name, "test-uhid-device");
	ev.u.create.rd_data = rdesc;
	ev.u.create.rd_size = sizeof(rdesc);
	ev.u.create.bus = BUS_USB;
	ev.u.create.vendor = 0x15d9;
	ev.u.create.product = 0x0a37;
	ev.u.create.version = 0;
	ev.u.create.country = 0;

	return uhid_write(fd, &ev);
}


void system_utilities::keyboard_utilities::press_button(int key)
{
	// Write a key to the keyboard buffer
	if(fd > 0)
	{
		struct input_event event;
		emit(fd, EV_KEY, key, 1);
		emit(fd, EV_SYN, SYN_REPORT, 0);
		emit(fd, EV_KEY, key, 0);
		emit(fd, EV_SYN, SYN_REPORT, 0);
	}
}

#endif

system_utilities::keyboard_utilities::Keyboard::Keyboard()
{
	system_utilities::keyboard_utilities::setup();
	buffer.keyboard->initalize_codes();
	buffer.keyboard->connect_to_keyboard();
	buffer.keyboard->start_listening();
}

system_utilities::keyboard_utilities::Keyboard::~Keyboard()
{ 
	buffer.keyboard->stop_listening();
	system_utilities::keyboard_utilities::tear_down();
}

void system_utilities::keyboard_utilities::Keyboard::wait_for_first_key(KPI key)
{

}

#ifdef _WIN32
char system_utilities::keyboard_utilities::get_char_from_kpi(KPI key)
{
	if(key == KEY::A)
		return 'A';
	else if(key == KEY::B)
		return 'B';
	else if(key == KEY::C)
		return 'C';
	else if(key == KEY::D)
		return 'D';
	else if(key == KEY::E)
		return 'E';
	else if(key == KEY::F)
		return 'F';
	else if(key == KEY::G)
		return 'G';
	else if(key == KEY::H)
		return 'H';
	else if(key == KEY::I)
		return 'I';
	else if(key == KEY::J)
		return 'J';
	else if(key == KEY::K)
		return 'K';
	else if(key == KEY::L)
		return 'L';
	else if(key == KEY::M)
		return 'M';
	else if(key == KEY::N)
		return 'N';
	else if(key == KEY::O)
		return 'O';
	else if(key == KEY::P)
		return 'P';
	else if(key == KEY::Q)
		return 'Q';
	else if(key == KEY::R)
		return 'R';
	else if(key == KEY::S)
		return 'S';
	else if(key == KEY::T)
		return 'T';
	else if(key == KEY::U)
		return 'U';
	else if(key == KEY::V)
		return 'V';
	else if(key == KEY::W)
		return 'W';
	else if(key == KEY::X)
		return 'X';
	else if(key == KEY::Y)
		return 'Y';
	else if(key == KEY::Z)
		return 'Z';
	else if(key == KEY::NUM_0)
		return '0';
	else if(key == KEY::NUM_1)
		return '1';
	else if(key == KEY::NUM_2)
		return '2';
	else if(key == KEY::NUM_3)
		return '3';
	else if(key == KEY::NUM_4)
		return '4';
	else if(key == KEY::NUM_5)
		return '5';
	else if(key == KEY::NUM_6)
		return '6';
	else if(key == KEY::NUM_7)
		return '7';
	else if(key == KEY::NUM_8)
		return '8';
	else if(key == KEY::NUM_9)
		return '9';
	else if(key == KEY::NUM_PAD::NUM_0)
		return VK_NUMPAD0;
	else if(key == KEY::NUM_PAD::NUM_1)
		return VK_NUMPAD1;
	else if(key == KEY::NUM_PAD::NUM_2)
		return VK_NUMPAD2;
	else if(key == KEY::NUM_PAD::NUM_3)
		return VK_NUMPAD3;
	else if(key == KEY::NUM_PAD::NUM_4)
		return VK_NUMPAD4;
	else if(key == KEY::NUM_PAD::NUM_5)
		return VK_NUMPAD5;
	else if(key == KEY::NUM_PAD::NUM_6)
		return VK_NUMPAD6;
	else if(key == KEY::NUM_PAD::NUM_7)
		return VK_NUMPAD7;
	else if(key == KEY::NUM_PAD::NUM_8)
		return VK_NUMPAD8;
	else if(key == KEY::NUM_PAD::NUM_9)
		return VK_NUMPAD9;
	else if(key == KEY::L_SHIFT)
		return VK_LSHIFT;
	else if(key == KEY::ENTER)
		return VK_RETURN;
	return 255;
}
#endif
#ifdef __linux__
#include <linux/input.h>
char system_utilities::keyboard_utilities::get_char_from_kpi(KPI key)
{
	if(key == KEY::A)
		return KEY_A;
	else if(key == KEY::B)
		return KEY_B;
	else if(key == KEY::C)
		return KEY_C;
	else if(key == KEY::D)
		return KEY_D;
	else if(key == KEY::E)
		return KEY_E;
	else if(key == KEY::F)
		return KEY_F;
	else if(key == KEY::G)
		return KEY_G;
	else if(key == KEY::H)
		return KEY_H;
	else if(key == KEY::I)
		return KEY_I;
	else if(key == KEY::J)
		return KEY_J;
	else if(key == KEY::K)
		return KEY_K;
	else if(key == KEY::L)
		return KEY_L;
	else if(key == KEY::M)
		return KEY_M;
	else if(key == KEY::N)
		return KEY_N;
	else if(key == KEY::O)
		return KEY_O;
	else if(key == KEY::P)
		return KEY_P;
	else if(key == KEY::Q)
		return KEY_Q;
	else if(key == KEY::R)
		return KEY_R;
	else if(key == KEY::S)
		return KEY_S;
	else if(key == KEY::T)
		return KEY_T;
	else if(key == KEY::U)
		return KEY_U;
	else if(key == KEY::V)
		return KEY_V;
	else if(key == KEY::W)
		return KEY_W;
	else if(key == KEY::X)
		return KEY_X;
	else if(key == KEY::Y)
		return KEY_Y;
	else if(key == KEY::Z)
		return KEY_Z;
	else if(key == KEY::NUM_0)
		return KEY_0;
	else if(key == KEY::NUM_1)
		return KEY_1;
	else if(key == KEY::NUM_2)
		return KEY_2;
	else if(key == KEY::NUM_3)
		return KEY_3;
	else if(key == KEY::NUM_4)
		return KEY_4;
	else if(key == KEY::NUM_5)
		return KEY_5;
	else if(key == KEY::NUM_6)
		return KEY_6;
	else if(key == KEY::NUM_7)
		return KEY_7;
	else if(key == KEY::NUM_8)
		return KEY_8;
	else if(key == KEY::NUM_9)
		return KEY_9;
	else if(key == KEY::NUM_PAD::NUM_0)
		return KEY_KP0;
	else if(key == KEY::NUM_PAD::NUM_1)
		return KEY_KP1;
	else if(key == KEY::NUM_PAD::NUM_2)
		return KEY_KP2;
	else if(key == KEY::NUM_PAD::NUM_3)
		return KEY_KP3;
	else if(key == KEY::NUM_PAD::NUM_4)
		return KEY_KP4;
	else if(key == KEY::NUM_PAD::NUM_5)
		return KEY_KP5;
	else if(key == KEY::NUM_PAD::NUM_6)
		return KEY_KP6;
	else if(key == KEY::NUM_PAD::NUM_7)
		return KEY_KP7;
	else if(key == KEY::NUM_PAD::NUM_8)
		return KEY_KP8;
	else if(key == KEY::NUM_PAD::NUM_9)
		return KEY_KP9;
	return 255;
}
#endif


void system_utilities::keyboard_utilities::Keyboard::operator<<(const std::string& input)
{
	for(char i : input)
	{
		system_utilities::keyboard_utilities::press_button(i);
	}
	system_utilities::keyboard_utilities::press_button(system_utilities::keyboard_utilities::get_char_from_kpi(KEY::ENTER));
}

void system_utilities::keyboard_utilities::Keyboard::operator<<(const int& input)
{
	operator<<(std::to_string(input));
}

void system_utilities::keyboard_utilities::Keyboard::operator<<(const char& input)
{
	system_utilities::keyboard_utilities::press_button(input);
}

void system_utilities::keyboard_utilities::Keyboard::set_key_operation(KPI key, std::function<void()> func)
{
	buffer.keyboard->set_on_press(key, func);
}