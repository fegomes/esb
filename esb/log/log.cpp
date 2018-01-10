#include "stdafx.h"
#include "log.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

namespace logging = boost::log;
namespace keywords = boost::log::keywords;
namespace sinks = boost::log::sinks;
namespace sources = boost::log::sources;

namespace core {

	log* core::log::_instance = nullptr;

	log::log()	{

	}
	
	log::~log()	{

	}

	log& log::get() {
		if (!_instance) {
			_instance = new log();
		}
		return *_instance;
	}

	void log::release() {
	}

	/*
	/* log.ini Example:
	/* [Log]
	/* Filename=log_%P_%Y-%m-%d-%H-%M-%S_%N.log
	/* Target=log
	/* RotationSize=10000
	/* Format=[%TimeStamp%][%Scope%][%Message%]
	/* Level=trace
	*/
	void log::init(const std::string& process, const std::string& ini){

		load(process, ini);

		logging::add_file_log(
			keywords::file_name = _file_name, // "log_" + process + "_%Y-%m-%d-%H-%M-%S_%N.log",
			keywords::target = _target, // "log"
			keywords::rotation_size = _rotation_size, // 1000000 * 1024 + 1024,
			keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
			keywords::format = _format // "[%TimeStamp%][%Scope%][%Message%]",
		);


		logging::core::get()->set_filter(
			logging::trivial::severity >= _level
		);
		
		add_common_attributes();
	}

	void log::add_common_attributes()
	{
		logging::add_common_attributes();
		auto core = logging::core::get();
		core->add_global_attribute("Scope", logging::attributes::named_scope());
	}

	void log::load(const std::string& process, const std::string& ini)
	{
		boost::property_tree::ptree pt;
		boost::property_tree::ini_parser::read_ini(ini, pt);

		_file_name = pt.get<std::string>("Log.Filename");
		_file_name.replace(_file_name.find("%P"), 2, process);

		_target = pt.get<std::string>("Log.Target");
		_rotation_size = pt.get<long>("Log.RotationSize");
		_format = pt.get<std::string>("Log.Format");
		_level = pt.get<severity_level>("Log.Level");
	}

}