#pragma once
#include <boost/any.hpp>

#include "plugin.h"

class receiver : public plugin {
public:
	virtual void receive(boost::any& output) = 0;
};
