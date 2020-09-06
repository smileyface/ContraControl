#include "log_item.h"

LogItem::LogItem(LOG_PRIORITY pri, std::string msg, std::string dev)
{
	priority = pri;
	message = msg;
	device = dev;
}
