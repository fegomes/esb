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

private:
	unsigned int _priority;
    bool _running;
};