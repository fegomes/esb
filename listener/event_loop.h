#pragma once

#include <thread>

#include "log.h"
#include "plugin/receiver.h"

class event_loop {
public:
    event_loop() = default;
    virtual ~event_loop() = default;

    template < class Rep, class Period >
    static void receive(receiver& rec, std::chrono::duration<Rep, Period> d) {
        boost::any output;
        size_t len = 0;
        while (rec.is_running()) {
            output.clear();
            len = 0;
            rec.receive(output, len);
            if (len > 0) {
                core::log::trace("teste");
            }
            std::this_thread::sleep_for(d);
        }

        core::log::trace("Stop Receive");
    }
};

