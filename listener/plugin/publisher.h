#pragma once
#include <boost/any.hpp>
#include <boost/shared_ptr.hpp>

#include "plugin.h"

class receiver;

class publisher : public plugin {
public:
	virtual void send(boost::any input) = 0;

public:
    std::string                  receiver_name;
    boost::shared_ptr<receiver>  rec;
};
