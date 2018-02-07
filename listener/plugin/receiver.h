#pragma once
#include <boost/any.hpp>
#include <boost/shared_ptr.hpp>

#include "plugin.h"

class publisher;

class receiver : public plugin {
public:
	virtual void receive(boost::any& output) = 0;

public:
    std::string                  publisher_name;
    boost::shared_ptr<publisher> pub;
};
