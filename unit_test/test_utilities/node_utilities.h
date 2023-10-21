#ifndef TESTING_NODE_UTILITIES
#define TESTING_NODE_UTILITIES
#include "../../dev/Model/node/node.h"

namespace node_utilities
{
	extern Node_Id local_node_handle;
	void start_test_environment();
    /*
	Create node in the model.
	*/
	void create_node(Node_Id id);
	/**
	 Remove a node from the model
	 */
	void remove_node(Node_Id id);

	/**
	 * Connect two nodes together.
	 */
	void connect_node(Node_Id id1, Node_Id id2);

	/**
	 * Remove connection from two nodes.
	 */
	void disconnect_node(Node_Id id1, Node_Id id2);

	/*
	Add a device to the given node in the model. Returns device name.
	*/
	Device_Label add_device(Node_Id id, Device_Creator creator);

	void setup_node(Node_Id id);
}

#endif