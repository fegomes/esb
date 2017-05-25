// http.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <iostream>

#include <boost/config.hpp> 

#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <plugin/receiver.h>

namespace comm {

	using boost::asio::ip::tcp;

	class session
		: public std::enable_shared_from_this<session>
	{
	public:
		session(tcp::socket socket)
			: socket_(std::move(socket))
		{
		}

		void start()
		{
			do_read();
		}

	private:
		void do_read()
		{
			auto self(shared_from_this());
			socket_.async_read_some(boost::asio::buffer(data2_, max_length),
				[this, self](boost::system::error_code ec, std::size_t length)
			{
				if (!ec)
				{
					do_write(length);
				}
			});
		}

		void do_write(std::size_t length)
		{
			auto self(shared_from_this());
			boost::asio::async_write(socket_, boost::asio::buffer(data_, length),
				[this, self](boost::system::error_code ec, std::size_t /*length*/)
			{
				if (!ec)
				{
					do_read();
				}
			});
		}

		tcp::socket socket_;
		enum { max_length = 1024 };
		std::string data_;
		char data2_[max_length];
	};

	class server
	{
	public:
		server(boost::asio::io_service& io_service, short port)
			: acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
			socket_(io_service)
		{
			do_accept();
		}

	private:
		void do_accept()
		{
			acceptor_.async_accept(socket_,
				[this](boost::system::error_code ec)
			{
				if (!ec)
				{
					std::make_shared<session>(std::move(socket_))->start();
				}

				do_accept();
			});
		}

		tcp::acceptor acceptor_;
		tcp::socket socket_;
	};


	class http : public receiver {
	public:
		http() {
			std::cout << "Constructing http" << std::endl;
		}

		void init() {
			std::cout << "init" << std::endl;

			try
			{
				boost::asio::io_service io_service;
				

				server server_(io_service, 1234);

				io_service.run();
			}
			catch (std::exception& e)
			{
				std::cerr << e.what() << std::endl;
			}
		}

		void receive(boost::any output, size_t len) {
			std::cout << "recv" << std::endl;
		}

		void end() {

		}


		~http() {
			std::cout << "Destructing http" << std::endl;
		}
	};

	extern "C" BOOST_SYMBOL_EXPORT http plugin;
	http plugin;

} // namespace my_namespace

