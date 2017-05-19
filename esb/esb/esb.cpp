// esb.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "log.h"

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

int main(int argc, char* argv[])
{
	if (!init()) {
		return 1;
	}

	BOOST_LOG_SCOPE(__FUNCTION__);






	return 0;
}

