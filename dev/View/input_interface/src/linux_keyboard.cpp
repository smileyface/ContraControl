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
	active_layer->add_code(KEY_A, KEY::A);
	active_layer->add_code(KEY_B, KEY::B);
	active_layer->add_code(KEY_C, KEY::C);
	active_layer->add_code(KEY_D, KEY::D);
	active_layer->add_code(KEY_E, KEY::E);
	active_layer->add_code(KEY_F, KEY::F);
	active_layer->add_code(KEY_G, KEY::G);
	active_layer->add_code(KEY_F, KEY::H);
	active_layer->add_code(KEY_I, KEY::I);
	active_layer->add_code(KEY_J, KEY::J);
	active_layer->add_code(KEY_K, KEY::K);
	active_layer->add_code(KEY_L, KEY::L);
	active_layer->add_code(KEY_M, KEY::M);
	active_layer->add_code(KEY_N, KEY::N);
	active_layer->add_code(KEY_O, KEY::O);
	active_layer->add_code(KEY_P, KEY::P);
	active_layer->add_code(KEY_Q, KEY::Q);
	active_layer->add_code(KEY_R, KEY::R);
	active_layer->add_code(KEY_S, KEY::S);
	active_layer->add_code(KEY_T, KEY::T);
	active_layer->add_code(KEY_U, KEY::U);
	active_layer->add_code(KEY_V, KEY::V);
	active_layer->add_code(KEY_W, KEY::W);
	active_layer->add_code(KEY_X, KEY::X);
	active_layer->add_code(KEY_Y, KEY::Y);
	active_layer->add_code(KEY_Z, KEY::Z);
	active_layer->add_code(KEY_0, KEY::NUM_0);
	active_layer->add_code(KEY_1, KEY::NUM_1);
	active_layer->add_code(KEY_2, KEY::NUM_2);
	active_layer->add_code(KEY_3, KEY::NUM_3);
	active_layer->add_code(KEY_4, KEY::NUM_4);
	active_layer->add_code(KEY_5, KEY::NUM_5);
	active_layer->add_code(KEY_6, KEY::NUM_6);
	active_layer->add_code(KEY_7, KEY::NUM_7);
	active_layer->add_code(KEY_8, KEY::NUM_8);
	active_layer->add_code(KEY_9, KEY::NUM_9);
	active_layer->add_code(KEY_KP0, KEY::NUM_PAD::NUM_0);
	active_layer->add_code(KEY_KP1, KEY::NUM_PAD::NUM_1);
	active_layer->add_code(KEY_KP2, KEY::NUM_PAD::NUM_2);
	active_layer->add_code(KEY_KP3, KEY::NUM_PAD::NUM_3);
	active_layer->add_code(KEY_KP4, KEY::NUM_PAD::NUM_4);
	active_layer->add_code(KEY_KP5, KEY::NUM_PAD::NUM_5);
	active_layer->add_code(KEY_KP6, KEY::NUM_PAD::NUM_6);
	active_layer->add_code(KEY_KP7, KEY::NUM_PAD::NUM_7);
	active_layer->add_code(KEY_KP8, KEY::NUM_PAD::NUM_8);
	active_layer->add_code(KEY_KP9, KEY::NUM_PAD::NUM_9);
	active_layer->add_code(KEY_ENTER, KEY::ENTER);
	active_layer->add_code(KEY_LEFTSHIFT, KEY::L_SHIFT);
	active_layer->add_code(KEY_LEFTALT, KEY::L_ALT);
	active_layer->add_code(KEY_LEFTCTRL, KEY::L_CTRL);

}

Linux_Keyboard::Linux_Keyboard()
{
	active = true;
	keyboard_fd = 0;
	keyboard_ev = new input_event();
	keyboard_st = new keyboard_state();


	setup_action_layers();
	connect_to_keyboard();
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

bool Linux_Keyboard::connect_to_keyboard()
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
		keyboard_present = connect_to_keyboard(location);
		if(keyboard_present)
		{
			break;
		}
		LOG_INFO(location + " not having a useful file descriptor", "Keyboard finder");
	}
	return keyboard_present;
}

bool Linux_Keyboard::connect_to_keyboard(std::string path_to_keyboard)
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
	return keyboard_present;
}

void Linux_Keyboard::readEv()
{
	int bytes = read(keyboard_fd, keyboard_ev, sizeof(*keyboard_ev));
	if(bytes > 0)
	{
		if(keyboard_ev->type & EV_KEY)
		{
			std::lock_guard<std::mutex> lock(keyboard_mutex);
			active_layer->handle_event(keyboard_ev->code, keyboard_ev->value);
		}
	}

}

short Linux_Keyboard::getKeyState(short key)
{
	return keyboard_st->keys[key];
}

std::map<int, KPI> code_map;


#endif // __linux__
