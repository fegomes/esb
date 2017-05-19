#pragma once

// std
#include <string>

// boost
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include <boost/log/utility/string_literal.hpp>

using namespace boost::log::trivial;

namespace core {

	class log : public std::ostringstream {
		private:
			log();
			virtual ~log();

		private:
			static log* _instance;

		public:
			static log& get();
			static void release();
			void init(const std::string& process, const std::string& file_name) throw(std::exception);

		private:
			void add_common_attributes();
			void log::load(const std::string& process, const std::string& ini);

		private:
			std::string    _file_name;
			std::string    _target;
			long           _rotation_size;
			std::string    _format;
			severity_level _level;
	};
}