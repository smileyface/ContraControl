/*****************************************************************//**
 * \file   file_view.h
 * \brief  
 * 
 * \author kason
 * \date   November 2023
 *********************************************************************/

#ifndef VIEW_FILE_VIEW
#define VIEW_FILE_VIEW

#include "../view.h"
#include <string>

/** A view to read and write to a file. */
class File_View : public View
{
public:
	File_View();
	~File_View();

	virtual void on_create();
	virtual void on_destroy();
protected:
	/** Message to "paint" (display) into the console. As the console is acsii only, this is a string */
	std::string painted_message;
private:
};

#endif
