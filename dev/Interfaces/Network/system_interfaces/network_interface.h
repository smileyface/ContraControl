#ifndef NETWORK_SYSTEM_INTERFACE
#define NETWORK_SYSTEM_INTERFACE

#include <string>
#include "Network/messages.h"
#include "types/ipv4_addr.h"
#include "types/network_status_state.h"

const unsigned short DEFAULT_PORT = 0xDCF5;
const std::string invalid_hostname = "INVALID";

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

    //setters
    virtual void set_my_ip() = 0;

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