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
	core::log::get().init("esb", trace);
	return true;
}

int main(int argc, char* argv[])
{
	BOOST_LOG_NAMED_SCOPE(__FUNCTION__);

	if (!init()) {
		return 1;
	}
	
	BOOST_LOG_TRIVIAL(debug) << "Begin";



	BOOST_LOG_TRIVIAL(debug) << "End";
	return 0;
}

