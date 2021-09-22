#include "Network/system_interfaces/types/network_status_state.h"

Network_Status_State::Network_Status_State()
{
    status = NETWORK_STATUS::NETWORK_ERROR;
    error = NETWORK_ERRORS::UNINITALIZED_INTERFACE;
}
void Network_Status_State::set_status(NETWORK_STATUS add_status)
{
    status = add_status;
    error = NETWORK_ERRORS::NO_NETWORK_ERROR;
}
void Network_Status_State::set_error(NETWORK_ERRORS add_error)
{
    status = NETWORK_STATUS::NETWORK_ERROR;
    error = add_error;
}