
#ifdef _WIN32
#include "../sys_interface/windows_keyboard.h"
#include "../sys_interface/key_input_interface.h"
#include "../action_layer/action_layer.h"

#include <Windows.h>
#include <vector>
#include <string>
#include <iostream>

UINT nDevices;

void Windows_Keyboard::initalize_codes()
{
	master_code_map['A'] = KEY::A;
	master_code_map['B'] = KEY::B;
	master_code_map['C'] = KEY::C;
	master_code_map['D'] = KEY::D;
	master_code_map['E'] = KEY::E;
	master_code_map['F'] = KEY::F;
	master_code_map['G'] = KEY::G;
	master_code_map['H'] = KEY::H;
	master_code_map['I'] = KEY::I;
	master_code_map['J'] = KEY::J;
	master_code_map['K'] = KEY::K;
	master_code_map['L'] = KEY::L;
	master_code_map['M'] = KEY::M;
	master_code_map['N'] = KEY::N;
	master_code_map['O'] = KEY::O;
	master_code_map['P'] = KEY::P;
	master_code_map['Q'] = KEY::Q;
	master_code_map['R'] = KEY::R;
	master_code_map['S'] = KEY::S;
	master_code_map['T'] = KEY::T;
	master_code_map['U'] = KEY::U;
	master_code_map['V'] = KEY::V;
	master_code_map['W'] = KEY::W;
	master_code_map['X'] = KEY::X;
	master_code_map['Y'] = KEY::Y;
	master_code_map['Z'] = KEY::Z;
	master_code_map['0'] = KEY::NUM_0;
	master_code_map['1'] = KEY::NUM_1;
	master_code_map['2'] = KEY::NUM_2;
	master_code_map['3'] = KEY::NUM_3;
	master_code_map['4'] = KEY::NUM_4;
	master_code_map['5'] = KEY::NUM_5;
	master_code_map['6'] = KEY::NUM_6;
	master_code_map['7'] = KEY::NUM_7;
	master_code_map['8'] = KEY::NUM_8;
	master_code_map['9'] = KEY::NUM_9;
	master_code_map[VK_NUMPAD0] = KEY::NUM_PAD::NUM_0;
	master_code_map[VK_NUMPAD1] = KEY::NUM_PAD::NUM_1;
	master_code_map[VK_NUMPAD2] = KEY::NUM_PAD::NUM_2;
	master_code_map[VK_NUMPAD3] = KEY::NUM_PAD::NUM_3;
	master_code_map[VK_NUMPAD4] = KEY::NUM_PAD::NUM_4;
	master_code_map[VK_NUMPAD5] = KEY::NUM_PAD::NUM_5;
	master_code_map[VK_NUMPAD6] = KEY::NUM_PAD::NUM_6;
	master_code_map[VK_NUMPAD7] = KEY::NUM_PAD::NUM_7;
	master_code_map[VK_NUMPAD8] = KEY::NUM_PAD::NUM_8;
	master_code_map[VK_NUMPAD9] = KEY::NUM_PAD::NUM_9;
	master_code_map[VK_RETURN] = KEY::ENTER;
	master_code_map[VK_LSHIFT] = KEY::L_SHIFT;
	master_code_map[VK_LMENU] = KEY::L_ALT;
	master_code_map[VK_LCONTROL] = KEY::L_CTRL;
	master_code_map[VK_TAB] = KEY::TAB;

	for(Keyboard_Code_Map::iterator i = master_code_map.begin(); i != master_code_map.end(); i++)
	{
		i->second.set_code(i->first);
	}
}

Windows_Keyboard::Windows_Keyboard()
{
	initalize_codes();
	action_stack.setup_action_layers();
}

Windows_Keyboard::~Windows_Keyboard()
{
}

void Windows_Keyboard::connect_to_keyboard()
{
	//if the keyboard is already connected, get out.
	if(keyboard_present == true)
	{
		return;
	}
	if(GetRawInputDeviceList(NULL, &nDevices, sizeof(RAWINPUTDEVICELIST)) != 0)
	{
	}
	if(nDevices == 0)
	{
		keyboard_present = false;
	}
	else
	{
		keyboard_present = true;
	}
}

void Windows_Keyboard::readEv()
{
	for(std::pair<int, KPI> key : master_code_map)
	{
		action_stack.get_active_layer()->handle_event(key.second, GetKeyState(key.second.get_code()) & 0x8000);
	}
}



#endif
