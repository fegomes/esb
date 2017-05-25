// deleteme.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include "server.hpp"

int main(int argc, char* argv[])
{
	try
	{
		// Check command line arguments.
		if (argc != 3)
		{
			std::cerr << "Usage: http_server <address> <port> <threads> <doc_root>\n";
			std::cerr << "  For IPv4, try:\n";
			std::cerr << "    receiver 0.0.0.0 80 1 .\n";
			std::cerr << "  For IPv6, try:\n";
			std::cerr << "    receiver 0::0 80 1 .\n";
			return 1;
		}

		// Initialise the server.
		unsigned short port = boost::lexical_cast<unsigned short>(argv[1]);
		std::size_t num_threads = boost::lexical_cast<std::size_t>(argv[2]);
		http::server::server s(port, num_threads);

		// Run the server until stopped.
		s.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "exception: " << e.what() << "\n";
	}

	return 0;
}