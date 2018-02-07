// http.cpp : Defines the exported functions for the DLL application.
//

#include <iostream>
#include <string>
#include <queue>
#include <mutex>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/config.hpp> 
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include "plugin/publisher.h"

namespace comm {

    class shared : public publisher {
    public:
        shared() {
           
        }

        void load(const std::string& filename) override {
            boost::property_tree::iptree pt;
            boost::property_tree::ini_parser::read_ini(filename, pt);
        }

        void init() override {
           

        }

        void send(boost::any input) {
            if (input.empty()) {
                return;
            }
            _lock.lock();
            std::cout << boost::any_cast<std::string>(input) << std::endl;
            _lock.unlock();
        }

        void end() override {

        }

        virtual ~shared() = default;
    private:
        std::mutex   _lock;
    };

    extern "C" BOOST_SYMBOL_EXPORT shared plugin;
    shared plugin;

} // namespace my_namespace

