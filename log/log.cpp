#include "log.h"

#include <mutex>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

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
		_logger = spdlog::rotating_logger_st(process, _target + _file_name, _rotation_size, 100);
		_logger->set_level(_level);
		_logger->set_pattern(_format);

	}

	void log::load(const std::string& process, const std::string& ini)
	{
		boost::property_tree::ptree pt;
		boost::property_tree::ini_parser::read_ini(ini, pt);

		_file_name = pt.get<std::string>("General.Filename");
		_file_name.replace(_file_name.find("%P"), 2, process);

		_target = pt.get<std::string>("General.Target");
		_rotation_size = pt.get<long>("General.RotationSize");
		_format = pt.get<std::string>("General.Format");
		_level = spdlog::level::to_level_enum(pt.get<std::string>("General.Level").c_str());

	}


}