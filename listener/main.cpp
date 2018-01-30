#include "log.h"
#include <iostream>
#include <thread>
#include <memory>
#include <chrono>

#include <boost/dll/import.hpp>
#include <boost/filesystem.hpp>
#include <boost/bind.hpp>

#include "ini.h"
#include "plugin/receiver.h"

int init();
template< typename Rep, typename Period>
inline void receive(receiver& rec, std::chrono::duration<Rep, Period> &d);

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
        std::shared_ptr<std::thread> thread(new std::thread([&ci]() { ci->get()->init(); }));
        threads.push_back(std::move(thread));
    }

    for (auto ci = receivers.begin(); ci != receivers.end(); ci++) {
        std::shared_ptr<std::thread> thread(new std::thread([&ci]() {  receive(*ci->get(), std::chrono::milliseconds(ci->get()->get_priority() * 50)); }));
        threads.push_back(std::move(thread));
    }

    for (auto ci = threads.begin(); ci != threads.end(); ci++) {
        ci->get()->join();
    }

    return 0;
}

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

template< typename Rep, typename Period>
inline void receive(receiver& rec, std::chrono::duration<Rep, Period> &d) {
    boost::any output;
    size_t len = 0;
    while (true) {
        output.clear();
        len = 0;
        rec.receive(output, len);
        if (len > 0) {
            core::log::trace("teste");
        }
        std::this_thread::sleep_for(d);
    }
}