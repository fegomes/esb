#pragma once
class plugin {
protected:
    plugin() : _priority(1), _running(true) {};
    ~plugin() = default;

public:
    virtual void load(const std::string& filename) = 0;
    virtual void init() = 0;
    virtual void end() = 0;

    void set_priority(unsigned int p) {
        if (p) {
            _priority = p;
        }
    }

    const unsigned int get_priority() const {
        return _priority;
    }

    void stop() {
        _running = false;
    }

    const bool is_running() const {
        return _running;
    }

    void set_ini_file(const std::string& ini) {
        _ini = ini;
    }

    const std::string& ini() const {
        return _ini;
    }

    void set_library(const std::string& lib) {
        _lib = lib;
    }

    const std::string& library() const {
        return _lib;
    }

    void set_path(const std::string& path) {
        _path = path;
    }

    const std::string& path() const {
        return _path;
    }

    const std::string fullpath_ini() {
        return _path + '\\' + _ini;
    }

    const std::string fullpath_lib() {
        return _path + '\\' + _lib;
    }

protected:
	unsigned int _priority;
    bool         _running;
    std::string  _ini;
    std::string  _lib;
    std::string  _path;
};