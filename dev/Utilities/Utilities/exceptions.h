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

#endif