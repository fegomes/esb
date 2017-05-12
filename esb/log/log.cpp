#include "stdafx.h"
#include "log.h"

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

	void log::init(const std::string& process, logging::trivial::severity_level level) const {
		logging::add_file_log(
			keywords::file_name = "log_" + process + "_%Y-%m-%d-%H-%M-%S_%N.log",
			keywords::rotation_size = 10 * 1024 + 1024,
			keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
			keywords::format = "[%TimeStamp%][%Scope%][%Message%]"
		);

		logging::core::get()->set_filter(
			logging::trivial::severity >= level
		);
		
		add_common_attributes();
	}

	void log::add_common_attributes() const
	{
		logging::add_common_attributes();
		auto core = logging::core::get();
		core->add_global_attribute("Scope", logging::attributes::named_scope());
	}

}