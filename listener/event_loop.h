#pragma once

#include <thread>

#include "log.h"

#include "plugin/receiver.h"
#include "plugin/requester.h"
#include "plugin/publisher.h"

class event_loop {
public:
    event_loop() = default;
    virtual ~event_loop() = default;

    template < class Rep, class Period >
    static void receive(receiver& rec, std::chrono::duration<Rep, Period> d) {
        core::log::scope s(__FUNCTION__);

        core::log::trace("receiving");

        boost::any output;
        while (rec.is_running()) {
            output.clear();
            rec.receive(output);
            if (!output.empty()) {
                rec.pub.get()->send(output);
                core::log::trace("received");
            }
            std::this_thread::sleep_for(d);
        }

        core::log::trace("stop receive");
    }

    template < class Rep, class Period >
    static void request(requester& req, std::chrono::duration<Rep, Period> d) {
        core::log::scope s(__FUNCTION__);

        core::log::trace("run requester");

        boost::any input;
        boost::any output;
        while (req.is_running()) {
            input.clear();
            output.clear();
            req.rec.get()->receive(input);
            if (!input.empty()) {
                req.request(input, output);
                req.pub.get()->send(output);
                core::log::trace("requested");
            }
            std::this_thread::sleep_for(d);
        }

        core::log::trace("stop requester");
    }


    template < class Rep, class Period >
    static void publish(publisher& pub, std::chrono::duration<Rep, Period> d) {
        core::log::scope s(__FUNCTION__);

        core::log::trace("run publisher");

        boost::any input;
        while (pub.is_running()) {
            input.clear();
            pub.rec.get()->receive(input);
            if (!input.empty()) {
                pub.send(input);
                core::log::trace("published");
            }
            std::this_thread::sleep_for(d);
        }

        core::log::trace("stop publisher");
    }
};