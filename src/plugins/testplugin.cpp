#include <iostream>
#include <string>
#include <memory>

#include "ircAutomat/plugin.h"

using namespace std;

struct test_deleter
{
	void operator()(Plugin * p) {
		std::cout << "used custom deleter to delete " << p << std::endl;
		delete p;
	}
};

extern "C" {
	shared_ptr<Plugin> get_plugin();
}

shared_ptr<Plugin> get_plugin()
{
	shared_ptr<Plugin> plugin(new Plugin(), test_deleter());
	std::cout << "plugin " << plugin.get() << " created" << std::endl;
	return plugin;
}
