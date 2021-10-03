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
    SOCKET_BUSY,
    SERVER_CANNOT_START,
    UNKNOWN_ERROR
};

/**
 * \brief A container for displaying the state of the network
 * 
 */
struct Network_Status_State
{
    NETWORK_STATUS status; ///<The status state.
    NETWORK_ERRORS error; ///<The current error state.
    /**
     * \brief Construct a new Network_Status_State object
     * Sets state to  and error to NETWORK_ERRORS::UNKNOWN_ERROR
     */
    Network_Status_State();

    /**
     * \brief Set the status of the network
     * 
     * Sets error to NETWORK_ERRORS::NO_NETWORK_ERROR
     *
     * \param add_status Status to set.
     */
    void set_status(NETWORK_STATUS add_status);
    /**
     * \brief Set the status of the error
     *
     * Sets status to NETWORK_STATUS::NETWORK_ERROR
     * 
     * \param add_error Error to set.
     */
    void set_error(NETWORK_ERRORS add_error);
};

#endif // !NETWORK_STATUS_STATE_H