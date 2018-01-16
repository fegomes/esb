#pragma once
class plugin {
protected:
	plugin() : _priority(1) {};
	~plugin() = default;
public:
	virtual void load(const std::string& filename) = 0;
	virtual void init() = 0;
	virtual void end() = 0;

	void set_priority(unsigned int p){
		if (p) {
			_priority = p;
		}
	}
	
	const unsigned int get_priority() const {
		return _priority;
	}

private:
	unsigned int _priority;
};