#ifndef NETWORK_SYSTEM_INTERFACE
#define NETWORK_SYSTEM_INTERFACE

enum class NETWORK_INITALIZED_ERRORS
{
    ADAPTER_ERROR,
    SOCKET_INVALID,
    INVALID_HOSTNAME
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
    ipv4_addr() {};
};

class Network_Interface
{
public:
    void set_server();
    void set_client();
    virtual void connect(ipv4_addr addr) = 0;
    virtual bool initalized() = 0;
    virtual void initalize() = 0;
protected:
    bool is_server = false;
    ipv4_addr my_ip = { 0xff,0xff,0xff,0xff };
};

namespace network
{
    extern Network_Interface* network_interface;

    extern void init_network_interfaces();
}

#endif