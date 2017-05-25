// http.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/config.hpp> 
#include <plugin/receiver.h>
#include "server.hpp"

namespace comm {


	class tcp : public receiver {
	public:
		tcp() {
			std::cout << "Constructing http" << std::endl;
		}

		void init() {
			std::cout << "init" << std::endl;

			try
			{
				unsigned short port = 1234;
				std::size_t num_threads = 1;
				http::server::server s(port, num_threads);
				s.run();
			}
			catch (std::exception& e)
			{
				std::cerr << "exception: " << e.what() << "\n";
			}

		}

		void receive(boost::any output, size_t len) {
			std::cout << "recv" << std::endl;
		}

		void end() {

		}


		~tcp() {
			std::cout << "Destructing http" << std::endl;
		}
	};

	extern "C" BOOST_SYMBOL_EXPORT tcp plugin;
	tcp plugin;

} // namespace my_namespace

