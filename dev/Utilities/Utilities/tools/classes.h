/*******************************************************************//**
 * \file   classes.h
 * \brief  
 * 
 * \author kason
 * \date   July 2022
 *********************************************************************/
#ifndef CLASSES_TOOL_UTILITY
#define CLASSES_TOOL_UTILITY
template<typename Base, typename T>
inline bool instanceof(const T* ptr)
{
	return dynamic_cast<const Base*>(ptr) != nullptr;
}

#endif