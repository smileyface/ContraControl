/*******************************************************************//**
 * \file   network_interface.h
 * \brief
 *
 * \author kason
 * \date   March 2022
 *********************************************************************/
#ifndef NETWORK_EXTERNAL_INTERFACE
#define NETWORK_EXTERNAL_INTERFACE

 /** Interfaces to the Network */
class Network_Interfaces
{
public:
	class Model_Interface;
	class View_Interface;
};

/**
 Network interface to the Model.
 */
class Network_Interfaces::Model_Interface
{ };

/**
 * Network interface to the View.
 */
class Network_Interfaces::View_Interface
{
	std::string query_for_interfaces(std::vector<std::string> interface_list);
};

#endif
