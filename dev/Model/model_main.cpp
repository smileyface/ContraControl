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
Task model::model_task;
Message_Consumer* model::model_controller_consumer;

Node model::my_node;

void model::initalize()
{
	model_controller_consumer = Message_Relay::get_instance()->register_consumer<Controller_Model_Command>();
	model_timer.reset_clock();
	initalize_my_node("LOCAL");
	model_task = Task("Model", 2, .2);
	Scheduler::get_instance()->add_system_task(model::step);
	Scheduler::get_instance()->add_cleanup_task([] ()
												{
													model_timer.update_time();
													for(auto i = model::step_actions.begin(); i != model::step_actions.end(); )
													{
														if(i->run)
														{
															i = model::step_actions.erase(i);
														}
														else
														{
															i++;
														}
													}
												} );
}

Node* model::get_node(Node_Id id)
{
	if(my_node.get_id() == id)
	{
		return &my_node;
	}
	return my_node.get_connection(id);
}

void model::create_node(NODE_TYPE type, Node_Id id)
{
	my_node.add_connection(type, id);
}

Device* model::get_device(Device_Label label)
{
	return model::get_node(label.get_node_id())->get_device(label.get_device_id());
}

template <typename T>
void mangle_model(T* command, Device* device)
{
	state_interfaces::mangle_state(command, device);
}

void model::step()
{
	for(auto i = Message_Relay::get_instance()->pop<Controller_Model_Command>(model_controller_consumer); i.is_valid(); i = Message_Relay::get_instance()->pop<Controller_Model_Command>(model_controller_consumer))
	{
		command_model(i.get_command());
	}
	int model_step_thread = 0;
	for(auto i = 0; i < model::step_actions.size(); ++i)
	{
		model_step_thread++;
		if(model::step_actions[i].run == false)
		{
			auto command = model::step_actions[i].command;
			auto label = model::step_actions[i].device_label;
			model_task.add_subtask(Cleaned_Task([command, label, &model_step_thread] () mutable
								   {
									   try
									   {
										   mangle_model(command, model::get_device(label));
										   command->complete_command();
										   command->time_to_complete -= model_timer.get_elapsed_time();
									   }
									   catch(std::exception&)
									   {
										   model_task.exception(std::current_exception());
									   }
									   model_step_thread--;
								   }));
			model::step_actions[i].run = true;
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
	my_node.clear_node();
	step_actions.clear();
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
	Packed_Command key;                                         //NOLINT
	compare(Packed_Command const& i) : key(i)                   //NOLINT
	{ }                                                         //NOLINT
	bool operator()(Packed_Command const& i)                    //NOLINT
	{                                                           //NOLINT
		bool same_command = key.command == i.command;           //NOLINT
		bool same_device = key.device_label == i.device_label;  //NOLINT
		return same_command && same_device;                     //NOLINT
	}                                                           //NOLINT
};
/**
 * \endcond
 */

void model::command_model(const Packed_Command& command)
{
	auto found = std::find_if(model::step_actions.begin(), model::step_actions.end(), compare(command));
	if(found == model::step_actions.end() || model::step_actions.size() == 0)
	{
		model::step_actions.emplace_back(command);
	}
}