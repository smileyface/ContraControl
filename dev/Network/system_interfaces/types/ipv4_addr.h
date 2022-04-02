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
struct ipv4_addr {
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
    ipv4_addr(std::string string);
    /**
     * \brief Construct a new ipv4 addr object from unsigned long.
     * 
     * \param l1 A long that is the ipv4_addr. 
     */
    ipv4_addr(unsigned long l1);
    /**
     * \brief Construct a new ipv4 addr object.
     * 
     */
    ipv4_addr();
    /**
     * \brief Get the address byte by byte
     * 
     * \return unsigned char* of size 4
     */
    unsigned char* get_addr_bytes();
    /**
     * \brief Get the ipv4_addr as string
     * 
     * \return std::string 
     */
    std::string get_as_string();
    /**
     * \brief Compare IPV4_addr for list generation and sorting
     * 
     * \param d ipv4_addr to compare to
     * \return true by comparing longs
     * \return false by comparing longs
     */
    bool operator<(const ipv4_addr& d) const;
    /**
     * \brief Set ipv4_addr with unsigned long.
     * 
     * \param D The address as unsigned long.
     */
    void operator=(const unsigned long& D);
    /**
     * \brief Set ipv4_addr with char array.
     * 
     * \param ca The address as a char array.
     */
    void operator=(const unsigned char* ca);

    bool operator==(const ipv4_addr ad);
};


#endif // !NETWORK_TYPE_IPV4_ADDR
