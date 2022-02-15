/*****************************************************************//**
 * \file   save_reader.h
 * \brief Not implemented
 *
 * \author kason
 * \date   February 2022
 *********************************************************************/

#ifndef SAVE_READER_H
#define SAVE_READER_H


#include "../Interfaces/model_interface.h"
#include "../Interfaces/controller_interface.h"

namespace file_reader {
	/**
	 * Not implemented
	 */
	std::function<void()>read_devices = []() {
	};
	/**
	 * Not implemented
	 */
	std::function<void()>read_commands = []() {
	};

	/**
	 * Not implemented
	 */
	std::function<void()>read_file = []() {
		file_reader::read_devices();
		file_reader::read_commands();
	};


}
#endif // !SAVE_READER_H
