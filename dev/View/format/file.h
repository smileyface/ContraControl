/*****************************************************************//**
 * \file   file.h
 * \brief  
 * 
 * \author kason
 * \date   November 2023
 *********************************************************************/

#ifndef FILE_DISPLAY_VIEW_H
#define FILE_DISPLAY_VIEW_H

#include "format.h"

/**
 * An interface to write to a file.
 */
class File_Format : public Format
{
public:
	void initalize();
	/**
	 * Add a new view to the format.
	 * \param view Type of view to add.
	 * \return Pointer to the newly created view
	 */
	Device_View* add_view(VIEW_TYPE_ENUM view_type);


protected:
	void step();
};
#endif // !FILE_DISPLAY_VIEW_H
