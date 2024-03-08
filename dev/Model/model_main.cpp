#include "model_main.h"

#include <algorithm>
#include <mutex>
#include <thread>

#include "Interfaces/types/state.h"
#include "Threading/threading.h"

std::mutex model_mutex;
Timer model_timer;

Model* Model::instance = 0;

void model_step()
{
	Model::get_instance()->step();
}

Model::Model()
{
	model_controller_consumer = Message_Relay::get_instance()->register_consumer<Controller_Model_Command>();
	model_timer.reset_clock();
	model_task = Task("Model", 2, .2);
	step_actions = Command_List();
	Scheduler::get_instance()->add_system_task(model_step);
	Scheduler::get_instance()->add_cleanup_task([this] ()
												{
													model_timer.update_time();
													for(auto i = step_actions.begin(); i != step_actions.end(); )
													{
														if(i->command_run())
														{
															i->get_command()->complete_command();
															i = step_actions.erase(i);
														}
														else
														{
															i++;
														}
													}
													if(step_actions.size() > 0)
													{
														LOG_DEBUG("Model will run " + std::to_string(step_actions.size()) + " commands next frame");
													}
												} );
}

Model::~Model()
{
	Message_Relay::get_instance()->deregister_consumer(model_controller_consumer);
	step_actions.clear();
	node_list.clear();
}

Model* Model::get_instance()
{
	if(instance == 0)
	{
		instance = new Model();
	}
	return instance;
}

void Model::destroy_instance()
{
	if(instance != 0)
	{
		delete instance;
		instance = 0;
	}
}

Model::~Model()
{
	Message_Relay::get_instance()->deregister_consumer(model_controller_consumer);
	step_actions.clear();
	node_list.clear();
}

Model* Model::get_instance()
{
	if(instance == 0)
	{
		instance = new Model();
	}
	return instance;
}

void Model::destroy_instance()
{
	if(instance != 0)
	{
		delete instance;
		instance = 0;
	}
	LOG_INFO("Model Destroyed", "Model");
}

Node* Model::get_node(Node_Id id)
{
	Node* found_item = nullptr;
	for(int i = 0; i < node_list.size(); i++)
	{
		if(node_list[i].get_id() == id)
		{
			found_item = &node_list[i];
		}
	}
	if(found_item == nullptr)
	{
		found_item = &Node::invalid_node;
		LOG_ERROR("Node " + id + " not found", "Node");
	}
	return found_item;
}

void Model::create_node(NODE_TYPE type, Node_Id id)
{
	node_list.emplace_back(type, id);
}

void Model::remove_node(Node_Id id)
{
	auto i = node_list.begin();
	for(; i != node_list.end(); i++)
	{
		if((*i).get_id() == id)
		{
			break;
		}
	}
	node_list.erase(i);
}

void Model::connect_node(Node_Id id1, Node_Id id2)
{ 
	get_node(id1)->add_connection(get_node(id2));
	get_node(id2)->add_connection(get_node(id1));
}

void Model::disconnect_node(Node_Id id1, Node_Id id2)
{ 
	get_node(id1)->remove_connection(id2);
	get_node(id2)->remove_connection(id1);
}

Device* Model::get_device(Device_Label label)
{
	Device* found_device = nullptr;
	found_device = get_node(label.get_node_id())->get_device(label.get_device_id());

	return found_device;
}

template <typename T>
void mangle_model(T* command)
{
	state_interfaces::mangle_state(command);
}

void Model::step()
{
	for(auto i = Message_Relay::get_instance()->pop<Controller_Model_Command>(model_controller_consumer); i.is_valid(); i = Message_Relay::get_instance()->pop<Controller_Model_Command>(model_controller_consumer))
	{
		LOG_DEBUG("Model has recieved command " + i.get_command().get_command()->get_id_str());
		command_model(i.get_command());
	}
	int model_step_thread = 0;
	for(auto command = step_actions.begin(); command != step_actions.end(); command++)
	{
		model_step_thread++;
			Packed_Command& step_command = (*command);
			model_task.add_subtask(Cleaned_Task([&step_command, &model_step_thread] () mutable
								   {
									   if(step_command.command_run() == false)
									   {
										   LOG_DEBUG("Running command " + step_command.get_command()->get_id_str() + "on the model");
											mangle_model(step_command.get_command());
											step_command.run_command();
											step_command.get_command()->time_to_complete -= model_timer.get_elapsed_time();
									   }
									   model_step_thread--;
								   }));
		}

}

void Model::start_loop()
{
	model_running = true;
	LOG_INFO("Model added to scheduler", subsystem_name);
	Scheduler::get_instance()->add_task(&model_task);
}

void Model::stop_loop()
{
	LOG_INFO("Model Stopped", subsystem_name);
	model_running = false;
	model_task.set_persistence(false);
}



void Model::initalize_my_node(Node_Id id)
{
	my_node.initalize_local_control(id);
}

/**
 *  \cond
 */
struct compare
{
	Packed_Command key;
	compare(Packed_Command const& i) : key(i)
	{ }
	bool operator()(Packed_Command const& i)
	{
		Packed_Command comp = i;
		return key.get_command() == comp.get_command();
	}
};
/**
 * \endcond
 */


void Model::command_model(const Packed_Command& command)
{
	//OPTIMIZE
	auto found = std::find_if(step_actions.begin(), step_actions.end(), compare(command));
	if(found == step_actions.end() || step_actions.size() == 0)
	{
		step_actions.push_back(std::move(command));
	}
}