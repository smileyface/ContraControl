#ifndef NETWORK_STATUS_STATE_H
#define NETWORK_STATUS_STATE_H

enum class NETWORK_STATUS : unsigned char
{
    NETWORK_ERROR,
    NETWORK_INITALIZED,
    CLIENT_CONNECT,
    SERVER_LISTENING
};

enum class NETWORK_ERRORS : unsigned char
{
    NO_NETWORK_ERROR,
    UNINITALIZED_INTERFACE,
    ADAPTER_ERROR,
    SOCKET_INVALID,
    INVALID_HOSTNAME,
    ERROR_ON_SOCKET_BIND,
    ERROR_ON_SOCKET_LISTEN,
    SYSTEM_INTERFACE_ERROR,
    SOCKET_BUSY
};

struct Network_Status_State
{
    NETWORK_STATUS status;
    NETWORK_ERRORS error;

    Network_Status_State();
    void set_status(NETWORK_STATUS add_status);
    void set_error(NETWORK_ERRORS add_error);
};

#endif // !NETWORK_STATUS_STATE_H