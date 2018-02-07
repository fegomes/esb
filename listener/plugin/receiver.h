#pragma once
#include <boost/any.hpp>

#include "plugin.h"
#include "publisher.h"

class receiver : public plugin {
public:
	virtual void receive(boost::any& output) = 0;

public:
    std::string                  publisher_name;
    boost::shared_ptr<publisher> pub;
};
