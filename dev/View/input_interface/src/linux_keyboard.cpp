#ifdef __linux__

#include "../sys_interface/linux_keyboard.h"
#include "../sys_interface/key_input_interface.h"

#include <unistd.h>
#include <linux/input-event-codes.h>

void Linux_Keyboard::initalize_codes()
{
	code_map[KEY_A] = KEY::A;
	code_map[KEY_B] = KEY::B;
	code_map[KEY_C] = KEY::C;
	code_map[KEY_D] = KEY::D;
	code_map[KEY_E] = KEY::E;
	code_map[KEY_F] = KEY::F;
	code_map[KEY_G] = KEY::G;
	code_map[KEY_H] = KEY::H;
	code_map[KEY_I] = KEY::I;
	code_map[KEY_J] = KEY::J;
	code_map[KEY_K] = KEY::K;
	code_map[KEY_L] = KEY::L;
	code_map[KEY_M] = KEY::M;
	code_map[KEY_N] = KEY::N;
	code_map[KEY_O] = KEY::O;
	code_map[KEY_P] = KEY::P;
	code_map[KEY_Q] = KEY::Q;
	code_map[KEY_R] = KEY::R;
	code_map[KEY_S] = KEY::S;
	code_map[KEY_T] = KEY::T;
	code_map[KEY_U] = KEY::U;
	code_map[KEY_V] = KEY::V;
	code_map[KEY_W] = KEY::W;
	code_map[KEY_X] = KEY::X;
	code_map[KEY_Y] = KEY::Y;
	code_map[KEY_Z] = KEY::Z;
	code_map[KEY_K] = KEY::K;
	code_map[KEY_0] = KEY::NUM_0;
	code_map[KEY_1] = KEY::NUM_1;
	code_map[KEY_2] = KEY::NUM_2;
	code_map[KEY_3] = KEY::NUM_3;
	code_map[KEY_4] = KEY::NUM_4;
	code_map[KEY_5] = KEY::NUM_5;
	code_map[KEY_6] = KEY::NUM_6;
	code_map[KEY_7] = KEY::NUM_7;
	code_map[KEY_8] = KEY::NUM_8;
	code_map[KEY_9] = KEY::NUM_9;
	code_map[KEY_KP0] = KEY::NUM_PAD::NUM_0;
	code_map[KEY_KP1] = KEY::NUM_PAD::NUM_1;
	code_map[KEY_KP2] = KEY::NUM_PAD::NUM_2;
	code_map[KEY_KP3] = KEY::NUM_PAD::NUM_3;
	code_map[KEY_KP4] = KEY::NUM_PAD::NUM_4;
	code_map[KEY_KP5] = KEY::NUM_PAD::NUM_5;
	code_map[KEY_KP6] = KEY::NUM_PAD::NUM_6;
	code_map[KEY_KP7] = KEY::NUM_PAD::NUM_7;
	code_map[KEY_KP8] = KEY::NUM_PAD::NUM_8;
	code_map[KEY_KP9] = KEY::NUM_PAD::NUM_9;
}

Linux_Keyboard::Linux_Keyboard()
{
	initalize_codes();
	active = true;
	keyboard_fd = 0;
	keyboard_ev = new input_event();
	keyboard_st = new keyboard_state();
	keyboard_fd = open(KEYBOARD_DEV, O_RDONLY | O_NONBLOCK);
	if(keyboard_fd > 0)
	{
		ioctl(keyboard_fd, EVIOCGNAME(256), name);
		std::cout << "   Name: " << name << std::endl;
		active = true;
		keyboard_present = true;
	}
	else
	{
		keyboard_present = false;
	}
}

Linux_Keyboard::~Linux_Keyboard()
{
	if(keyboard_fd > 0)
	{
		active = false;
		pthread_join(thread, 0);
		close(keyboard_fd);
	}
	delete keyboard_st;
	delete keyboard_ev;
	keyboard_fd = 0;
}

void Linux_Keyboard::readEv()
{
	int bytes = read(keyboard_fd, keyboard_ev, sizeof(*keyboard_ev));
	if(bytes > 0)
	{
		if(keyboard_ev->type & EV_KEY)
		{
			code_map[keyboard_ev->code] = keyboard_ev->value;
		}
	}

}

short Linux_Keyboard::getKeyState(short key)
{
	return keyboard_st->keys[key];
}

std::map<int, KPI> code_map;


#endif // __linux__
