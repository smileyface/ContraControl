#ifdef __linux__

#include "../sys_interface/linux_keyboard.h"
#include "../sys_interface/key_input_interface.h"
#include "Messaging/message_relay.h"

#include <unistd.h>
#include <linux/input-event-codes.h>
#include <mutex>
#include <regex>

#include <dirent.h>

std::mutex keyboard_mutex;

std::vector<std::string> event_eligible;

void Linux_Keyboard::initalize_codes()
{
	master_code_map[KEY_A] = KEY::A;
	master_code_map[KEY_B] = KEY::B;
	master_code_map[KEY_C] = KEY::C;
	master_code_map[KEY_D] = KEY::D;
	master_code_map[KEY_E] = KEY::E;
	master_code_map[KEY_F] = KEY::F;
	master_code_map[KEY_G] = KEY::G;
	master_code_map[KEY_F] = KEY::H;
	master_code_map[KEY_I] = KEY::I;
	master_code_map[KEY_J] = KEY::J;
	master_code_map[KEY_K] = KEY::K;
	master_code_map[KEY_L] = KEY::L;
	master_code_map[KEY_M] = KEY::M;
	master_code_map[KEY_N] = KEY::N;
	master_code_map[KEY_O] = KEY::O;
	master_code_map[KEY_P] = KEY::P;
	master_code_map[KEY_Q] = KEY::Q;
	master_code_map[KEY_R] = KEY::R;
	master_code_map[KEY_S] = KEY::S;
	master_code_map[KEY_T] = KEY::T;
	master_code_map[KEY_U] = KEY::U;
	master_code_map[KEY_V] = KEY::V;
	master_code_map[KEY_W] = KEY::W;
	master_code_map[KEY_X] = KEY::X;
	master_code_map[KEY_Y] = KEY::Y;
	master_code_map[KEY_Z] = KEY::Z;
	master_code_map[KEY_0] = KEY::NUM_0;
	master_code_map[KEY_1] = KEY::NUM_1;
	master_code_map[KEY_2] = KEY::NUM_2;
	master_code_map[KEY_3] = KEY::NUM_3;
	master_code_map[KEY_4] = KEY::NUM_4;
	master_code_map[KEY_5] = KEY::NUM_5;
	master_code_map[KEY_6] = KEY::NUM_6;
	master_code_map[KEY_7] = KEY::NUM_7;
	master_code_map[KEY_8] = KEY::NUM_8;
	master_code_map[KEY_9] = KEY::NUM_9;
	master_code_map[KEY_KP0] = KEY::NUM_PAD::NUM_0;
	master_code_map[KEY_KP1] = KEY::NUM_PAD::NUM_1;
	master_code_map[KEY_KP2] = KEY::NUM_PAD::NUM_2;
	master_code_map[KEY_KP3] = KEY::NUM_PAD::NUM_3;
	master_code_map[KEY_KP4] = KEY::NUM_PAD::NUM_4;
	master_code_map[KEY_KP5] = KEY::NUM_PAD::NUM_5;
	master_code_map[KEY_KP6] = KEY::NUM_PAD::NUM_6;
	master_code_map[KEY_KP7] = KEY::NUM_PAD::NUM_7;
	master_code_map[KEY_KP8] = KEY::NUM_PAD::NUM_8;
	master_code_map[KEY_KP9] = KEY::NUM_PAD::NUM_9;
	master_code_map[KEY_ENTER] = KEY::ENTER;
	master_code_map[KEY_LEFTSHIFT] = KEY::L_SHIFT;
	master_code_map[KEY_LEFTALT] = KEY::L_ALT;
	master_code_map[KEY_LEFTCTRL] = KEY::L_CTRL;

	for(Keyboard_Code_Map::iterator i = master_code_map.begin(); i != master_code_map.end(); i++)
	{
		i->second.set_code(i->first);
	}
}

Linux_Keyboard::Linux_Keyboard()
{
	active = true;
	keyboard_fd = 0;
	keyboard_ev = new input_event();
	keyboard_st = new keyboard_state();

	initalize_codes();
	action_stack.setup_action_layers();
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

void Linux_Keyboard::connect_to_keyboard()
{
	struct dirent* entry = nullptr;
	DIR* dp = nullptr;

	dp = opendir("/dev/input");

	if(dp != nullptr)
	{
		std::regex e("event(\\d)");
		while((entry = readdir(dp)))
		{

			std::string s(entry->d_name);
			if(std::regex_match(s, e))
			{
				event_eligible.push_back(s);
			}
		}
	}

	closedir(dp);
	bool keyboard_present = false;
	for(int i = 0; i < event_eligible.size(); i++)
	{
		std::string location = "/dev/input/" + event_eligible[i];
		connect_to_keyboard(location);
		if(keyboard_present)
		{
			break;
		}
	}
}

void Linux_Keyboard::connect_to_keyboard(std::string path_to_keyboard)
{
	if((keyboard_fd = open(path_to_keyboard.c_str(), O_RDONLY | O_NONBLOCK)) > 0)
	{
		ioctl(keyboard_fd, EVIOCGNAME(256), name);
		active = true;
		keyboard_present = true;
		LOG_INFO(path_to_keyboard + " found", "Keyboard connection");
	}
	else
	{
		std::string error_as_string = std::strerror(errno);
		LOG_DEBUG(path_to_keyboard + " failed because of error code " + error_as_string);
		keyboard_present = false;
	}
}

void Linux_Keyboard::readEv()
{
	int bytes = read(keyboard_fd, keyboard_ev, sizeof(*keyboard_ev));
	if(bytes > 0)
	{
		if(keyboard_ev->type & EV_KEY)
		{
			std::lock_guard<std::mutex> lock(keyboard_mutex);
			KPI pressed_key;
			for(auto i : master_code_map)
			{
				if(i.second.get_code() == keyboard_ev->code)
					pressed_key = i.second;
			}
			action_stack.get_active_layer()->handle_event(pressed_key, keyboard_ev->value);
		}
	}

}

short Linux_Keyboard::getKeyState(short key)
{
	return keyboard_st->keys[key];
}

std::map<int, KPI> code_map;


#endif // __linux__
