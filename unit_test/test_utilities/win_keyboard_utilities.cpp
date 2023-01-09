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

#ifdef _WIN32
#include <Windows.h>
#include "../../Network/system_interfaces/windows_network_interface.h"
#include "../../dev/View/input_interface/sys_interface/windows_keyboard.h"

void system_utilities::keyboard_utilities::press_button(int key)
{
	// This structure will be used to create the keyboard
// input event.
	INPUT ip { };
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
	std::this_thread::sleep_for(std::chrono::milliseconds(40));
}

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

void system_utilities::keyboard_utilities::tear_down()
{
	system_utilities::cleanup();
}

void system_utilities::keyboard_utilities::setup()
{
	system_utilities::setup();
}
#endif // _WIN32