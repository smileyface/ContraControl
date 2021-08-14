#ifndef NETWORK_SYSTEM_INTERFACE
#define NETWORK_SYSTEM_INTERFACE

#include <string>

#include "Network/messages.h"

const int DEFAULT_PORT = 65656;
const std::string invalid_hostname = "INVALID";

enum class NETWORK_INITALIZED_ERRORS
{
    ADAPTER_ERROR,
    SOCKET_INVALID,
    INVALID_HOSTNAME,
    ERROR_ON_SOCKET_BIND,
    ERROR_ON_SOCKET_LISTEN
};

struct ipv4_addr {
    union {
        struct {
            unsigned char s_b1;
            unsigned char s_b2;
            unsigned char s_b3;
            unsigned char s_b4;
        } S_un_b;
        struct {
            unsigned short s_w1;
            unsigned short s_w2;
        } S_un_w;
        unsigned long S_addr;
    } S_un;
    ipv4_addr(char* string);
    ipv4_addr(unsigned char b1, unsigned char b2, unsigned char b3, unsigned char b4)
    {
        S_un.S_un_b.s_b1 = b1;
        S_un.S_un_b.s_b2 = b2;
        S_un.S_un_b.s_b3 = b3;
        S_un.S_un_b.s_b4 = b4;
    }
    ipv4_addr(unsigned long l1)
    {
        S_un.S_addr = l1;
    }
    ipv4_addr() { S_un.S_addr = ULONG_MAX; };
    unsigned char* get_addr_bytes()
    {
        return reinterpret_cast<unsigned char*>(&S_un.S_un_b);
    }
    std::string get_as_string()
    {
        std::string addr_string = std::to_string(S_un.S_un_b.s_b1);
        for (int i = 1; i < sizeof(S_un.S_un_b); i++)
        {
            addr_string.append(".");
            addr_string.append(std::to_string(get_addr_bytes()[i]));
        }
        return addr_string;
    }
    bool operator<(const ipv4_addr& d) const
    {
        return S_un.S_addr < d.S_un.S_addr;
    }
    /**
     * Specify the ++ operator for network sweeps. Must be specified to handle windows endian problems. Unix cound just treat this like a long
     */
    ipv4_addr operator++()
    {
        if (this->S_un.S_un_b.s_b2 == 255 && this->S_un.S_un_b.s_b3 == 255 && this->S_un.S_un_b.s_b4 == 255)
        {
            this->S_un.S_un_b.s_b1++;
        }
        if (this->S_un.S_un_b.s_b3 == 255 && this->S_un.S_un_b.s_b4 == 255)
        {
            this->S_un.S_un_b.s_b2++;
        }
        if (this->S_un.S_un_b.s_b4 == 255)
        {
            this->S_un.S_un_b.s_b3++;
        }
        this->S_un.S_un_b.s_b4++;
        return *this;
    }
};

class Network_Interface
{
public:
    void set_server();
    void set_client();
    virtual bool initalized() = 0;
    virtual void initalize() = 0;
    virtual void clean_up() = 0;

    //getters
    unsigned char* local_ip();

    //Client Code
    virtual void connect_to_server(ipv4_addr addr) = 0;
    virtual void scan_for_server() = 0;
    
    //Server Code
    virtual void server_start() = 0;

   //Constants
    const ipv4_addr localhost = ipv4_addr("127.0.0.1");
protected:
    bool is_server = false;
    ipv4_addr my_ip = ipv4_addr("255.255.255.255");
    char hostname[255];
};

namespace network
{
    extern Network_Interface* network_interface;

    extern void init_network_interfaces();
    extern void teardown_network_interfaces();
    extern void send_message(MESSAGE*);

    extern void start_server();
    extern void start_client();
}

#endif