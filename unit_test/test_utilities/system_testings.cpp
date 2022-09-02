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
			std::cout << "[  \u001b[33m" + mess->get_priority_string() + "\u001b[0m]";
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
	SendInput(1, &ip, sizeof(INPUT));
	std::this_thread::sleep_for(std::chrono::milliseconds(40));

	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));

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
