/*****************************************************************//**
 * \file   predefined_layer.h
 * \brief  
 * 
 * \author kason
 * \date   November 2022
 *********************************************************************/
#ifndef PREDEFINED_ACTION_LAYER_H
#define PREDEFINED_ACTION_LAYER_H

#include "action_layer.h"

/**
 * Default action layers to be loaded in Action_Stack::setup_action_layers()
 */
namespace Predefined_Action_Layer
{
	enum
	{
		BUFFERED_INPUT_LAYER = 0,
		SIMPLE_BUFFERED_INPUT_LAYER = 1,
		END_OF_PREDEFINED = 2
	};
	/**
	 * Layer for buffered input. For things like reading strings in.
	 * \return Newly created layer
	 */
	Action_Layer buffered_input_layer();

	/**
	 * States for a Simple Input Layer
	 */
	namespace Simple_Input_Layer
	{
		extern bool terminated; ///<Has the Simple Input Layer been terminated.
		extern bool returned;   ///<Has the Simple Input Layer has successfully returned a string.
	}
	/**
	* Layer for buffered input. For things like reading strings in.
	* \return Newly created layer
	*/
	Action_Layer simple_buffered_input_layer();
}

#endif // 