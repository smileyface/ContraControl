#include <thread>
#include <mutex>

#include "messages.h"
#include "messages/node_communication.h"

#include "network_main.h"
#ifdef _WIN32
#include "system_interfaces/windows_network_interface.h"
#endif
#ifdef __linux__
#include "system_interfaces/linux_network_interface.h"
#endif

/*Externs*/
Network_Interface* network::network_interface;
Task network::network_task;

bool network_running = false;
std::mutex network_mutex;

void network::init_network_interfaces()
{
	instantiate_interface();
	network_interface->initalize();
	generate_crc_table();

	Scheduler::get_instance()->add_system_task([] ()
											   {
													if(network::network_interface->server())
													{
														   
													}
													else if(network::network_interface->client())
													{
														network::network_task.add_subtask(Cleaned_Task(node_messages::network_client_state_machine));
													}
											   });
}

void network::instantiate_interface()
{
#ifdef _WIN32
	network::network_interface = new Windows_Network_Interface();
#endif // IS_WIN32
#ifdef __linux__
	network::network_interface = new Linux_Network_Interface();
#endif //__linux__
#ifdef _MAC
	//For now, we'll just use the linux interface.
	network::network_interface = new Linux_Network_Interface();
#endif // _MAC
}

void network::init_network_interfaces(std::string interfaces)
{
	init_network_interfaces();
	network_interface->clean_up();
	network_interface->set_interface(interfaces);
	network_interface->initalize();
}

void client_loop()
{
	//call_and_response(NODE_HELLO, NODE_ACK, 2);
	while(network_running)
	{
		node_messages::network_client_state_machine();
	}
}

void server_loop()
{
	while(network_running)
	{
		//listen on Broadcast for NODE_HELLO
		//Once found, Send NODE_ACK
	}
}

void network::teardown_network_interfaces()
{
	network_running = false;
	network_task.set_persistence(false);
	if(network::network_interface != nullptr)
	{
		network::network_interface->clean_up();
		network::network_interface = nullptr;
	}
	LOG_INFO("Network Interface torndown", "Network");
}

Network_Message network::listen_for_message(Connection_Id src, MESSAGES listen_for)
{
	return Network_Message();
}

void network::start_server()
{
	LOG_INFO("Starting Server Loop", "Server Loop");
	network::network_interface->set_server();
	Scheduler::get_instance()->add_task(&network::network_task);
	network_running = true;
}

void network::start_client()
{
	LOG_INFO("Starting Client Loop", "Client Loop");
	network::network_interface->set_client();
	Scheduler::get_instance()->add_task(&network::network_task);
	network_running = true;
}

void network::set_interface(std::string i)
{
	network_interface->set_interface(i);
}

void network::send_message(Connection_Id dest, Network_Message outgoing)
{
	Packed_Message packed_outgoing(outgoing);
	network_interface->send(dest, reinterpret_cast<char*>(packed_outgoing.get_packet().data()));
	LOG_DEBUG("Sending message " + get_message_type_string(packed_outgoing.get_message_type()) + " to " + dest);
}