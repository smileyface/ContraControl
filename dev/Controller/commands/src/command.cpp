#include "../command.h"

COMMAND_ENUM Command::get_id() { return COMMAND_ENUM::INVALID; }

bool Command::completed() { return time_to_complete <= 0.0; }