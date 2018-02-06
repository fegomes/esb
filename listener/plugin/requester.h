#pragma once
#include <boost/any.hpp>

#include "plugin.h"

class requester : public plugin {
public:
	virtual void request(boost::any input, boost::any& output) = 0;
};
