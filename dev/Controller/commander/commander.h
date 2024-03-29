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
#include "Messaging/message_relay.h"

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
	 * Singleton destroy instance
	 */
	static void destroy_instance();
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

	/**
	 * \return Number of commands not executed yet.
	 */
	int get_number_of_commands();

	/**
	 * \return If the command is still on the commander.
	 * 
	 * \param command Command to verify the existance of.
	 */
	bool is_command_still_around(Command* command);

private:
	std::vector<Command*> command_list;
	Commander() = default;
	~Commander();
	static Commander* instance;
};

template<typename T, typename ...Args>
inline Command* Commander::make_command(Args&&... a)
{
	command_list.emplace_back(new T(std::forward<Args>(a)...));
	LOG_DEBUG("Adding command " + command_list[command_list.size() - 1]->get_id_str() + " to commander." );
	return command_list[command_list.size()-1];
}
