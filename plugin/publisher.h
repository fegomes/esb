#pragma once
#include <boost/any.hpp>

#include "plugin.h"

class publisher : public plugin {
public:
	virtual void send(boost::any input, size_t input_len) = 0;
};
