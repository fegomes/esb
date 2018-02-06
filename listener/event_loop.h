#pragma once

#include <thread>

#include "log.h"

#include "plugin/receiver.h"
#include "plugin/requester.h"
#include "plugin/publisher.h"

static void send(boost::any input) {
    
}

static boost::any get() {
    boost::any response("");
    return response;
}


class event_loop {
public:
    event_loop() = default;
    virtual ~event_loop() = default;

    template < class Rep, class Period >
    static void receive(receiver& rec, std::chrono::duration<Rep, Period> d) {
        core::log::scope s(__FUNCTION__);

        core::log::trace("Receiving");

        boost::any output;
        size_t len = 0;
        while (rec.is_running()) {
            output.clear();
            len = 0;
            rec.receive(output);
            if (len > 0) {
                send(output);
            }
            std::this_thread::sleep_for(d);
        }

        core::log::trace("Stop Receive");
    }

    template < class Rep, class Period >
    static void request(requester& req, std::chrono::duration<Rep, Period> d) {
        core::log::scope s(__FUNCTION__);

        core::log::trace("Run Requester");

        boost::any input;
        boost::any output;
        while (req.is_running()) {
            input = get();
            if (!input.empty()) {
                req.request(input, output);
                send(output);
            }
            std::this_thread::sleep_for(d);
        }

        core::log::trace("Stop Requester");
    }


    template < class Rep, class Period >
    static void publish(publisher& pub, std::chrono::duration<Rep, Period> d) {
        core::log::scope s(__FUNCTION__);

        core::log::trace("Run Publisher");

        boost::any input;
        while (pub.is_running()) {
            input = get();
            if (!input.empty()) {
                pub.send(input);
            }
            std::this_thread::sleep_for(d);
        }

        core::log::trace("Stop Publisher");
    }
};