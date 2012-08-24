#ifndef PLUGIN_MANAGER_HPP
#define PLUGIN_MANAGER_HPP

#include "ircAutomat/plugin.h"

#include <vector>
#include <map>
#include <memory>

class PluginManager
{
public:
	static const char * DEFAULT_PATH;

private:
	std::vector<std::shared_ptr<void>> dlHandles;
	std::map<unsigned long, std::shared_ptr<Plugin>> plugins;

private:
	PluginManager();
	PluginManager(const PluginManager &) {}
	PluginManager& operator=(const PluginManager &) { return *this; }
	~PluginManager();

public:
	static PluginManager& getPluginManager();

	std::shared_ptr<Plugin> loadPlugin(const std::string & file);
	std::vector<std::shared_ptr<Plugin>>
		loadPlugins(const std::string & dir);
};

#endif /* PLUGIN_MANAGER_HPP */
