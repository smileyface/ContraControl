#include "../action_layer/input_buffer.h"

Keyboard_Input_Buffer::Keyboard_Input_Buffer()
{ 
    input_buffer = std::vector<std::pair<KPI, KEY_STATE>>();
}

Keyboard_Input_Buffer::~Keyboard_Input_Buffer()
{ }

bool shifted = false;

char get_special_character_num_line(KPI key)
{
    char character = 0;
    if(key == KEY::NUM_0)
    {
        character = 41;
    }
    else if(key == KEY::NUM_1)
    {
        character = 33;
    }
    else if(key == KEY::NUM_2)
    {
        character = 64;
    }
    else if(key == KEY::NUM_3)
    {
        character = 35;
    }
    else if(key == KEY::NUM_4)
    {
        character = 36;
    }
    else if(key == KEY::NUM_5)
    {
        character = 37;
    }
    else if(key == KEY::NUM_6)
    {
        character = 94;
    }
    else if(key == KEY::NUM_7)
    {
        character = 38;
    }
    else if(key == KEY::NUM_8)
    {
        character = 42;
    }
    else if(key == KEY::NUM_9)
    {
        character = 40;
    }
    character -= key.index();
    return character;
}

char get_ascii_chart_conversion(KPI key, KEY_STATE state)
{
    char ascii_chart_conversion = 0;
    if(key >= KEY::A && key <= KEY::Z)
    {
        if(state == KEY_STATE::PRESSED)
        {
            ascii_chart_conversion = 65 - KEY::A.index();
            if(!shifted)
            {
                ascii_chart_conversion += 32;
            }
        }
    }
    else if(key >= KEY::NUM_0 && key <= KEY::NUM_9)
    {
        if(state == KEY_STATE::PRESSED)
        {
            if(shifted)
                ascii_chart_conversion = get_special_character_num_line(key);
            else
                ascii_chart_conversion = 48 - KEY::NUM_0.index();
        }
    }
    else if(key >= KEY::NUM_PAD::NUM_0 && key <= KEY::NUM_PAD::NUM_9)
    {
        if(state == KEY_STATE::PRESSED)
            ascii_chart_conversion = 48 - KEY::NUM_PAD::NUM_0.index();
    }
    return ascii_chart_conversion;
}



char KPI_to_ascii(std::pair<KPI, KEY_STATE> key)
{
    char ascii_chart_conversion = get_ascii_chart_conversion(key.first, key.second);
    char val = 0;
    if(ascii_chart_conversion > 0)
    {
        val = key.first.index() + ascii_chart_conversion;
    }

    if(key.first == KEY::L_SHIFT)
    {
        if(key.second == KEY_STATE::PRESSED)
            shifted = true;
        if(key.second == KEY_STATE::RELEASED)
            shifted = false;
    }

    if(key.first == KEY::ENTER && key.second == KEY_STATE::PRESSED)
    {
        val = 13;
    }
    else if(key.first == KEY::TAB && key.second == KEY_STATE::PRESSED)
    {
        val = 9;
    }
    return val;
}

std::string Keyboard_Input_Buffer::get_buffer()
{
    std::string return_value = "";
    for(auto i : input_buffer)
    {
        char current = KPI_to_ascii(i);
        if(current != 0)
        {
            if(current == 13)
            {
            #ifdef WIN32
                return_value += "\r\n";
            #elif __linux__
                return_value += "\n";
            #endif
            }
            else if(current == 9)
            {
                return_value += "\t";
            }
            else
            {
                return_value += current;
            }
        }
    }
    input_buffer.clear();
    return return_value;
}


void Keyboard_Input_Buffer::add(KPI key, KEY_STATE state)
{ 
    input_buffer.push_back(std::make_pair(key, state));
}

void Keyboard_Input_Buffer::clear()
{
    input_buffer.clear();
}
