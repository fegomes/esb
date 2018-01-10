#pragma once
class plugin {
protected:
	plugin() = default;
	~plugin() = default;
public:
	virtual void load(const std::string& filename) = 0;
	virtual void init() = 0;
	virtual void end() = 0;
};