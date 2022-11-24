
#ifdef _WIN32
#include "../sys_interface/windows_keyboard.h"
#include "../sys_interface/key_input_interface.h"

#include <Windows.h>
#include <vector>
#include <string>

UINT nDevices;

void Windows_Keyboard::initalize_codes()
{
	active_layer->add_code('A', KEY::A);
	active_layer->add_code('B', KEY::B);
	active_layer->add_code('C', KEY::C);
	active_layer->add_code('D', KEY::D);
	active_layer->add_code('E', KEY::E);
	active_layer->add_code('F', KEY::F);
	active_layer->add_code('G', KEY::G);
	active_layer->add_code('H', KEY::H);
	active_layer->add_code('I', KEY::I);
	active_layer->add_code('J', KEY::J);
	active_layer->add_code('K', KEY::K);
	active_layer->add_code('L', KEY::L);
	active_layer->add_code('M', KEY::M);
	active_layer->add_code('N', KEY::N);
	active_layer->add_code('O', KEY::O);
	active_layer->add_code('P', KEY::P);
	active_layer->add_code('Q', KEY::Q);
	active_layer->add_code('R', KEY::R);
	active_layer->add_code('S', KEY::S);
	active_layer->add_code('T', KEY::T);
	active_layer->add_code('U', KEY::U);
	active_layer->add_code('V', KEY::V);
	active_layer->add_code('W', KEY::W);
	active_layer->add_code('X', KEY::X);
	active_layer->add_code('Y', KEY::Y);
	active_layer->add_code('Z', KEY::Z);
	active_layer->add_code('0', KEY::NUM_0);
	active_layer->add_code('1', KEY::NUM_1);
	active_layer->add_code('2', KEY::NUM_2);
	active_layer->add_code('3', KEY::NUM_3);
	active_layer->add_code('4', KEY::NUM_4);
	active_layer->add_code('5', KEY::NUM_5);
	active_layer->add_code('6', KEY::NUM_6);
	active_layer->add_code('7', KEY::NUM_7);
	active_layer->add_code('8', KEY::NUM_8);
	active_layer->add_code('9', KEY::NUM_9);
	active_layer->add_code(VK_NUMPAD0, KEY::NUM_PAD::NUM_0);
	active_layer->add_code(VK_NUMPAD1, KEY::NUM_PAD::NUM_1);
	active_layer->add_code(VK_NUMPAD2, KEY::NUM_PAD::NUM_2);
	active_layer->add_code(VK_NUMPAD3, KEY::NUM_PAD::NUM_3);
	active_layer->add_code(VK_NUMPAD4, KEY::NUM_PAD::NUM_4);
	active_layer->add_code(VK_NUMPAD5, KEY::NUM_PAD::NUM_5);
	active_layer->add_code(VK_NUMPAD6, KEY::NUM_PAD::NUM_6);
	active_layer->add_code(VK_NUMPAD7, KEY::NUM_PAD::NUM_7);
	active_layer->add_code(VK_NUMPAD8, KEY::NUM_PAD::NUM_8);
	active_layer->add_code(VK_NUMPAD9, KEY::NUM_PAD::NUM_9);
	active_layer->add_code(VK_RETURN, KEY::ENTER);
	active_layer->add_code(VK_LSHIFT, KEY::L_SHIFT);
	active_layer->add_code(VK_LMENU, KEY::L_ALT);
	active_layer->add_code(VK_LCONTROL, KEY::L_CTRL);
}

Windows_Keyboard::Windows_Keyboard()
{
	initalize_codes();
	setup_action_layers();
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
		active_layer->handle_event(i, GetKeyState(i) & 0x8000);
	}
}



#endif
