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

	void build_str(const std::string& initial, std::string& response)
	{
		std::string tmp("");
		char sortType = ' ';
		std::stringstream ss_in(initial);
		std::stringstream ss_out;
		std::vector<float> nums_to_sort;	//No idea how many numbers, may need to access elements in middle, vector is best choice

		//Initialized response stringstream
		ss_out << "SORTED ";

		//Initial input
		ss_in >> tmp;

		//Invalid request format
		if (tmp != "LIST")
		{
			response = "ERROR";
			return;
		}

		//Number of inputs in LIST request
		int count = 0;

		int valid = 0;
		int sortIndex = 0;
		while (!ss_in.eof())
		{
			//Read next value
			ss_in >> tmp;
			count++;

			float val = 0;

			std::cout << "String Input: " << tmp << "\n";

			//Check for sorting type
			sortIndex = tmp.find_first_of("|");
			if (sortIndex >= 0)
			{
				//Make sure index exists
				if (sortIndex + 1 >= tmp.size())
				{
					response = "ERROR";
					return;
				}
				else
				{
					sortType = tmp[sortIndex + 1];
				}
			}

			//First check if float, then int, else error
			if (sscanf(tmp.c_str(), "%f", &val) > 0)
			{
				nums_to_sort.push_back(val);
				std::cout << "float: " << val << "\n";
				continue;
			}

			response = "ERROR";
			return;
		}

		//No numbers passed
		if (count <= 0)
		{
			response = "ERROR";
			return;
		}

		switch (sortType)
		{
		case 'd':	//Descedning
			std::sort(nums_to_sort.begin(), nums_to_sort.end(), [](int a, int b) {return a > b; });
			break;

		case 's':	//Alphabetical
			std::sort(nums_to_sort.begin(), nums_to_sort.end(), [](int a, int b) {return std::to_string(a) < std::to_string(b); });
			break;
		
		case 'a':	//Ascending
		case ' ':
			std::sort(nums_to_sort.begin(), nums_to_sort.end());
			break;

		default:	//Invalid
			response = "ERROR";
			return;
			
		}
		

		//Add sorted numbers to stringstream
		for (int i = 0; i < nums_to_sort.size(); i++)
		{
			ss_out << nums_to_sort[i];

			//Don't need space after last element
			if (i < nums_to_sort.size() - 1)
			{
				ss_out << " ";
			}
		}

		response = ss_out.str();
	}

	/// <summary>
	/// Handles any connected clients
	/// </summary>
	/// <returns>Whether or not the connection is alive</returns>
	bool handle_connection(Socket& clt_sock)
	{
		char buffer[4096];
		int nbytes_recvd = clt_sock.Recv(buffer, sizeof(buffer));

		if (nbytes_recvd == -1)
		{
			//Error and crash
			perror("recv() failed");
			exit(1);
		}

		//Got no data
		if (nbytes_recvd == 0) { return false; }

		//Receive initial message
		std::string msg_recvd(buffer, nbytes_recvd);
		std::cout << "Received message " << nbytes_recvd << " bytes long: '" << msg_recvd << "'\n";

		//Construct response
		std::string response("");
		build_str(msg_recvd, response);

		//Send response
		std::cout << "Sending message " << response.size() << " bytes long: '" << response << "'\n\n";
		clt_sock.Send(response.data(), response.size());
 
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

			while (handle_connection(clt_sock))
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
