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
#include <boost/bimap.hpp>


int main(int argc, char* argv[])
{
	auto name = "fernando";
	
	std::function< int(double) > _func;

	
	// atribuindo a fun��o a vari�vel
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
	
	
	// declara��o de um bimap ( nome <-> idade ) e abaixo 3 atribui��es
	typedef boost::bimap< std::string, int > tbimap;
	typedef tbimap::value_type pos;
	tbimap _bimap;
	_bimap.insert(pos("Fernando", 28));
	_bimap.insert(pos("Maria", 45));
	_bimap.insert(pos("Jo�o", 60));

	// para recuperar a idade passando o nome 
	int idade = _bimap.left.at("Fernando");

	// para recuperar o nome com a idade
	std::string nome = _bimap.right.at(28);
	return 0;
}