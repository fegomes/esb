// deleteme.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include "server.hpp"
#include <boost/logic/tribool.hpp>
using namespace boost;

tribool some_operation() { return tribool(indeterminate); }
	

#include <map>
#include <utility>
#include <functional>

int conv(double d) {
	return (int)d;
}

struct useless_type { };

class nonaddressable {
public:
	nonaddressable(int x) {
		x1 = x;
	}
	useless_type operator&() const;
	static void* operator new(std::size_t sz) {
		return nullptr;
	}
	static void* operator new(std::size_t sz, bool b) {
		return nullptr;
	}

	int x1;
};


int main(int argc, char* argv[])
{
	auto name = "fernando";
	
	std::function< int(double) > _func;

	
	// atribuindo a função a variável
	_func = conv;

	int i = _func(1.234);

	nonaddressable x(10);
	//nonaddressable* ptr = &x;
	x.x1;
	nonaddressable *x2 = new nonaddressable(10);

	
	tribool b = some_operation();
	if (b) {
		return 1;
	}
	else if (!b) {
		return 0;
	}
	else {
		return -1;
	}


	//x2->x = 10;
	
	
	return 0;
}