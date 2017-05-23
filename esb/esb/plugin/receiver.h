#pragma once
#include <boost/any.hpp>

class receiver {
public:
	virtual void init() = 0;
	virtual void receive(boost::any output, size_t len) = 0;
};
