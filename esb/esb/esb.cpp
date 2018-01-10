// esb.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <thread>
#include <memory>

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

#include "ini.h"

int init() {
	try {
		core::log::get().init("esb", "log.ini");
		esb::ini::get().init("esb.ini");
	}
	catch (...) {
		return false;
	}
	return true;
}

std::vector<boost::shared_ptr<receiver>> receivers;

void receive(receiver& rec) {
	BOOST_LOG_SCOPE(__FUNCTION__);
	while (true) {
		boost::any output;
		size_t len = 0;
		rec.receive(output, len);
		if (len > 0) {
			BOOST_LOG_TRIVIAL(trace) << "Receive Message";
			BOOST_LOG_TRIVIAL(debug) << boost::any_cast<std::string>(output);
		}
	}
}

int main(int argc, char* argv[])
{
	if (!init()) {
		return 1;
	}

	BOOST_LOG_SCOPE(__FUNCTION__);

	auto protocols = esb::ini::get().get_protocols();

	for (auto ci = protocols.begin(); ci != protocols.end(); ci++) {
		boost::filesystem::path lib_path(ci->second._path);
		receivers.push_back(boost::dll::import<receiver>(lib_path / (ci->second._file),
			"plugin",
			boost::dll::load_mode::append_decorations
			));
	}
	           
	BOOST_LOG_TRIVIAL(debug) << "Loading the plugins";

	std::vector<std::shared_ptr<std::thread> > threads;

	for (auto ci = receivers.begin(); ci != receivers.end(); ci++) {
		std::shared_ptr<std::thread> thread(new std::thread([&ci]() { ci->get()->init(); }));
		threads.push_back(thread);
	}
	
	for (auto ci = receivers.begin(); ci != receivers.end(); ci++) {
		std::shared_ptr<std::thread> thread(new std::thread([&ci]() {  receive(*ci->get()); }));
		threads.push_back(thread);
	}
	

	// Wait for all threads in the pool to exit.
	for (std::size_t i = 0; i < threads.size(); ++i) {
		threads[i]->join();
	}
	





	return 0;
}

