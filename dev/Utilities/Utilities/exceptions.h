#ifndef PROJECT_EXCEPTIONS_H
#define PROJECT_EXCEPTIONS_H

#include <exception>
/**
 \brief Exception node throws when attempting to access a device that does not exist.
 */
class DeviceNotFoundException : public std::exception
{
    virtual const char* what() const throw()
    {
        return "Device is not on node";
    }
};

/**
 \brief Exception for when attempting to access a node that is non-existant
 */

class NodeNotFoundException : public std::exception
{
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
    virtual const char* what() const throw()
    {
        return "Invalid command given";
    }
};
#endif