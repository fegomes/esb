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
			_port = 1789;
			_threads = 1;
		}
		
		void load(const std::string& filename) override {

		}

		void init() override {
			try
			{
				http::server::server s(_port, _threads);
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

		void end() override {

		}


		~tcp() {
			std::cout << "Destructing http" << std::endl;
		}

	private:
		std::queue<http::server::request> _requests;
		std::string _filename;
		unsigned int _port;
		unsigned int _threads;
	};

	extern "C" BOOST_SYMBOL_EXPORT tcp plugin;
	tcp plugin;

} // namespace my_namespace

