// deleteme.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include "server.hpp"
#include <boost/bimap.hpp>

int main(int argc, char* argv[])
{
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