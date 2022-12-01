#include "../action_layer/input_buffer.h"

Keyboard_Input_Buffer::Keyboard_Input_Buffer()
{ 
    input_buffer = std::vector<std::pair<KPI, KEY_STATE>>();
}

Keyboard_Input_Buffer::~Keyboard_Input_Buffer()
{ }

bool shifted = false;

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
    if(key >= KEY::NUM_0 && key <= KEY::NUM_9)
    {
        if(state == KEY_STATE::PRESSED)
            ascii_chart_conversion = 48 - KEY::NUM_0.index();
    }
    if(key >= KEY::NUM_PAD::NUM_0 && key <= KEY::NUM_PAD::NUM_9)
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

    if(key.first == KEY::L_SHIFT)
    {
        if(key.second == KEY_STATE::PRESSED)
            shifted = true;
        if(key.second == KEY_STATE::RELEASED)
            shifted = false;
    }

    if(ascii_chart_conversion > 0)
    {
        val = key.first.index() + ascii_chart_conversion;
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
            return_value += current;
        }
    }
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
