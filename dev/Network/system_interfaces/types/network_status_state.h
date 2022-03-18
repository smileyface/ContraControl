/*****************************************************************//**
 * \file   network_status_state.h
 * \brief  
 * 
 * \author kason
 * \date   October 2021
 *********************************************************************/
#ifndef NETWORK_STATUS_STATE_H
#define NETWORK_STATUS_STATE_H

/** 
 * Network status states. Mainly a parody so the different systems can report the same statuses.
 */
enum class NETWORK_STATUS : unsigned char
{
    /** Network is in the error state. */
    NETWORK_ERROR,
    /** Network is initalized */
    NETWORK_INITALIZED,
    /** Client is connected */
    CLIENT_CONNECT,
    /** Server is listening for clients */
    SERVER_LISTENING
};

/**
 * Errors that the network can encounter. Mainly a parody so the different systems can report the same statuses.
 */
enum class NETWORK_ERRORS : unsigned char
{
    /** No errors. */
    NO_NETWORK_ERROR,
    /** The network libraries are not initalized. */
    UNINITALIZED_INTERFACE,
    /** The physical adapter is not available. */
    ADAPTER_ERROR,
    /** Socket is not valid. */
    SOCKET_INVALID,
    /** Hostname is not valid */
    INVALID_HOSTNAME,
    /** Binding to a socket failed */
    ERROR_ON_SOCKET_BIND,
    /** Listening on a socket failed */
    ERROR_ON_SOCKET_LISTEN,
    /** The system network interface failed */
    SYSTEM_INTERFACE_ERROR,
    /** The socket is busy. Not a fatal error. */
    SOCKET_BUSY,
    /** Error starting server */
    SERVER_CANNOT_START,
    /** A code error has occured and needs debugged. */
    NETWORK_CODE_ERROR,
    /** When an option is incorrect. */
    NETWORK_OPTION_ERROR,
    /** Some unknown error has occured. */
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