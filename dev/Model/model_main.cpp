#include "model_main.h"

#include <algorithm>
#include <thread>
#include <mutex>

#include "Interfaces/types/state.h"

#include "Messaging/message_relay.h"


std::thread model_thread;
std::mutex model_mutex;

Timer::Basic model_timer;
std::atomic<bool> model::model_running;
Command_List model::step_actions;

Node model::my_node;

void model::initalize()
{
	model_timer.reset_clock();
	initalize_my_node("LOCAL");
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
	for(Command_List::iterator it = model::step_actions.begin(); it != model::step_actions.end(); ++it)
	{
		try
		{
			mangle_model(it->command, model::get_device(it->label));
			it->command->time_to_complete -= model_timer.get_elapsed_time();
		}
		catch(std::exception&)
		{
			model::step_actions.erase(model::step_actions.begin(), model::step_actions.begin() + 1);
			std::rethrow_exception(std::current_exception());
		}
	}

	model_timer.update_time();
	model::step_actions.erase(model::step_actions.begin(), model::step_actions.end());
}

void model_loop()
{
	LOG_DEBUG("Loop thread has started");
	while(model::model_running)
	{
		model::step();
	}
}

void model::start_loop()
{
	model_running = true;
	LOG_INFO("Model Started", subsystem_name);
	model_thread = std::thread(model_loop);
}

void model::stop_loop()
{
	LOG_INFO("Model Stopped", subsystem_name);
	model_running = false;
	model_thread.join();
}

void model::clean_up()
{
	my_node.clear_node();
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
	Model_Command key;
	compare(Model_Command const& i) : key(i)
	{ }
	bool operator()(Model_Command const& i)
	{
		bool same_command = key.command == i.command;
		bool same_device = key.label == i.label;
		return same_command && same_device;
	}
};
/**
 * \endcond
 */

void model::command_model(Model_Command command)
{
	auto found = std::find_if(model::step_actions.begin(), model::step_actions.end(), compare(command));
	if(found == model::step_actions.end() || model::step_actions.size() == 0)
	{
		model::step_actions.emplace_back(command);
	}
}