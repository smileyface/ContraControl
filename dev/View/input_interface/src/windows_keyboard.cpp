
#ifdef _WIN32
#include "../sys_interface/windows_keyboard.h"
#include "../sys_interface/key_input_interface.h"

#include <Windows.h>
#include <vector>
#include <string>

UINT nDevices;

void Windows_Keyboard::initalize_codes()
{
	this->code_map['A'] = KEY::A;
	this->code_map['B'] = KEY::B;
	this->code_map['C'] = KEY::C;
	this->code_map['D'] = KEY::D;
	this->code_map['E'] = KEY::E;
	code_map['F'] = KEY::F;
	code_map['G'] = KEY::G;
	code_map['H'] = KEY::H;
	code_map['I'] = KEY::I;
	code_map['J'] = KEY::J;
	code_map['K'] = KEY::K;
	code_map['L'] = KEY::L;
	code_map['M'] = KEY::M;
	code_map['N'] = KEY::N;
	code_map['O'] = KEY::O;
	code_map['P'] = KEY::P;
	code_map['Q'] = KEY::Q;
	code_map['R'] = KEY::R;
	code_map['S'] = KEY::S;
	code_map['T'] = KEY::T;
	code_map['U'] = KEY::U;
	code_map['V'] = KEY::V;
	code_map['W'] = KEY::W;
	code_map['X'] = KEY::X;
	code_map['Y'] = KEY::Y;
	code_map['Z'] = KEY::Z;
	code_map['0'] = KEY::NUM_0;
	code_map['1'] = KEY::NUM_1;
	code_map['2'] = KEY::NUM_2;
	code_map['3'] = KEY::NUM_3;
	code_map['4'] = KEY::NUM_4;
	code_map['5'] = KEY::NUM_5;
	code_map['6'] = KEY::NUM_6;
	code_map['7'] = KEY::NUM_7;
	code_map['8'] = KEY::NUM_8;
	code_map['9'] = KEY::NUM_9;
	code_map[VK_NUMPAD0] = KEY::NUM_PAD::NUM_0;
	code_map[VK_NUMPAD1] = KEY::NUM_PAD::NUM_1;
	code_map[VK_NUMPAD2] = KEY::NUM_PAD::NUM_2;
	code_map[VK_NUMPAD3] = KEY::NUM_PAD::NUM_3;
	code_map[VK_NUMPAD4] = KEY::NUM_PAD::NUM_4;
	code_map[VK_NUMPAD5] = KEY::NUM_PAD::NUM_5;
	code_map[VK_NUMPAD6] = KEY::NUM_PAD::NUM_6;
	code_map[VK_NUMPAD7] = KEY::NUM_PAD::NUM_7;
	code_map[VK_NUMPAD8] = KEY::NUM_PAD::NUM_8;
	code_map[VK_NUMPAD9] = KEY::NUM_PAD::NUM_9;
	code_map[VK_RETURN] = KEY::ENTER;
	code_map[VK_LSHIFT] = KEY::L_SHIFT;
	code_map[VK_LMENU] = KEY::L_ALT;
	code_map[VK_LCONTROL] = KEY::L_CTRL;
}

Windows_Keyboard::Windows_Keyboard()
{
	connect_to_keyboard();
}

Windows_Keyboard::~Windows_Keyboard()
{

}

bool Windows_Keyboard::connect_to_keyboard()
{
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
	return keyboard_present;
}

void Windows_Keyboard::readEv()
{
	for(int i = 0; i < 256; i++)
	{
		if(code_map.find(i) != code_map.end())
		{
			code_map[i] = GetKeyState(i) & 0x8000;
		}
	}
}

short Windows_Keyboard::getKeyState(short key)
{
	return 0x00;
}



#endif
