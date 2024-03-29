/*****************************************************************//**
 * \file   view_type_enum.h
 * \brief
 *
 * \author kason
 * \date   February 2022
 *********************************************************************/

#ifndef VIEW_TYPE_ENUM_H
#define VIEW_TYPE_ENUM_H

 /**
  * Identifier for View Type
  */
enum class VIEW_TYPE_ENUM
{
	/** A System View Type. Mainly for System_Messages */
	LOG,
	/** An optional popup. */
	POPUP_OPTION
};

/**
 * Return view type as string.
 * \param view_type Enumerator to be coverted to string.
 * \return Enumeration of view type as a c string.
 */
char* get_view_type_enum_as_string(VIEW_TYPE_ENUM view_type);

#endif
