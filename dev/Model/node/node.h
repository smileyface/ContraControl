/*****************************************************************//**
 * \file   node.h
 * \brief  
 * 
 * \author kason
 * \date   May 2021
 *********************************************************************/
#ifndef MODEL_NODE_H
#define MODEL_NODE_H

#include "../device.h"
#include "Interfaces/enums/node_type.h"

/**
 A node, which represents a computer, such as a Raspberry Pi, or other command device. 
 */
class Node
{
public:
	Node();
	/**
	 Create a node instance by giving it a type.

	 \param type The type of node.
	 */
	Node(NODE_TYPE type);

	/**
	 Create a node instance by giving it a type and a name.

	 \param type The type of node.
	 */
	Node(NODE_TYPE type, Node_Id id);

	~Node();
	/**
	 Get ready to destroy node.
	 */
	void clear_node();
	/**
	 Add a Device to the node. 

	 \param device A creator struct that will be used to make the device.
	 */
	void register_device(Device_Creator device);

	/**
	 * Remove a device from the node.
	 * \param label A label to the device that needs removal.
	 */
	void remove_device(Device_Id label);
	/**
	 Return a pointer to a device requested by Device_Id

	 \param device An Id struct that points to a specific device.
	 \return Pointer to the device.
	 \throws DeviceNotFoundException if node does not know about the device
	 */
	Device* get_device(Device_Id device);
	/**
	 Return a pointer to a device requested by Device_Name
	 \param device A name that points to a specific device.
	 \return Pointer to the device.
	 \throws DeviceNotFoundException if node does not know about the device
	 */
	Device* get_device(Device_Name device);
	/**
	 Return all devices that the node knows about
	 \return The list of Devices.
	 */
	Device_List get_devices();
	/**
	 Make the identified node the local node.
	 \param id The id of the local node
	 */
	void initalize_local_control(Node_Id id);

	/**
	 * Get the node connected to the local node.
	 * \param id Id of the node to get.
	 * \return Pointer to the connected node.
	 * \throw NodeNotFoundException If node is not a known connection.
	 */
	Node* get_connection(Node_Id id);

	/**
	 * Add node to known connections.
	 * \param type Type of the node.
	 * \param id The id of the node on the system.
	 */
	void add_connection(NODE_TYPE type, Node_Id id);

	/**
	 * Remove a connection to a node.
	 * \param id The ID to the node that needs removing
	 */
	void remove_connection(Node_Id id);

	/**
	 * Get the id of the local node.
	 * \return The id.
	 */
	Node_Id get_id();
private:
	std::map<Node_Id, Node*> connections;
	Device_Id_Map devices;
	std::map<Device_Name, Device_Id> name_to_id_map;
	NODE_TYPE my_type;
	Device_Id id_pool;
	Node_Id my_id;
};

#endif // !MODEL_NODE_H
