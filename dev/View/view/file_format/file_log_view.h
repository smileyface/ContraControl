/*****************************************************************//**
 * \file   file_log_view.h
 * \brief  
 * 
 * \author kason
 * \date   November 2023
 *********************************************************************/

#ifndef VIEW_FILE_LOG_VIEW
#define VIEW_FILE_LOG_VIEW

#include "file_view.h"
#include "../view_type/log_view_type.h"

#include <fstream>

/** View for Log messages to be written to files */
class File_Log_View : public File_View, public Log_View_Type
{
public:
	File_Log_View();
	virtual ~File_Log_View();

	void on_create() override;
	void on_refresh() override;
	void on_paint() override;
	void on_display() override;
	void on_destroy() override;

	// Inherited via File_View
	bool is_stale() override;
	bool quit() override;

	/**
	 * \return The name of the Log file.
	 */
	std::string get_file_name();
private:
	std::ofstream log_file;
	std::string file_name;
	std::string get_time_str();

};
#endif // !VIEW_FILE_LOG_VIEW
