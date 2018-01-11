// esb.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <thread>
#include <memory>
#include <chrono>

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

template< typename Rep, typename Period>
inline void receive(receiver& rec, std::chrono::duration<Rep,Period> &d) {
	BOOST_LOG_SCOPE(__FUNCTION__);
	boost::any output;
	size_t len = 0;
	while (true) {
		output.clear();
		len = 0;
		rec.receive(output, len);
		if (len > 0) {
			BOOST_LOG_TRIVIAL(trace) << "Receive Message";
			BOOST_LOG_TRIVIAL(debug) << boost::any_cast<std::string>(output);
		}
		std::this_thread::sleep_for(d);
	}
}

int main(int argc, char* argv[])
{
	if (!init()) {
		return 1;
	}

	BOOST_LOG_SCOPE(__FUNCTION__);

	auto protocols = esb::ini::get().get_listeners();

	for (auto ci = protocols.begin(); ci != protocols.end(); ci++) {
		boost::filesystem::path lib_path(ci->second._path);
		boost::shared_ptr<receiver> rec = boost::dll::import<receiver>(ci->second._fullpath_lib,
			"plugin",
			boost::dll::load_mode::append_decorations
			);
		rec->load(ci->second._fullpath_ini);
		receivers.push_back(rec);
	}
	           
	BOOST_LOG_TRIVIAL(debug) << "Loading the plugins";

	std::vector<std::shared_ptr<std::thread> > threads;



	for (auto ci = receivers.begin(); ci != receivers.end(); ci++) {
		std::shared_ptr<std::thread> thread(new std::thread([&ci]() { ci->get()->init(); }));
		threads.push_back(thread);
	}
	
	for (auto ci = receivers.begin(); ci != receivers.end(); ci++) {
		std::shared_ptr<std::thread> thread(new std::thread([&ci]() {  receive(*ci->get(), std::chrono::milliseconds(500)); }));
		threads.push_back(thread);
	}
	

	// Wait for all threads in the pool to exit.
	for (std::size_t i = 0; i < threads.size(); ++i) {
		threads[i]->join();
	}
	





	return 0;
}

