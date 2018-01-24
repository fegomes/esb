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
#include <boost\bimap.hpp>

//#include <spdlog\spdlog.h>
#include <memory>

//namespace spd = spdlog;

int main(int argc, char* argv[])
{
	auto name = "fernando";
	size_t q_size = 16; //queue size must be power of 2
	//spdlog::set_async_mode(q_size);
	//auto file_logger = spd::rotating_logger_mt("file_logger", "logs/mylogfile.log", 1024, 1024);
	//for (int i = 0; i < 100; ++i)
	//	file_logger->info("Async message #{}", i);
	//auto async_file = spd::daily_logger_st("async_file_logger", "logs/async_log.txt");
	///for (int i = 0; i < 100; ++i)
	//	async_file->info("Async message #{}", i);

	

	struct Pai {
		virtual void ola() { whois(); ola(); }
		virtual void whois() { std::cout << "sou pai" << std::endl; }
	};

	struct Filho : public Pai {
		virtual void ola() { 
			static int i = 0;
			if (i > 0) {
				std::cout << "Oie Pai!" << std::endl;
				return;
			} 
			i++;
			Pai::ola(); 
		}
		virtual void whois() { std::cout << "sou filho" << std::endl; }
	};

	Pai *p = new Filho();
	p->whois();
	p->ola();

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
	
	
	// declaração de um bimap ( nome <-> idade ) e abaixo 3 atribuições
	typedef boost::bimap< std::string, int > tbimap;
	typedef tbimap::value_type pos;
	tbimap _bimap;
	_bimap.insert(pos("Fernando", 28));
	_bimap.insert(pos("Maria", 45));
	_bimap.insert(pos("João", 60));

	// para recuperar a idade passando o nome 
	int idade = _bimap.left.at("Fernando");

	// para recuperar o nome com a idade
	std::string nome = _bimap.right.at(28);
	return 0;
}