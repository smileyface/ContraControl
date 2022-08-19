#include "../sys_interface/key_input_interface.h"

#include <vector>
#include <iostream>

KPI KEY::A(1);
KPI KEY::B(2);
KPI KEY::C(3);
KPI KEY::D(4);
KPI KEY::E(5);
KPI KEY::F(6);
KPI KEY::G(7);
KPI KEY::H(8);
KPI KEY::I(9);
KPI KEY::J(10);
KPI KEY::K(11);
KPI KEY::L(12);
KPI KEY::M(13);
KPI KEY::N(14);
KPI KEY::O(15);
KPI KEY::P(16);
KPI KEY::Q(17);
KPI KEY::R(18);
KPI KEY::S(19);
KPI KEY::T(20);
KPI KEY::U(21);
KPI KEY::V(22);
KPI KEY::W(23);
KPI KEY::X(24);
KPI KEY::Y(25);
KPI KEY::Z(26);
KPI KEY::NUM_0(27);
KPI KEY::NUM_1(28);
KPI KEY::NUM_2(29);
KPI KEY::NUM_3(30);
KPI KEY::NUM_4(31);
KPI KEY::NUM_5(32);
KPI KEY::NUM_6(33);
KPI KEY::NUM_7(34);
KPI KEY::NUM_8(35);
KPI KEY::NUM_9(36);
KPI KEY::NUM_PAD::NUM_0(37);
KPI KEY::NUM_PAD::NUM_1(38);
KPI KEY::NUM_PAD::NUM_2(39);
KPI KEY::NUM_PAD::NUM_3(40);
KPI KEY::NUM_PAD::NUM_4(41);
KPI KEY::NUM_PAD::NUM_5(42);
KPI KEY::NUM_PAD::NUM_6(43);
KPI KEY::NUM_PAD::NUM_7(44);
KPI KEY::NUM_PAD::NUM_8(45);
KPI KEY::NUM_PAD::NUM_9(46);


std::vector<KPI> parse_input(char)
{
    return std::vector<KPI>();
}

Key_Press_Interface::Key_Press_Interface()
{
    on_press = [] ()
    {
        printf("Presses");
        fflush(stdout);
    };
    on_release = [] ()
    { };
    on_hold = [] ()
    { };
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

Key_Press_Interface::Key_Press_Interface(int index)
{ 
    on_press = [] ()
    {
        printf("indexed button pressed");
        fflush(stdout);
    };
    on_release = [] ()
    { };
    on_hold = [] ()
    { };
    val = -1;
    pressed = false;
    index_ = index;
}

bool Key_Press_Interface::operator==(const Key_Press_Interface check_val)
{
    if(index_ < 0)
    {
        return false;
    }
    return index_ == check_val.index_;
}
