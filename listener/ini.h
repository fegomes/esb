#pragma once
#include <string>
#include <unordered_map>
#include <memory>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/algorithm/string.hpp>

#include "plugin/receiver.h"
#include "plugin/publisher.h"
#include "plugin/requester.h"

namespace esb {

	class ini {
	private:
		ini() = default;
		virtual ~ini() = default;

	private:
		static ini* _instance;

	public:
        typedef std::unordered_map<std::string, boost::shared_ptr<receiver>>  receivers;
        typedef std::unordered_map<std::string, boost::shared_ptr<publisher>> publishers;
        typedef std::unordered_map<std::string, boost::shared_ptr<requester>> requesters;

		static ini& get() {
			if (!_instance) {
				_instance = new ini();
			}
			return *_instance;
		}
		static void release() {
			if (_instance) {
				delete _instance;
			}
		}

	public:

		void init(const std::string& filename) {
			_filename = filename;
			boost::property_tree::iptree pt;
			boost::property_tree::ini_parser::read_ini(filename, pt);

            load_receivers(pt);
            load_publishers(pt);
            load_requesters(pt);
          
		}

		const receivers& get_receivers() const {
			return _receivers;
		}

        const requesters& get_requesters() const {
            return _requesters;
        }

        const publishers& get_publishers() const {
            return _publishers;
        }

    private:
        void load_receivers(boost::property_tree::iptree& pt) {
            std::vector<std::string> v_receivers;
            std::string receivers = pt.get<std::string>("general.receivers");
            boost::split(v_receivers, receivers, boost::is_any_of(","));

            for (auto ci = v_receivers.begin(); ci != v_receivers.end(); ci++) {

                std::string path = pt.get<std::string>(*ci + ".path", ".");
                std::string lib = pt.get<std::string>(*ci + ".lib");

                boost::filesystem::path lib_path(path);

                try {
                    boost::shared_ptr<receiver> recv = boost::dll::import<receiver>(
                        lib_path.string() + lib,
                        "plugin",
                        boost::dll::load_mode::append_decorations
                        );

                    recv->set_ini_file(pt.get<std::string>(*ci + ".ini", "config.ini"));
                    recv->publisher_name = pt.get<std::string>(*ci + ".publisher");
                    recv->set_priority(pt.get<unsigned int>(*ci + ".priority", 500));
                    recv->set_library(lib);
                    recv->set_path(lib_path.string());
                    recv->load(recv->fullpath_ini());

                    _receivers[*ci] = std::move(recv);
                }
                catch (std::exception& e) {
                    std::cout << e.what() << std::endl;
                }
            }
        }

        void load_publishers(boost::property_tree::iptree& pt) {
            std::vector<std::string> v_publishers;
            std::string publishers = pt.get<std::string>("general.publishers");
            boost::split(v_publishers, publishers, boost::is_any_of(","));

            for (auto ci = v_publishers.begin(); ci != v_publishers.end(); ci++) {

                std::string path = pt.get<std::string>(*ci + ".path", ".");
                std::string lib = pt.get<std::string>(*ci + ".lib");

                boost::filesystem::path lib_path(path);

                try {
                    boost::shared_ptr<publisher> pub = boost::dll::import<publisher>(
                        lib_path.string() + lib,
                        "plugin",
                        boost::dll::load_mode::append_decorations
                        );

                    pub->set_ini_file(pt.get<std::string>(*ci + ".ini", "config.ini"));
                    pub->receiver_name = pt.get<std::string>(*ci + ".receiver");
                    pub->set_priority(pt.get<unsigned int>(*ci + ".priority", 500));
                    pub->set_library(lib);
                    pub->set_path(lib_path.string());
                    pub->load(pub->fullpath_ini());

                    _publishers[*ci] = std::move(pub);
                }
                catch (std::exception& e) {
                    std::cout << e.what() << std::endl;
                }
            }
        }

        void load_requesters(boost::property_tree::iptree& pt) {
            std::vector<std::string> v_requesters;
            std::string requesters = pt.get<std::string>("general.receivers");
            boost::split(v_requesters, requesters, boost::is_any_of(","));

            for (auto ci = v_requesters.begin(); ci != v_requesters.end(); ci++) {

                std::string path = pt.get<std::string>(*ci + ".path", ".");
                std::string lib = pt.get<std::string>(*ci + ".lib");

                boost::filesystem::path lib_path(path);

                try {
                    boost::shared_ptr<requester> req = boost::dll::import<requester>(
                        lib_path.string() + lib,
                        "plugin",
                        boost::dll::load_mode::append_decorations
                        );

                    req->set_ini_file(pt.get<std::string>(*ci + ".ini", "config.ini"));
                    req->publisher_name = pt.get<std::string>(*ci + ".publisher");
                    req->receiver_name = pt.get<std::string>(*ci + ".receiver");
                    req->set_priority(pt.get<unsigned int>(*ci + ".priority", 500));
                    req->set_library(lib);
                    req->set_path(lib_path.string());
                    req->load(req->fullpath_ini());

                    _requesters[*ci] = std::move(req);
                }
                catch (std::exception& e) {
                    std::cout << e.what() << std::endl;
                }
            }
        }
		

	private:
		std::string _filename;
        receivers   _receivers;
        publishers  _publishers;
        requesters  _requesters;
	};

	ini* ini::_instance = nullptr;
}

