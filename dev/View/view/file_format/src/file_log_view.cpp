#include "../file_log_view.h"

#include <time.h>
#include <chrono>

#ifdef WIN32
#define localtime_r(_Time, _Tm) localtime_s(_Tm, _Time)
#include <windows.h>
#endif

File_Log_View::File_Log_View()
{
}

File_Log_View::~File_Log_View()
{ }

void File_Log_View::on_create()
{ 
	log_file.open(get_time_str() + ".log");
	Log_View_Type::create();
	File_View::on_create();
}

void File_Log_View::on_refresh()
{
	get_message();
}

void File_Log_View::on_paint()
{
	std::string paint_message = "[" + message.LEVEL + "]\t(" + message.LOC + "):\t" + message.MESSAGE;
	painted_message = get_time_str() +"\t" + paint_message;
}

void File_Log_View::on_display()
{
	log_file << painted_message << std::endl << std::flush;
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
	return "[" + std::to_string(month) + "/" + std::to_string(day) + "/" + std::to_string(year) + "  "
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
