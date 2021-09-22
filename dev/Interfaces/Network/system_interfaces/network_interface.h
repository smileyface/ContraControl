#ifndef NETWORK_SYSTEM_INTERFACE
#define NETWORK_SYSTEM_INTERFACE

#include <string>
#include "Network/messages.h"
#include "types/network_status_state.h"

const unsigned short DEFAULT_PORT = 0xDCF5;
const std::string invalid_hostname = "INVALID";

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
    ipv4_addr(std::string string);
    ipv4_addr(unsigned char b1, unsigned char b2, unsigned char b3, unsigned char b4);
    ipv4_addr(unsigned long l1);
    ipv4_addr();
    unsigned char* get_addr_bytes();
    std::string get_as_string();
    bool operator<(const ipv4_addr& d) const;
    void operator=(const unsigned long& D);
    /**
     * Specify the ++ operator for network sweeps. Must be specified to handle windows endian problems. Unix cound just treat this like a long
     */
    ipv4_addr operator++();
};

class Network_Interface
{
public:
    void set_server();
    void set_client();
    virtual void initalized() = 0;
    virtual void initalize() = 0;
    virtual void clean_up() = 0;
    Network_Status_State get_status();

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
    std::string hostname;

    Network_Status_State status_state;
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