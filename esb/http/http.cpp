// http.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <iostream>

#include <boost/config.hpp> // for BOOST_SYMBOL_EXPORT
#include <plugin/receiver.h>

namespace comm {

	class http : public receiver {
	public:
		http() {
			std::cout << "Constructing http" << std::endl;
		}

		void init() {
			std::cout << "init" << std::endl;
		}

		void recv(boost::any output, size_t len) {
			std::cout << "recv" << std::endl;
		}

		~http() {
			std::cout << "Destructing http" << std::endl;
		}
	};

	extern "C" BOOST_SYMBOL_EXPORT http plugin;
	http plugin;

} // namespace my_namespace

