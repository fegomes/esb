#include "log.h"
#include <iostream>
#include <thread>
#include <memory>
#include <chrono>

#include <boost/dll/import.hpp>
#include <boost/filesystem.hpp>
#include <boost/bind.hpp>

#include "plugin/receiver.h"

#include "ini.h"
#include "event_loop.h"

int init() {
    try {
        core::log::get().init("esb", "log.ini");
        esb::ini::get().init("listener.ini");
    }
    catch (...) {
        return false;
    }
    return true;
}

int done() {
    try {
        core::log::release();
        esb::ini::release();
    }
    catch (...) {
        return false;
    }
    return true;
}

int main(int argc, char* argv[])
{
    if (!init()) {
        return 1;
    }

    core::log::score s(__FUNCTION__);

    std::vector<std::shared_ptr<std::thread> > threads;
    esb::ini::receivers receivers = esb::ini::get().get_receivers();
    
    for (auto ci = receivers.begin(); ci != receivers.end(); ci++) {
        std::shared_ptr<std::thread> thread(new std::thread([&ci]() {  ci->get()->init(); event_loop::receive(*ci->get(), std::chrono::milliseconds( ci->get()->get_priority() )); }));
        threads.push_back(std::move(thread));
    }

    for (auto ci = threads.begin(); ci != threads.end(); ci++) {
        ci->get()->join();
    }

    if(!done()){
        return 1;
    }

    return 0;
}




