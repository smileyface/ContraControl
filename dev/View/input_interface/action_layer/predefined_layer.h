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
	/**
	 * Layer for buffered input. For things like reading strings in.
	 * \return Newly created layer
	 */
	Action_Layer buffered_input_layer();
}

#endif // 