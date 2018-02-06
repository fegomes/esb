#pragma once
#include <vector>

#include <boost/shared_ptr.hpp>

#include "plugin/receiver.h"
#include "plugin/publisher.h"
#include "plugin/requester.h"

class listener {
public:
    listener() = default;
    virtual ~listener() = default;

private:
    std::vector<boost::shared_ptr<receiver>> _receivers;
};