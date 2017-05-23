#pragma once
#include <boost/any.hpp>

class requester {
public:
	virtual void init() = 0;
	virtual void request(boost::any input, size_t input_len, boost::any output, size_t output_len) = 0;
};
