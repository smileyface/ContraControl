#ifndef SYSTEM_TESTING_UTIL_H
#define SYSTEM_TESTING_UTIL_H

#include "../../dev/Interfaces/Messaging/message_relay.h"
#include "../../dev/View/input_interface/sys_interface/keyboard_interface.h"

namespace system_utilities
{
	void setup();
	void setup_messaging();
	void teardown_messaging();

	void cleanup();
	void print_log_messages();

	void step(int steps);

	void sleep_thread(int wait_time);
	extern bool CI;
	extern bool LINUX;
	extern bool WINDOWS;
	namespace model_utilities
	{
		void start();
		void stop();
	}
	namespace controller_utilities
	{
		void start();
		void stop();
	}
	namespace view_utilities
	{
		void start();
		void stop();
	}
	namespace network_utilities
	{
		void setup();
	}
	namespace keyboard_utilities
	{
		class Keyboard
		{
		public:
			Keyboard();
			~Keyboard();
			void wait_for_first_key(KPI key);
			void operator<<(const int& input);
			void operator<<(const char& input);
			void operator<<(const std::string& input);
			void set_key_operation(KPI key, std::function<void()> func);
			bool keyboard_present();
			void operator<(const KPI key_to_press);
			Keyboard_Interface* get_interface();
			void override_interface(Keyboard_Interface* new_interface);
			bool still_running();
		private:
			Keyboard_Interface* buffer;
		};
		char get_char_from_kpi(KPI key);
		void setup();
		void tear_down();
		void press_button(int key);
		extern bool connect; //default is connect to the hardware
	}
}

#endif