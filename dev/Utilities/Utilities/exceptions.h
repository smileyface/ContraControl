/*****************************************************************//**
 * \file   exceptions.h
 * \brief  
 * 
 * \author kason
 * \date   June 2021
 *********************************************************************/
#ifndef PROJECT_EXCEPTIONS_H
#define PROJECT_EXCEPTIONS_H

#include <stdexcept>

/**
 \brief Exception for when attempting to access a node that is non-existant
 */

class NodeNotFoundException : public std::exception
{
public:
    /**
 * Austin 3:16 says:
 *
 * \return String of message
 */
    virtual const char* what() const throw()
    {
        return "Node is unknown";
    }
};

/**
 \brief Exception thrown when a command is given to a device that does not deal with the command. Example: A switch attempting a linear transition.
 */
class IncorrectStateTypeException : public std::exception
{
public:
    /**
 * Austin 3:16 says:
 *
 * \return String of message
 */
    virtual const char* what() const throw()
    {
        return "Incorrect state attempting to be mangled";
    }
};

/**
 \brief When the state mangler recieves an invalid command.
 */
class InvalidCommandException : public std::exception
{
public:
    /**
 * Austin 3:16 says:
 *
 * \return String of message
 */
    virtual const char* what() const throw()
    {
        return "Invalid command given";
    }
};

/**
 \brief When attempting to change the state of an invalid device type
 */
class InvalidDeviceException : public std::exception
{
public:
    /**
 * Austin 3:16 says:
 *
 * \return String of message
 */
    virtual const char* what() const throw()
    {
        return "Device is of an invalid type";
    }
};

/**
 \brief When a function has not been implemented.
 */
class UnimplementedFunctionException : public std::exception
{
public:
    /**
 * Austin 3:16 says:
 *
 * \return String of message
 */
    virtual const char* what() const throw()
    {
        return "Function not implemented";
    }
};

/**
 \brief When the network struggles. See the network status_state for details.
 */
class NetworkErrorException : public std::exception
{
public:
    /**
     * Austin 3:16 says:
     * 
     * \return String of message
     */
    virtual const char* what() const throw()
    {
        return "Network Error";
    }

};
#endif