// TCP_Socket.h
// TCP_Socket for FS2Open PXO
// Derek Meek
// 2-14-2003

// ############## ATTENTION ##########
// Licensed under the Academic Free License version 2.0
// View License at http://www.opensource.org/licenses/afl-2.0.php
// ###################################




#if !defined(__TCP_SOCKET_H_)
#define __TCP_SOCKET_H_

#define ASIO_STANDALONE
#include <asio.hpp>

#include "globalincs/pstypes.h" // make sure _cdecl is defined correctly on *nix

#include <memory>

// Only use the as namespace so it's easier to switch to boost::asio if required
namespace as = ::asio;
namespace ip = as::ip;

class TCPSocket
{
	SCP_string _address;
	SCP_string _port;

	bool _connecting;
	bool _connected;

	as::io_service _io_service;

	std::unique_ptr<ip::tcp::socket> _socket;
	std::unique_ptr<ip::tcp::resolver> _resolver;

	std::error_code _error;

	void runIo();

	void resolve_callback(const std::error_code& errorCode, const ip::tcp::resolver::iterator& it);
	void connect_callback(const std::error_code& errorCode, const ip::tcp::resolver::iterator& it);
public:
	TCPSocket(const SCP_string& address, SCP_string port);
	~TCPSocket();

	bool connect();
};

int FS2NetD_ConnectToServer(const char *host, const char *port);
void FS2NetD_Disconnect();

int FS2NetD_GetData(char *buffer, int blen);
int FS2NetD_SendData(char *buffer, int blen);
bool FS2NetD_DataReady();


#endif // __TCP_SOCKET_H_
