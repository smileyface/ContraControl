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

/**
 * An interface for Command memory management.
 */
class Commander
{
public:
	/**
	 * Singleton get instance
	 * \return Singleton instance
	 */
	static Commander* get_instance();
	/**
	 * Create a new command and put it on the command_list
	 * \tparam T Type of Command to create
	 * \param a Argument list for Command construction.
	 * \return A pointer to the newly created Command.
	 */
	template<typename T, typename... Args>
	Command* make_command(Args&&... a);
	/**
	 * Destruct and remove all Commands on the command_list that are marked as completed.
	 */
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
