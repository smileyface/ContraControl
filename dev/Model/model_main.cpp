#include "model_main.h"

#include <algorithm>
#include <thread>
#include <mutex>

#include "Interfaces/types/state.h"
#include "Threading/threading.h"

std::mutex model_mutex;

Timer model_timer;
std::atomic<bool> model::model_running;
Command_List model::step_actions;
std::vector<Node> model::node_list;
Task model::model_task;
Message_Consumer* model::model_controller_consumer;

Node model::my_node;

void model::initalize()
{
	model_controller_consumer = Message_Relay::get_instance()->register_consumer<Controller_Model_Command>();
	model_timer.reset_clock();
	model_task = Task("Model", 2, .2);
	step_actions = Command_List();
	Scheduler::get_instance()->add_system_task(model::step);
	Scheduler::get_instance()->add_cleanup_task([] ()
												{
													model_timer.update_time();
													std::lock_guard<std::mutex> lock(model_mutex);
													for(auto i = model::step_actions.begin(); i != model::step_actions.end(); )
													{
														if(i->command_run())
														{
															i->get_command()->complete_command();
															i = model::step_actions.erase(i);
														}
														else
														{
															i++;
														}
													}
													if(model::step_actions.size() > 0)
													{
														printf("Model will run %d commands next frame\n");
													}
												} );
}

Node* model::get_node(Node_Id id)
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
		LOG_ERROR("Node " + id + " not found", "Node");
	}
	return found_item;
}

void model::create_node(NODE_TYPE type, Node_Id id)
{
	node_list.emplace_back(Node(type, id));
}

void model::remove_node(Node_Id id)
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

void model::connect_node(Node_Id id1, Node_Id id2)
{ 
	get_node(id1)->add_connection(get_node(id2));
	get_node(id2)->add_connection(get_node(id1));
}

void model::disconnect_node(Node_Id id1, Node_Id id2)
{ 
	get_node(id1)->remove_connection(id2);
	get_node(id2)->remove_connection(id1);
}

Device* model::get_device(Device_Label label)
{
	return model::get_node(label.get_node_id())->get_device(label.get_device_id());
}

template <typename T>
void mangle_model(T* command)
{
	state_interfaces::mangle_state(command);
}

void model::step()
{
	for(auto i = Message_Relay::get_instance()->pop<Controller_Model_Command>(model_controller_consumer); i.is_valid(); i = Message_Relay::get_instance()->pop<Controller_Model_Command>(model_controller_consumer))
	{
		LOG_DEBUG("Model has recieved command " + i.get_command().get_command()->get_id_str());
		command_model(i.get_command());
	}
	int model_step_thread = 0;
	for(auto command = model::step_actions.begin(); command != model::step_actions.end(); command++)
	{
		model_step_thread++;
		if(command->command_run() == false)
		{
			model_task.add_subtask(Cleaned_Task([command, &model_step_thread] () mutable
								   {
									   LOG_DEBUG("Running command %d on the model"+ command->get_command()->get_id_str());
									   try
									   {
										   std::lock_guard<std::mutex> lock(model_mutex);
										   mangle_model(command->get_command());
										   command->run_command();
										   command->get_command()->time_to_complete -= model_timer.get_elapsed_time();
									   }
									   catch(std::exception& e)
									   {
										   std::string what = e.what();
										   LOG_ERROR("Exception thrown " + what, "Model");
										   model_task.exception(std::current_exception());
									   }
									   model_step_thread--;
								   }));
		}

	}
}

void model::start_loop()
{
	model_running = true;
	LOG_INFO("Model added to scheduler", subsystem_name);
	Scheduler::get_instance()->add_task(&model::model_task);
}

void model::stop_loop()
{
	LOG_INFO("Model Stopped", subsystem_name);
	model_running = false;
	model_task.set_persistence(false);
}

void model::clean_up()
{
	Message_Relay::get_instance()->deregister_consumer(model_controller_consumer);
	step_actions.clear();
	node_list.clear();
}

void model::initalize_my_node(Node_Id id)
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


void model::command_model(const Packed_Command& command)
{
	//OPTIMIZE

	auto found = std::find_if(model::step_actions.begin(), model::step_actions.end(), compare(command));
	if(found == model::step_actions.end() || model::step_actions.size() == 0)
	{
		model::step_actions.push_back(std::move(command));
	}
}