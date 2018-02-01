#pragma once

#include <string>
#include <spdlog/spdlog.h>

namespace core {

	class log {
	private:
		log();
		virtual ~log();

	private:
		static log* _instance;

	public:
		static log& get();
		static void release();
		void init(const std::string& process, const std::string& file_name);
		spdlog::logger& logger() {
			return *_logger.get();
		}

	private:
		void load(const std::string& process, const std::string& ini);

	private:
		std::string                     _file_name;
		std::string                     _target;
		long                            _rotation_size;
		std::string                     _format;
		spdlog::level::level_enum       _level;
		std::shared_ptr<spdlog::logger> _logger;

	public:
		template <typename T> 
		static void trace(const T& v) {
			core::log::get().logger().trace(v);
		}
		template <typename T> 
		static void debug(const T& v) {
			core::log::get().logger().debug(v);
		}
		template <typename T> 
		static void info(const T& v) {
			core::log::get().logger().info(v);
		}
		template <typename T> 
		static void warn(const T& v) {
			core::log::get().logger().warn(v);
		}
		template <typename T> 
		static void error(const T& v) {
			core::log::get().logger().error(v);
		}
		template <typename T> 
		static void critical(const T& v) {
			core::log::get().logger().critical(v);
		}
		template <typename Arg1, typename... Args> 
		static void trace(const char* fmt, const Arg1& arg1, const Args&... args) {
			core::log::get().logger().trace(fmt, arg1, args...);
		}
		template <typename Arg1, typename... Args> 
		static void debug(const char* fmt, const Arg1&  arg1, const Args&... args) {
			core::log::get().logger().debug(fmt, arg1, args...);
		}
		template <typename Arg1, typename... Args> 
		static void info(const char* fmt, const Arg1&  arg1, const Args&... args) {
			core::log::get().logger().info(fmt, arg1, args...);
		}
		template <typename Arg1, typename... Args> 
		static void warn(const char* fmt, const Arg1&  arg1, const Args&... args) {
			core::log::get().logger().warn(fmt, arg1, args...);
		}
		template <typename Arg1, typename... Args> 
		static void error(const char* fmt, const Arg1&  arg1, const Args&... args) {
			core::log::get().logger().error(fmt, arg1, args...);
		}
		template <typename Arg1, typename... Args> 
		static void critical(const char* fmt, const Arg1& arg1, const Args&... args) {
			core::log::get().logger().critical(fmt, arg1, args...);
		}

		class score {
		public:
			score(const std::string& name) {
				info("Begin");
			}
			~score() {
				info("End");
			}

		private:
			std::string _name;
		};
	};

}

