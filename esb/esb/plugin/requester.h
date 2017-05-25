#pragma once
#include <boost/any.hpp>

#include "plugin.h"

class requester : public plugin {
public:
	virtual void request(boost::any input, size_t input_len, boost::any output, size_t output_len) = 0;
};
