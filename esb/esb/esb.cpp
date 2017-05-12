// esb.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "log.h"


int main(int argc, char* argv[])
{
	// init log
	core::log::get().init("esb", trace);

	BOOST_LOG_NAMED_SCOPE("main");

	BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
	BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
	BOOST_LOG_TRIVIAL(info) << "An informational severity message";
	BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
	BOOST_LOG_TRIVIAL(error) << "An error severity message";
	BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";


	return 0;
}

