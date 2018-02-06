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
#include "loop.h"

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

    std::vector<std::shared_ptr<std::thread> > threads;
    std::vector<boost::shared_ptr<receiver>> receivers;
    auto protocols = esb::ini::get().get_listeners();

    for (auto ci = protocols.begin(); ci != protocols.end(); ci++) {
        boost::filesystem::path lib_path(ci->second._path);
        boost::shared_ptr<receiver> recv = boost::dll::import<receiver>(ci->second._fullpath_lib,
                                                                        "plugin",
                                                                        boost::dll::load_mode::append_decorations
        );
        recv->load(ci->second._fullpath_ini);
        recv->set_priority(ci->second._priority);
        receivers.push_back(std::move(recv));
    }


    for (auto ci = receivers.begin(); ci != receivers.end(); ci++) {
        std::shared_ptr<std::thread> thread(new std::thread([&ci]() {  ci->get()->init(); loop::receive(*ci->get(), std::chrono::milliseconds( ci->get()->get_priority() )); }));
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




