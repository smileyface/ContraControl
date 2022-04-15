/*****************************************************************//**
 * \file   ipv4_addr.h
 * \brief  
 * 
 * \author kason
 * \date   September 2021
 *********************************************************************/
#ifndef NETWORK_TYPE_IPV4_ADDR
#define NETWORK_TYPE_IPV4_ADDR


#include <string>

/**
 * Common container for ipv4 address. This is a platform independant container.
 */
struct IPV4_Addr {
    union {
        struct {
            unsigned char s_b1; ///<Byte 1
            unsigned char s_b2; ///<Byte 2
            unsigned char s_b3; ///<Byte 3
            unsigned char s_b4; ///<Byte 4
        } S_un_b; ///<Address as bytes.
        struct {
            unsigned short s_w1; ///<Word 1
            unsigned short s_w2; ///<Word 2
        } S_un_w; ///<Address as words
        unsigned long S_addr; ///<Address as long
    } S_un; ///<Address structure
    /**
     * \brief Construct a new ipv4 addr object from string
     * 
     * \param string String to be split into bytes and put into S_un_b
     */
    IPV4_Addr(std::string string);
    /**
     * \brief Construct a new ipv4 addr object from unsigned long.
     * 
     * \param l1 A long that is the IPV4_Addr. 
     */
    IPV4_Addr(unsigned long l1);
    /**
     * \brief Construct a new ipv4 addr object.
     * 
     */
    IPV4_Addr();
    /**
     * \brief Get the address byte by byte
     * 
     * \return unsigned char* of size 4
     */
    unsigned char* get_addr_bytes();
    /**
     * \brief Get the IPV4_Addr as string
     * 
     * \return std::string 
     */
    std::string get_as_string();

    /**
     * \brief Set IPV4_Addr with char array.
     * 
     * \param ca The address as a char array.
     */
    void operator=(const unsigned char* ca);

    /**
     * \brief Compare 2 ipv4_addrs.
     * 
     * \param ad Address to compare.
     * \return equal compare.
     */
    bool operator==(const IPV4_Addr ad);
};


#endif // !NETWORK_TYPE_IPV4_ADDR
