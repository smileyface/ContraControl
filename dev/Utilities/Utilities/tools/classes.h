/*******************************************************************//**
 * \file   classes.h
 * \brief  
 * 
 * \author kason
 * \date   July 2022
 *********************************************************************/
#ifndef CLASSES_TOOL_UTILITY
#define CLASSES_TOOL_UTILITY
/**
 * See if T is an instance of Base
 * \param ptr Instance to check on.
 * \return if the instance is of base
 */
template<typename Base, typename T>
inline bool instanceof(const T* ptr)
{
	return dynamic_cast<const Base*>(ptr) != nullptr;
}

#endif