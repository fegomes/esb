// http.cpp : Defines the exported functions for the DLL application.
//

#include <iostream>
#include <string>
#include <queue>
#include <mutex>

#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include "plugin/publisher.h"

using namespace boost::interprocess;

namespace comm {

    class shared : public publisher {
    public:
        shared() {
           
        }

        void load(const std::string& filename) override {
            boost::property_tree::iptree pt;
            boost::property_tree::ini_parser::read_ini(filename, pt);

            _name = pt.get<std::string>("general.name", "temp");
            _count = pt.get<unsigned int>("general.count", 512);
            _size = pt.get<unsigned int>("general.size", 10000);
        }

        
        void init() override {
            message_queue::remove(_name.c_str());
            _mq.reset(new message_queue(create_only, _name.c_str(), _count, _size));
        }

        void send(boost::any input) {
            if (input.empty()) {
                return;
            }
            
            _lock.lock();

            try {
                if (input.type() == typeid(int)) {
                    int value = boost::any_cast<int>(input);
                    _mq->try_send(&value, sizeof(value), 0);
                }
                else if (input.type() == typeid(std::string)) {
                    std::string value = boost::any_cast<std::string>(input);
                    _mq->try_send(value.c_str(), value.size(), 0);
                }
            }
            catch (interprocess_exception& e) {
                std::cout << e.what() << std::endl;
            }

            _lock.unlock();

            char value[10000] = { '\0' } ;
            size_t len;
            size_t priority;
            _lock.lock();
            _mq->receive(&value, 10000, len, priority);
            _lock.unlock();            
        }

        void end() override {

        }

        virtual ~shared() = default;
    private:
        std::unique_ptr<message_queue>  _mq;
        std::string                     _name;
        unsigned int                    _size;
        unsigned int                    _count;
        std::mutex                      _lock;
    };

    extern "C" BOOST_SYMBOL_EXPORT shared plugin;
    shared plugin;

} // namespace my_namespace

