// esb.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <thread>

#include <boost/dll/import.hpp>
#include <boost/filesystem.hpp>
#include <boost/bind.hpp>

#include "log.h"
#include "plugin/receiver.h"

/*
BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
BOOST_LOG_TRIVIAL(info) << "An informational severity message";
BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
BOOST_LOG_TRIVIAL(error) << "An error severity message";
BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";
*/
int init() {
	try {
		core::log::get().init("esb", "log.ini");
	}
	catch (...) {
		return false;
	}
	return true;
}

boost::shared_ptr<receiver> plugin1;

void listen() {
	plugin1->init();
}

void receive() {
	while (true) {
		boost::any output;
		size_t len = 0;
		plugin1->receive(output, len);
		if (len > 0) {
			std::cout << boost::any_cast<std::string>(output) << std::endl;
		}
	}
}

int main(int argc, char* argv[])
{
	if (!init()) {
		return 1;
	}

	BOOST_LOG_SCOPE(__FUNCTION__);

	boost::filesystem::path lib_path("C:\\Users\\fernando\\Source\\Repos\\esb\\esb\\Debug"); 
	           
	std::cout << "Loading the plugin" << std::endl;

	plugin1 = boost::dll::import<receiver>(  lib_path / "http",                    
											"plugin",                                   
											boost::dll::load_mode::append_decorations
											);

	std::vector<std::shared_ptr<std::thread> > threads;

	{
		std::shared_ptr<std::thread> thread(new std::thread(listen));
		threads.push_back(thread);
	}
	{
		std::shared_ptr<std::thread> thread(new std::thread(receive));
		threads.push_back(thread);
	}
	

	// Wait for all threads in the pool to exit.
	for (std::size_t i = 0; i < threads.size(); ++i) {
		threads[i]->join();
	}
	





	return 0;
}

