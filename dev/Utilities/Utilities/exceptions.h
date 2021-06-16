#ifndef PROJECT_EXCEPTIONS_H
#define PROJECT_EXCEPTIONS_H

#include <exception>

class DeviceNotFoundException : public std::exception
{
    virtual const char* what() const throw()
    {
        return "Device is not on node";
    }
};

class NodeNotFoundException : public std::exception
{
    virtual const char* what() const throw()
    {
        return "Node is unknown";
    }
};
class IncorrectStateTypeException : public std::exception
{
    virtual const char* what() const throw()
    {
        return "Incorrect state attempting to be mangled";
    }
};
class InvalidCommandException : public std::exception
{
    virtual const char* what() const throw()
    {
        return "Invalid command given";
    }
};
#endif