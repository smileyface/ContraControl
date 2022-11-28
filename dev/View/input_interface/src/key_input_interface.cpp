#include "../sys_interface/key_input_interface.h"
#include "Messaging/message_relay.h"

#include <vector>

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
KPI KEY::ENTER(47);
KPI KEY::L_SHIFT(48);
KPI KEY::L_CTRL(49);
KPI KEY::L_ALT(50);
KPI KEY::TAB(51);


std::vector<KPI> parse_input(char)
{
    return std::vector<KPI>();
}

Key_Press_Interface::Key_Press_Interface()
{
    on_press = [] ()
    { };
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
    { };
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

bool shifted = false;

//TODO: Implement this for buffered KPI conversion.
//char KPI_to_acsii(std::pair<KPI, KEY_STATE> key)
//{
//    char val = 0;
//    if(key.second == KEY_STATE::PRESSED)
//    {
//        if(!shifted)
//        {
//            if(key.first == KEY::A)
//                val = 'a';
//            else if(key.first == KEY::B)
//                val = 'b';
//            else if(key.first == KEY::C)
//                val = 'c';
//            else if(key.first == KEY::D)
//                val = 'd';
//            else if(key.first == KEY::E)
//                val = 'e';
//            else if(key.first == KEY::F)
//                val = 'f';
//            else if(key.first == KEY::G)
//                val = 'g';
//            else if(key.first == KEY::H)
//                val = 'h';
//            else if(key.first == KEY::I)
//                val = 'i';
//            else if(key.first == KEY::J)
//                val = 'j';
//            else if(key.first == KEY::K)
//                val = 'k';
//            else if(key.first == KEY::L)
//                val = 'l';
//            else if(key.first == KEY::M)
//                val = 'm';
//            else if(key.first == KEY::N)
//                val = 'n';
//            else if(key.first == KEY::O)
//                val = 'o';
//            else if(key.first == KEY::P)
//                val = 'p';
//            else if(key.first == KEY::Q)
//                val = 'q';
//            else if(key.first == KEY::R)
//                val = 'r';
//            else if(key.first == KEY::S)
//                val = 's';
//            else if(key.first == KEY::T)
//                val = 't';
//            else if(key.first == KEY::U)
//                val = 'u';
//            else if(key.first == KEY::V)
//                val = 'v';
//            else if(key.first == KEY::W)
//                val = 'w';
//            else if(key.first == KEY::X)
//                val = 'x';
//            else if(key.first == KEY::Y)
//                val = 'y';
//            else if(key.first == KEY::Z)
//                val = 'z';
//            else if(key.first == KEY::NUM_0)
//                val = '0';
//            else if(key.first == KEY::NUM_1)
//                val = '1';
//            else if(key.first == KEY::NUM_2)
//                val = '2';
//            else if(key.first == KEY::NUM_3)
//                val = '3';
//            else if(key.first == KEY::NUM_4)
//                val = '4';
//            else if(key.first == KEY::NUM_5)
//                val = '5';
//            else if(key.first == KEY::NUM_6)
//                val = '6';
//            else if(key.first == KEY::NUM_7)
//                val = '7';
//            else if(key.first == KEY::NUM_8)
//                val = '8';
//            else if(key.first == KEY::NUM_9)
//                val = '9';
//            else if(key.first == KEY::NUM_PAD::NUM_0)
//                val = '0';
//            else if(key.first == KEY::NUM_PAD::NUM_1)
//                val = '1';
//            else if(key.first == KEY::NUM_PAD::NUM_2)
//                val = '2';
//            else if(key.first == KEY::NUM_PAD::NUM_3)
//                val = '3';
//            else if(key.first == KEY::NUM_PAD::NUM_4)
//                val = '4';
//            else if(key.first == KEY::NUM_PAD::NUM_5)
//                val = '5';
//            else if(key.first == KEY::NUM_PAD::NUM_6)
//                val = '6';
//            else if(key.first == KEY::NUM_PAD::NUM_7)
//                val = '7';
//            else if(key.first == KEY::NUM_PAD::NUM_8)
//                val = '8';
//            else if(key.first == KEY::NUM_PAD::NUM_9)
//                val = '9';
//            else if(key.first == KEY::L_SHIFT)
//                val = 14;
//                shifted = true;
//        }
//        if(shifted)
//        {
//            if(key.first == KEY::A)
//                val = 'A';
//            else if(key.first == KEY::B)
//                val = 'B';
//            else if(key.first == KEY::C)
//                val = 'C';
//            else if(key.first == KEY::D)
//                val = 'D';
//            else if(key.first == KEY::E)
//                val = 'E';
//            else if(key.first == KEY::F)
//                val = 'F';
//            else if(key.first == KEY::G)
//                val = 'G';
//            else if(key.first == KEY::H)
//                val = 'H';
//            else if(key.first == KEY::I)
//                val = 'I';
//            else if(key.first == KEY::J)
//                val = 'J';
//            else if(key.first == KEY::K)
//                val = 'K';
//            else if(key.first == KEY::L)
//                val = 'L';
//            else if(key.first == KEY::M)
//                val = 'M';
//            else if(key.first == KEY::N)
//                val = 'N';
//            else if(key.first == KEY::O)
//                val = 'O';
//            else if(key.first == KEY::P)
//                val = 'P';
//            else if(key.first == KEY::Q)
//                val = 'Q';
//            else if(key.first == KEY::R)
//                val = 'R';
//            else if(key.first == KEY::S)
//                val = 'S';
//            else if(key.first == KEY::T)
//                val = 'T';
//            else if(key.first == KEY::U)
//                val = 'U';
//            else if(key.first == KEY::V)
//                val = 'V';
//            else if(key.first == KEY::W)
//                val = 'W';
//            else if(key.first == KEY::X)
//                val = 'X';
//            else if(key.first == KEY::Y)
//                val = 'Y';
//            else if(key.first == KEY::Z)
//                val = 'Z';
//            else if(key.first == KEY::NUM_0)
//                val = ')';
//            else if(key.first == KEY::NUM_1)
//                val = '!';
//            else if(key.first == KEY::NUM_2)
//                val = '@';
//            else if(key.first == KEY::NUM_3)
//                val = '#';
//            else if(key.first == KEY::NUM_4)
//                val = '$';
//            else if(key.first == KEY::NUM_5)
//                val = '%';
//            else if(key.first == KEY::NUM_6)
//                val = '^';
//            else if(key.first == KEY::NUM_7)
//                val = '&';
//            else if(key.first == KEY::NUM_8)
//                val = '*';
//            else if(key.first == KEY::NUM_9)
//                val = '(';
//            else if(key.first == KEY::NUM_PAD::NUM_0)
//                val = '0';
//            else if(key.first == KEY::NUM_PAD::NUM_1)
//                val = '1';
//            else if(key.first == KEY::NUM_PAD::NUM_2)
//                val = '2';
//            else if(key.first == KEY::NUM_PAD::NUM_3)
//                val = '3';
//            else if(key.first == KEY::NUM_PAD::NUM_4)
//                val = '4';
//            else if(key.first == KEY::NUM_PAD::NUM_5)
//                val = '5';
//            else if(key.first == KEY::NUM_PAD::NUM_6)
//                val = '6';
//            else if(key.first == KEY::NUM_PAD::NUM_7)
//                val = '7';
//            else if(key.first == KEY::NUM_PAD::NUM_8)
//                val = '8';
//            else if(key.first == KEY::NUM_PAD::NUM_9)
//                val = '9';
//        }
//    }
//    else if(key.second == KEY_STATE::RELEASED)
//    {
//        if(key.first == KEY::L_SHIFT)
//        {
//            shifted = false;
//            val = 15;
//        }
//            
//    }
//    return val;
//}

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