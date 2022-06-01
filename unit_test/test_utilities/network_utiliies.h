#include <vector>

#ifdef _WIN32
#include <WinSock2.h>
#endif
#ifdef __linux__
#include <sys/socket.h>
typedef int SOCKET;
#endif


namespace network_utilities
{
	extern SOCKET test_broadcast_sock;
	extern SOCKET test_direct_sock;
	void setup();
	void cleanup();

	void send_broadcast_message(std::vector<char> message);
}