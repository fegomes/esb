#pragma once
#include <string>
#include <unordered_map>
#include <memory>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/algorithm/string.hpp>

struct listener {
	std::string  ini;
	std::string  lib;
	std::string  path;
	unsigned int priority;
	std::string  fullpath_ini;
	std::string  fullpath_lib;
};

namespace esb {

	class ini {
	private:
		ini() = default;
		virtual ~ini() = default;

	private:
		static ini* _instance;

	public:
		typedef std::unordered_map<std::string, listener> listeners_map;
        typedef std::vector<boost::shared_ptr<receiver>> receivers;

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

			std::string listeners = pt.get<std::string>("General.listeners");
			std::vector<std::string> v_listeners;
			boost::split(v_listeners, listeners, boost::is_any_of(","));

			for (auto ci = v_listeners.begin(); ci != v_listeners.end(); ci++) {
				listener l;
				l.path = pt.get<std::string>(*ci + ".path");
				l.ini = pt.get<std::string>(*ci + ".ini");
				l.lib = pt.get<std::string>(*ci + ".lib");
				l.priority = pt.get<unsigned int>(*ci + ".priority");
				l.fullpath_ini = l.path + '\\' + l.ini;
				l.fullpath_lib = l.path + '\\' + l.lib;
				_listeners[*ci] = std::move(l);
			}

            for (auto ci = _listeners.begin(); ci != _listeners.end(); ci++) {
                boost::filesystem::path lib_path(ci->second.path);
                boost::shared_ptr<receiver> recv = boost::dll::import<receiver>(ci->second.fullpath_lib,
                    "plugin",
                    boost::dll::load_mode::append_decorations
                    );
                recv->load(ci->second.fullpath_ini);
                recv->set_priority(ci->second.priority);
                _receivers.push_back(std::move(recv));
            }
		}

		const receivers& get_receivers() const {
			return _receivers;
		}

    private:

		

	private:
		listeners_map _listeners;
		std::string   _filename;
        receivers     _receivers;
	};

	ini* ini::_instance = nullptr;
}

