#ifndef COMMON_MENU_INTERFACE
#define COMMON_MENU_INTERFACE
#include<string>
#include<vector>

class Menu_Item
{
public:
    enum class Menu_Types
    {
        MENU,
        MENU_ITEM,
        SEPERATOR,

        INVALID
    };
    std::string text;
    Menu_Types flag;
    unsigned int id;


    Menu_Item()
    {
        text = "";
        flag = Menu_Types::INVALID;
        id = UINT32_MAX;
    }
    Menu_Item(std::string txt, Menu_Types flg, unsigned int _id)
    {
        text = txt;
        flag = flg;
        id = _id;
    }
};
class Menu : public Menu_Item
{
public:
    Menu() {};
    Menu(std::string txt)
    {
        flag = Menu_Types::MENU;
        text = txt;
    }
    virtual void add_to_menu(Menu_Item* menu)
    {
        menu_tree.push_back(menu);
    }
protected:
    std::vector<Menu_Item*> menu_tree;
};

#endif // !COMMON_MENU_INTERFACE