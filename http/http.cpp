// http.cpp : Defines the exported functions for the DLL application.
//

#include <iostream>
#include <string>
#include <queue>
#include <mutex>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/config.hpp> 
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include "plugin/receiver.h"

#include "server.hpp"
#include "request.hpp"
#include "connection.hpp"

namespace comm {


	class tcp : public receiver {
	public:
		tcp() {
			http::server::connection::request_sig_.connect(boost::bind(&tcp::get, this, _1));
			_port = 1789;
			_threads = 1;
		}
		
		void load(const std::string& filename) override {
			boost::property_tree::iptree pt;
			boost::property_tree::ini_parser::read_ini(filename, pt);

			set_port(pt.get<unsigned int>("General.port", 1789));
			set_threads(pt.get<unsigned int>("General.threads", 1));
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
			_lock.lock();
			std::string body = std::move(_requests.front().body);
			_requests.pop();
			_lock.unlock();

			len = body.size();
			output = std::move(body);
		}

		void end() override {

		}

		virtual ~tcp() = default;

	private:
		void set_port(unsigned int port) {
			if (port) {
				_port = port;
			}
		}

		void set_threads(unsigned int threads) {
			if (threads) {
				_threads = threads;
			}
		}

	private:
		std::queue<http::server::request> _requests;
		std::string  _filename;
		unsigned int _port;
		unsigned int _threads;
		std::mutex   _lock;
	};

	extern "C" BOOST_SYMBOL_EXPORT tcp plugin;
	tcp plugin;

} // namespace my_namespace

