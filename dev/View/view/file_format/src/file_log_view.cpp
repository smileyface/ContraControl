#include "../file_log_view.h"

#include <time.h>
#include <chrono>

#ifdef WIN32
#define localtime_r(_Time, _Tm) localtime_s(_Tm, _Time)
#include <windows.h>
#endif

#include "Messaging/message_relay.h"

//TODO: Add this to a utility
void replace(
	std::string& s,
	std::string const& toReplace,
	std::string const& replaceWith
)
{
	for(std::size_t pos = s.find(toReplace); pos != std::string::npos; pos = s.find(toReplace))
	{
		s.replace(pos, toReplace.length(), replaceWith);
	}
}

File_Log_View::File_Log_View() :
	file_name("")
{
}

File_Log_View::~File_Log_View()
{ }

void File_Log_View::on_create()
{ 
	std::string timestamp = get_time_str();
	replace(timestamp, ":", ".");
	replace(timestamp, "/", "-");
	file_name = "LOG FILE" + timestamp + ".log";
	const char* file = file_name.c_str();
	log_file.open(file);
	if(log_file.fail())
	{
		LOG_ERROR("File creation failed. Error No: " + errno, "File_Log_View");
	}
	Log_View_Type::create();
	File_View::on_create();
}

void File_Log_View::on_refresh()
{
	get_message();
}

void File_Log_View::on_paint()
{
	while(!log_messages.empty())
	{
		auto message = log_messages.front();
		if(message.vaild)
		{
			std::string paint_message = "[" + message.LEVEL + "]\t(" + message.LOC + "):\t" + message.MESSAGE;
			painted_messages.push_back("[" + get_time_str() + "]" + "\t" + paint_message);
		}
		log_messages.erase(log_messages.begin());
	}
}

void File_Log_View::on_display()
{
	while(!painted_messages.empty())
	{
		auto message = painted_messages.front();
		log_file << message << std::endl << std::flush;
		painted_messages.erase(painted_messages.begin());
	}
}

void File_Log_View::on_destroy()
{
	log_file.close();
	Log_View_Type::destroy();
	File_View::on_destroy();
}

std::string File_Log_View::get_time_str()
{
	tm aTime;
	auto t = std::chrono::system_clock::now();
	time_t now = std::chrono::system_clock::to_time_t(t);
	localtime_r(&now, &aTime);

	const std::chrono::duration<double> tse = t.time_since_epoch();
	std::chrono::seconds::rep milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(tse).count() % 1000;

	int day = aTime.tm_mday;
	int month = aTime.tm_mon + 1; // Month is 0 - 11, add 1 to get a jan-dec 1-12 concept
	int year = aTime.tm_year + 1900; // Year is # years since 1900
	int hour = aTime.tm_hour; //24 hour format
	int minute = aTime.tm_min;
	int second = aTime.tm_sec;
	return std::to_string(month) + "/" + std::to_string(day) + "/" + std::to_string(year) + "-"
		+ std::to_string(hour) + ":" + std::to_string(minute) + ":" + std::to_string(second) + "." + std::to_string(milliseconds);
}

bool File_Log_View::is_stale()
{
	return log_consumer->is_stale();
}

bool File_Log_View::quit()
{
	return quiter;
}

std::string File_Log_View::get_file_name()
{
	return file_name;
}
