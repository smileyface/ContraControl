/*****************************************************************//**
 * \file   device_label.h
 * \brief  
 * 
 * \author kason
 * \date   June 2021
 *********************************************************************/
#ifndef INTERFACE_TYPE_DEVICE_LABEL
#define INTERFACE_TYPE_DEVICE_LABEL

#include <string>	//std::string
#include <vector>   //std::vector

/*!
* Code for an invalid device.
*/
const uint16_t INVALID_DEVICE = UINT16_MAX;

/**
 An identifier object mainly for readability
 */
typedef uint16_t Device_Id;
/**
A name for a device
 */
typedef std::string Device_Name;


/**
 List of device IDs. For use with the Device_Id_Map.
 */
typedef std::vector<Device_Id> Device_List;

/**
 An Identifier for a node.
 */
typedef std::string Node_Id;

/**
 A struct to feed the device factory.
 */
typedef std::pair<Device_Id, Device_Name> Device_Creator;

/**
 Struct to locate a device.
 */
class Device_Label
{
public:
	Device_Label() { device_label = INVALID_DEVICE; };
	/**
	 Constructor that takes a Node_Id and Device_Id.
	 \param node Id of the node that contains the device you're looking for.
	 \param device Id of the device that you're looking for.
	 */
	Device_Label(Node_Id node, Device_Id device)
	{
		node_label = node;
		device_label = device;
	}
	/**
	 Compare device ID and node ID
	 \param rhs right hand Device_Label
	 \return if labels are the same.
	 */
	bool operator==(const Device_Label& rhs)
	{
		return rhs.device_label == device_label && rhs.node_label == node_label;
	}
	/**
	 Get ID of the node.
	 \return Id of the node.
	 */
	Node_Id get_node_id()
	{
		return node_label;
	}
	/**
	 Get the device ID.
	 \return Id of the device
	 */
	Device_Id get_device_id()
	{
		return device_label;
	}
private:
	Node_Id node_label;
	Device_Id device_label;
};

#endif