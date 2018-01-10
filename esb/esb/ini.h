#pragma once
#include <string>
#include <unordered_map>
#include <memory>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/algorithm/string.hpp>

struct protocol {
	std::string _file;
	std::string _path;
};

namespace esb {

	class ini {
	private:
		ini() = default;
		virtual ~ini() = default;

	private:
		static ini* _instance;

	public:
		typedef std::unordered_map<std::string, protocol> protocols_map;

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
			boost::property_tree::ptree pt;
			boost::property_tree::ini_parser::read_ini(filename, pt);

			std::string protocols = pt.get<std::string>("General.Protocols");
			std::vector<std::string> v_protocols;
			boost::split(v_protocols, protocols, boost::is_any_of(","));

			for (auto ci = v_protocols.begin(); ci != v_protocols.end(); ci++) {
				protocol p;
				p._file = pt.get<std::string>(*ci + ".file");
				p._path = pt.get<std::string>(*ci + ".path");
				_protocols[*ci] = std::move(p);
			}
		}

		const protocols_map get_protocols() const {
			return _protocols;
		}

	private:
		protocols_map _protocols;
		std::string _filename;
	};

	ini* ini::_instance = nullptr;
}

