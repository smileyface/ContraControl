#include <chrono>
#include <iostream>
#include <thread>

#include "keyboard_interface_utilities.h"
#include "system_utilities.h"

#include "test_utilities.h"
#include "Utilities/exceptions.h"

#include "../../dev/Controller/controller_main.h"
#include "../../dev/Model/model_main.h"

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
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
	std::this_thread::sleep_for(std::chrono::milliseconds(40));
}

char system_utilities::keyboard_utilities::get_char_from_kpi(KPI key)
{
	char value = 0xFF;
	if(key == KEY::A)
		value = 'A';
	else if(key == KEY::B)
		value = 'B';
	else if(key == KEY::C)
		value = 'C';
	else if(key == KEY::D)
		value = 'D';
	else if(key == KEY::E)
		value = 'E';
	else if(key == KEY::F)
		value = 'F';
	else if(key == KEY::G)
		value = 'G';
	else if(key == KEY::H)
		value = 'H';
	else if(key == KEY::I)
		value = 'I';
	else if(key == KEY::J)
		value = 'J';
	else if(key == KEY::K)
		value = 'K';
	else if(key == KEY::L)
		value = 'L';
	else if(key == KEY::M)
		value = 'M';
	else if(key == KEY::N)
		value = 'N';
	else if(key == KEY::O)
		value = 'O';
	else if(key == KEY::P)
		value = 'P';
	else if(key == KEY::Q)
		value = 'Q';
	else if(key == KEY::R)
		value = 'R';
	else if(key == KEY::S)
		value = 'S';
	else if(key == KEY::T)
		value = 'T';
	else if(key == KEY::U)
		value = 'U';
	else if(key == KEY::V)
		value = 'V';
	else if(key == KEY::W)
		value = 'W';
	else if(key == KEY::X)
		value = 'X';
	else if(key == KEY::Y)
		value = 'Y';
	else if(key == KEY::Z)
		value = 'Z';
	else if(key == KEY::NUM_0)
		value = '0';
	else if(key == KEY::NUM_1)
		value = '1';
	else if(key == KEY::NUM_2)
		value = '2';
	else if(key == KEY::NUM_3)
		value = '3';
	else if(key == KEY::NUM_4)
		value = '4';
	else if(key == KEY::NUM_5)
		value = '5';
	else if(key == KEY::NUM_6)
		value = '6';
	else if(key == KEY::NUM_7)
		value = '7';
	else if(key == KEY::NUM_8)
		value = '8';
	else if(key == KEY::NUM_9)
		value = '9';
	else if(key == KEY::NUM_PAD::NUM_0)
		value = VK_NUMPAD0;
	else if(key == KEY::NUM_PAD::NUM_1)
		value = VK_NUMPAD1;
	else if(key == KEY::NUM_PAD::NUM_2)
		value = VK_NUMPAD2;
	else if(key == KEY::NUM_PAD::NUM_3)
		value = VK_NUMPAD3;
	else if(key == KEY::NUM_PAD::NUM_4)
		value = VK_NUMPAD4;
	else if(key == KEY::NUM_PAD::NUM_5)
		value = VK_NUMPAD5;
	else if(key == KEY::NUM_PAD::NUM_6)
		value = VK_NUMPAD6;
	else if(key == KEY::NUM_PAD::NUM_7)
		value = VK_NUMPAD7;
	else if(key == KEY::NUM_PAD::NUM_8)
		value = VK_NUMPAD8;
	else if(key == KEY::NUM_PAD::NUM_9)
		value = VK_NUMPAD9;
	else if(key == KEY::L_SHIFT)
		value = VK_LSHIFT;
	else if(key == KEY::ENTER)
		value = VK_RETURN;
	return value;
}

void system_utilities::keyboard_utilities::tear_down()
{
}

void system_utilities::keyboard_utilities::setup()
{
}
#endif // _WIN32