#include <thread>
#include <chrono>
#include <iostream>

#include "system_utilities.h"
#include "keyboard_interface_utilities.h"

#include "Utilities/exceptions.h"
#include "test_utilities.h"

#include "../../dev/Model/model_main.h"
#include "../../dev/Controller/controller_main.h"

#include "../../Network/network_main.h"

#ifdef __linux__
#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include <linux/uhid.h>
#include <sstream>
#include "../../Network/system_interfaces/linux_network_interface.h"
#include "../../dev/View/input_interface/sys_interface/linux_keyboard.h"

int fd = 0;

void enable_keys(int fd)
{
	ioctl(fd, UI_SET_EVBIT, EV_KEY);
	ioctl(fd, UI_SET_KEYBIT, KEY_A);
	ioctl(fd, UI_SET_KEYBIT, KEY_B);
	ioctl(fd, UI_SET_KEYBIT, KEY_C);
	ioctl(fd, UI_SET_KEYBIT, KEY_D);
	ioctl(fd, UI_SET_KEYBIT, KEY_E);
	ioctl(fd, UI_SET_KEYBIT, KEY_F);
	ioctl(fd, UI_SET_KEYBIT, KEY_G);
	ioctl(fd, UI_SET_KEYBIT, KEY_H);
	ioctl(fd, UI_SET_KEYBIT, KEY_I);
	ioctl(fd, UI_SET_KEYBIT, KEY_J);
	ioctl(fd, UI_SET_KEYBIT, KEY_K);
	ioctl(fd, UI_SET_KEYBIT, KEY_L);
	ioctl(fd, UI_SET_KEYBIT, KEY_M);
	ioctl(fd, UI_SET_KEYBIT, KEY_N);
	ioctl(fd, UI_SET_KEYBIT, KEY_O);
	ioctl(fd, UI_SET_KEYBIT, KEY_P);
	ioctl(fd, UI_SET_KEYBIT, KEY_Q);
	ioctl(fd, UI_SET_KEYBIT, KEY_R);
	ioctl(fd, UI_SET_KEYBIT, KEY_S);
	ioctl(fd, UI_SET_KEYBIT, KEY_T);
	ioctl(fd, UI_SET_KEYBIT, KEY_U);
	ioctl(fd, UI_SET_KEYBIT, KEY_V);
	ioctl(fd, UI_SET_KEYBIT, KEY_W);
	ioctl(fd, UI_SET_KEYBIT, KEY_X);
	ioctl(fd, UI_SET_KEYBIT, KEY_Y);
	ioctl(fd, UI_SET_KEYBIT, KEY_Z);
	ioctl(fd, UI_SET_KEYBIT, KEY_ENTER);
}

void system_utilities::keyboard_utilities::setup()
{
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
		testing_utilities::input_utilities::connect_keyboard("/dev/uinput");
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
}

void system_utilities::keyboard_utilities::tear_down()
{
	ioctl(fd, UI_DEV_DESTROY);
	close(fd);
}


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
	else if(key == KEY::ENTER)
		return KEY_ENTER;
	return 255;
}
#endif