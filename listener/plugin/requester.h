#pragma once
#include <boost/any.hpp>
#include <boost/shared_ptr.hpp>

#include "plugin.h"

class receiver;
class publisher;

class requester : public plugin {
public:
	virtual void request(boost::any input, boost::any& output) = 0;

public:
    std::string                  receiver_name;
    boost::shared_ptr<receiver>  rec;

    std::string                  publisher_name;
    boost::shared_ptr<publisher> pub;
};
