#include "../sys_interface/key_input_interface.h"

#include <vector>
#include <iostream>

KPI KEY::A;
KPI KEY::B;
KPI KEY::C;
KPI KEY::D;
KPI KEY::E;
KPI KEY::F;
KPI KEY::G;
KPI KEY::H;
KPI KEY::I;
KPI KEY::J;
KPI KEY::K;
KPI KEY::L;
KPI KEY::M;
KPI KEY::N;
KPI KEY::O;
KPI KEY::P;
KPI KEY::Q;
KPI KEY::R;
KPI KEY::S;
KPI KEY::T;
KPI KEY::U;
KPI KEY::V;
KPI KEY::W;
KPI KEY::X;
KPI KEY::Y;
KPI KEY::Z;
KPI KEY::NUM_0;
KPI KEY::NUM_1;
KPI KEY::NUM_2;
KPI KEY::NUM_3;
KPI KEY::NUM_4;
KPI KEY::NUM_5;
KPI KEY::NUM_6;
KPI KEY::NUM_7;
KPI KEY::NUM_8;
KPI KEY::NUM_9;
KPI KEY::NUM_PAD::NUM_0;
KPI KEY::NUM_PAD::NUM_1;
KPI KEY::NUM_PAD::NUM_2;
KPI KEY::NUM_PAD::NUM_3;
KPI KEY::NUM_PAD::NUM_4;
KPI KEY::NUM_PAD::NUM_5;
KPI KEY::NUM_PAD::NUM_6;
KPI KEY::NUM_PAD::NUM_7;
KPI KEY::NUM_PAD::NUM_8;
KPI KEY::NUM_PAD::NUM_9;


std::vector<KPI> parse_input(char)
{
    return std::vector<KPI>();
}

Key_Press_Interface::Key_Press_Interface()
{
    on_press = {};
    on_hold = {};
    on_release = {};
    val = -1;
    pressed = false;
}


void Key_Press_Interface::operator=(const int new_val)
{
    if(!pressed && new_val)
    {
        on_press();
        pressed = true;
    }
    else if(pressed && new_val)
    {
        on_hold();
    }
    else if(pressed && !new_val)
    {
        on_release();
        pressed = false;
    }
}

