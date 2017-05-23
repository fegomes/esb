#pragma once
#include <boost/any.hpp>

class publisher {
public:
	virtual void init() = 0;
	virtual void send(boost::any input, size_t input_len) = 0;
};
