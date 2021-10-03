/*****************************************************************//**
 * \file   ipv4_addr.h
 * \brief  
 * 
 * \author kason
 * \date   September 2021
 *********************************************************************/
#include <string>

/**
 * Common container for ipv4 address. This is a platform independant container.
 */
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
    } S_un; ///<Address structure
    /**
     * Parse address from string.
     */
    ipv4_addr(std::string string);
    /**
     * Set address from byte, byte, byte, byte.
     * \param b1 Byte 1 of address.
     * \param b2 Byte 2 of address.
     * \param b3 Byte 3 of address.
     * \param b4 Byte 4 of address.
     */
    ipv4_addr(unsigned char b1, unsigned char b2, unsigned char b3, unsigned char b4);
    ipv4_addr(unsigned long l1);
    ipv4_addr();
    unsigned char* get_addr_bytes();
    std::string get_as_string();
    bool operator<(const ipv4_addr& d) const;
    void operator=(const unsigned long& D);
    /**
     * Specify the ++ operator for network sweeps. Must be specified to handle windows endian problems. Unix could just treat this like a long
     */
    ipv4_addr operator++();
};