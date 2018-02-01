#pragma once
#include <string>
#include <unordered_map>
#include <memory>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/algorithm/string.hpp>

struct listener {
	std::string  _ini;
	std::string  _lib;
	std::string  _path;
	unsigned int _priority;
	std::string  _fullpath_ini;
	std::string  _fullpath_lib;
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
				l._path = pt.get<std::string>(*ci + ".path");
				l._ini = pt.get<std::string>(*ci + ".ini");
				l._lib = pt.get<std::string>(*ci + ".lib");
				l._priority = pt.get<unsigned int>(*ci + ".priority");
				l._fullpath_ini = l._path + '\\' + l._ini;
				l._fullpath_lib = l._path + '\\' + l._lib;
				_listeners[*ci] = std::move(l);
			}
		}

		const listeners_map& get_listeners() const {
			return _listeners;
		}
		

	private:
		listeners_map _listeners;
		std::string   _filename;
	};

	ini* ini::_instance = nullptr;
}

