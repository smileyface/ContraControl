#include "../sys_interface/key_input_interface.h"
#include "Messaging/message_relay.h"

#include <vector>
#include <Windows.h>

KPI INVALID;
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
KPI KEY::ENTER;
KPI KEY::L_SHIFT;
KPI KEY::L_CTRL;
KPI KEY::L_ALT;
KPI KEY::TAB;

int key_index = 0;

Key_Press_Interface::Key_Press_Interface()
{
    on_press = [] ()
    { };
    on_release = [] ()
    { };
    on_hold = [] ()
    { };
    val = -1;
    pressed = KEY_STATE::RELEASED;
    index_ = key_index;
    key_index++;
}

void Key_Press_Interface::operator=(const int new_val)
{
    if(pressed == KEY_STATE::RELEASED && new_val)
    {
        on_press();
        pressed = KEY_STATE::PRESSED;
    }
    else if(pressed == KEY_STATE::PRESSED && new_val)
    {
        on_hold();
        pressed = KEY_STATE::HELD;
    }
    else if(!(pressed == KEY_STATE::RELEASED) && !new_val)
    {
        on_release();
        pressed = KEY_STATE::RELEASED;
    }
}

bool Key_Press_Interface::operator==(const Key_Press_Interface check_val)
{
    if(index_ < 0)
    {
        return false;
    }
    return index_ == check_val.index_;
}

bool Key_Press_Interface::operator<=(const Key_Press_Interface check_val)
{
    return index_ <= check_val.index_;
}

bool Key_Press_Interface::operator>=(const Key_Press_Interface check_val)
{
    return index_ >= check_val.index_;
}


int Key_Press_Interface::index()
{
    return index_;
}

void Key_Press_Interface::set_code(char value)
{
    code = value;
}

char Key_Press_Interface::get_code()
{
    return code;
}

KEY_STATE Key_Press_Interface::get_state()
{
    return pressed;
}
