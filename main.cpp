#include <iostream>
#include <sstream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#include <socklib.h>

const char * const HOST = "127.0.0.1";
const int PORT = 20000;
const int BACKLOG = 20;

class SortServer {
private:
	Socket srv_sock;
	std::string srv_host;
	int srv_port;
	int srv_backlog;

public:
	//List initializer for socket
	SortServer(const char* host, int port) : srv_sock(Socket(Socket::Family::INET, Socket::Type::STREAM)) 
	{
		srv_host = host;
		srv_port = port;
		srv_backlog = BACKLOG;
	}

	/// <summary>
	/// Handles any connected clients
	/// </summary>
	/// <returns>Whether or not the connection is alive</returns>
	bool handle_connection()
	{
		return true;
	}

	/// <summary>
	/// Initializes socket and waits for connections
	/// </summary>
	void run_server() 
	{
		//Bind socket to host/port
		Address srv_addr = Address(srv_host, srv_port);
		srv_sock.Bind(srv_addr);

		//Listen at socket
		srv_sock.Listen(srv_backlog);

		//Never shuts down
		while (true)
		{
			//Hangs while waiting for socket to accept connection
			std::cout << "\n----------------------\n";
			std::cout << "Awaiting connection...\n";
			std::cout << "----------------------\n\n";
			Socket clt_sock = srv_sock.Accept();

			std::cout << "\n----------------------\n";
			std::cout << "Connection received.\n";
			std::cout << "----------------------\n\n";

			while (handle_connection())
			{

			}

			std::cout << "\n----------------------\n";
			std::cout << "Connection Terminated.\n";
			std::cout << "----------------------\n\n";
		}
	}
};

int main(int argc, char *argv[]) {

	SockLibInit();

	SortServer server(HOST, PORT);
	server.run_server();

	SockLibShutdown();

  return 0;
}
