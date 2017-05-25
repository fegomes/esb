#pragma once
class plugin {
protected:
	plugin() {};
	~plugin() {};
public:
	virtual void init() = 0;
	virtual void end() = 0;
};