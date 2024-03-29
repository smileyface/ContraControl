/*****************************************************************//**
 * \file   console.h
 * \brief
 *
 * \author kason
 * \date   February 2022
 *********************************************************************/

#ifndef CONSOLE_DISPLAY_VIEW_H
#define CONSOLE_DISPLAY_VIEW_H

#include "format.h"

 /**
  * Interface for Console UI.
  */
class Console_Format : public Format
{
public:
	void initalize();
	/**
	 * Add a new view to the format.
	 * \param view Type of view to add.
	 * \return Pointer to the newly created view
	 */
	View* add_view(VIEW_TYPE_ENUM view);


protected:
	void step();
};

#endif