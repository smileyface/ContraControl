/*****************************************************************//**
 * \file   commander.h
 * \brief  
 * 
 * \author kason
 * \date   September 2023
 *********************************************************************/

#include <vector>
#include <stdarg.h>     /* va_list, va_start, va_arg, va_end */

#include "Interfaces/types/packed_command.h"
class Commander
{
public:
	static Commander* get_instance();
	template<typename T, typename... Args>
	Command* make_command(Args&&... a);
	void clean_list();
private:
	std::vector<Command*> command_list;
	Commander() = default;
	static Commander* instance;
};

template<typename T, typename ...Args>
inline Command* Commander::make_command(Args&&... a)
{
	command_list.emplace_back(new T(std::forward<Args>(a)...));
	return command_list[command_list.size()-1];
}
