#include "keyboard_interface_utilities.h"

Test_Keyboard_Interface::Test_Keyboard_Interface()
{
	read_a_character = false;
	initalize_codes();
	action_stack.setup_action_layers();
}

void Test_Keyboard_Interface::initalize_codes()
{ 
	master_code_map[1] = KEY::A;
	master_code_map[2] = KEY::B;
	master_code_map[3] = KEY::C;
	master_code_map[4] = KEY::D;
	master_code_map[5] = KEY::E;
	master_code_map[6] = KEY::F;
	master_code_map[7] = KEY::G;
	master_code_map[8] = KEY::H;
	master_code_map[9] = KEY::I;
	master_code_map[10] = KEY::J;
	master_code_map[11] = KEY::K;
	master_code_map[12] = KEY::L;
	master_code_map[13] = KEY::M;
	master_code_map[14] = KEY::N;
	master_code_map[15] = KEY::O;
	master_code_map[16] = KEY::P;
	master_code_map[17] = KEY::Q;
	master_code_map[18] = KEY::R;
	master_code_map[19] = KEY::S;
	master_code_map[20] = KEY::T;
	master_code_map[21] = KEY::U;
	master_code_map[22] = KEY::V;
	master_code_map[23] = KEY::W;
	master_code_map[24] = KEY::X;
	master_code_map[25] = KEY::Y;
	master_code_map[26] = KEY::Z;
	master_code_map[27] = KEY::NUM_0;
	master_code_map[28] = KEY::NUM_1;
	master_code_map[29] = KEY::NUM_2;
	master_code_map[30] = KEY::NUM_3;
	master_code_map[31] = KEY::NUM_4;
	master_code_map[32] = KEY::NUM_5;
	master_code_map[33] = KEY::NUM_6;
	master_code_map[34] = KEY::NUM_7;
	master_code_map[35] = KEY::NUM_8;
	master_code_map[36] = KEY::NUM_9;
	master_code_map[37] = KEY::NUM_PAD::NUM_0;
	master_code_map[38] = KEY::NUM_PAD::NUM_1;
	master_code_map[39] = KEY::NUM_PAD::NUM_2;
	master_code_map[40] = KEY::NUM_PAD::NUM_3;
	master_code_map[41] = KEY::NUM_PAD::NUM_4;
	master_code_map[42] = KEY::NUM_PAD::NUM_5;
	master_code_map[43] = KEY::NUM_PAD::NUM_6;
	master_code_map[44] = KEY::NUM_PAD::NUM_7;
	master_code_map[45] = KEY::NUM_PAD::NUM_8;
	master_code_map[46] = KEY::NUM_PAD::NUM_9;
	master_code_map[47] = KEY::ENTER;
	master_code_map[48] = KEY::L_SHIFT;
	master_code_map[49] = KEY::L_ALT;
	master_code_map[50] = KEY::L_CTRL;
	master_code_map[51] = KEY::TAB;

	for(Keyboard_Code_Map::iterator i = master_code_map.begin(); i != master_code_map.end(); i++)
	{
		i->second.set_code(i->first);
	}
}

void Test_Keyboard_Interface::connect_to_keyboard()
{
	keyboard_present = true;
}

void Test_Keyboard_Interface::readEv()
{
	read_a_character = true;
}
