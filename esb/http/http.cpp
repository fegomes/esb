// http.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <queue>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/config.hpp> 
#include <plugin/receiver.h>
#include "server.hpp"
#include "request.hpp"
#include "connection.hpp"

namespace comm {


	class tcp : public receiver {
	public:
		tcp() {
			std::cout << "Constructing http" << std::endl;
			http::server::connection::request_sig_.connect(boost::bind(&tcp::get, this, _1));
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

		void get(http::server::request request) {
			_requests.push(request);
		}

		void receive(boost::any& output, size_t& len) {
			if (_requests.empty()) {
				return;
			}
			output =  _requests.front().body;
			len = _requests.front().body.size();
			_requests.pop();
		}

		void end() {

		}


		~tcp() {
			std::cout << "Destructing http" << std::endl;
		}

	private:
		std::queue<http::server::request> _requests;
	};

	extern "C" BOOST_SYMBOL_EXPORT tcp plugin;
	tcp plugin;

} // namespace my_namespace

