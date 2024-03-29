/*****************************************************************//**
 * \file   model_main.h
 * \brief  Main brains for the model. DO NOT INCLUDE. Include a model_interface instead
 *
 * \author kason
 * \date   May 2021
 *********************************************************************/

#ifndef MODEL_MAIN_H
#define MODEL_MAIN_H
#include <atomic>

#include "system/timer.h"

#include "node/node.h"
#include "Messaging/message_relay.h"
#include "Threading/threading.h"

 /**
  * Main brain of the model. It keeps track of nodes and does actions such as looping, stepping through commands given from the Command_Interface, and sending nodes commands to run with devices.
  * \todo Include logging of model state.
  */
namespace model
{

	/**
	 * .The string of the namespace name. This is for locating Messages.
	 */
	static const char* subsystem_name = "Model";
	/**
	 Is the model looping
	 */
	extern std::atomic<bool> model_running;
	/**
	 The node where this model is running. Each node will have its own version of the model running on it.
	 */
	extern Node my_node;
	/**
	 Actions to be completed on this step of the loop.
	 */
	extern Command_List step_actions;
	/**
	 * Task to add model to the scheduler.
	 */
	extern Task model_task;
	/**
	 * Consumer for Controller messages
	 */
	extern Message_Consumer* model_controller_consumer;
	/**
	 * A container for all node pointers
	 */
	extern std::vector<Node> node_list;

	/**
	 * \brief Get node from list of known nodes by ID
	 * \param id Identifier of node returning
	 * \return A pointer to the desired Node
	 */
	Node* get_node(Node_Id);

	/**
	 * \brief Create Node in models map.
	 *
	 * This alerts the model to another nodes existance. It can interact with that node as it sees fit.
	 *
	 * \param type Type of node based off of Enum
	 * \param id Identifier of the node that model will refer to it as.
	 */
	void create_node(NODE_TYPE, Node_Id);

	/**
	 * \brief Destroy the Node in the models map.
	 * 
	 * \param id Identifier of the node to remove.
	 */
	void remove_node(Node_Id);

	/**
	 * \brief Add a connection for each node.
	 * 
	 * \param id1 An ID to connect id2 to
	 * \param id2 An ID to connect id1 to
	 */
	void connect_node(Node_Id id1, Node_Id id2);

	/**
	 * \brief Remove a connection for each node.
	 * 
	 * \param id1 An ID to remove connection from id2.
	 * \param id2 An ID to remove connection from id1.
	 */
	void disconnect_node(Node_Id id1, Node_Id id2);

	/**
	 * \brief A short circut for getting a device on a node using a node ID and device ID
	 *
	 * This is mainly used for testing devices, though should probably be removed.
	 * \param label Node and device combination to access device.
	 * \return Pointer to the called for device
	 * \todo remove this
	 */
	Device* get_device(Device_Label);

	/**
	 * \brief Start up.
	 *
	 * Reset clock to 0 elapsed. Get node id from list of declared id's. Declare node operational to network and see who else is online.
	 * \todo network
	 */
	void initalize();

	/**
	* \brief Run all commands lined up for this iteration of the loop.
	*
	* This is the main function of a loop.
	*/
	void step();

	/**
	 * \brief Start shutting down the model.
	 *
	 * Shuts down the Model execution loop.
	 */
	void stop_loop();

	/**
	 * \brief Start up the Model loop.
	 *
	 * Spawns a thread for the Model to be run in.
	 */
	void start_loop();

	/**
	 * \brief Delete all nodes and send out a 'Node Shut Down' notice on the network
	 * \todo create a Node_Shut_Down network message.
	 */
	void clean_up();

	/**
	 * Initalize the node that controls the local devices.
	 * \param id Name of the local node.
	 */
	void initalize_my_node(Node_Id id);

	/**
	 * .Add a command to the Model from the an interface.
	 * \param command The command to run.
	 */
	void command_model(const Packed_Command& command);
}
#endif 