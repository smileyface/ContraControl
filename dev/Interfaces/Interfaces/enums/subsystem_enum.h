/*******************************************************************//**
 * \file   subsystem_enum.h
 * \brief
 *
 * \author kason
 * \date   June 2022
 *********************************************************************/

#ifndef SUBSYSTEM_ENUM_DECL_TYPE
#define SUBSYSTEM_ENUM_DECL_TYPE

/** Enumerator of all the subsystems. */
enum class SUBSYSTEM_ID_ENUM
{
	INVALID,
	/** Enumerator for the controller */
	CONTROLLER,
	/** Enumerator for the model */
	MODEL,
	/** Enumerator for the Network */
	NETWORK,
	/** Enumerator for the View */
	VIEW_SUBSYSTEM,
	/** Enumerator for Testing */
	TEST
};

#endif