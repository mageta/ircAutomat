#include "pluginManager.hpp"

#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>

#include <dlfcn.h>

const char * PluginManager::DEFAULT_PATH = "./plugins/";

PluginManager::PluginManager() :
	dlHandles(), plugins()
{

}

PluginManager::~PluginManager()
{
	plugins.clear();
	dlHandles.clear();
}

PluginManager&
PluginManager::getPluginManager()
{
	static PluginManager pm;
	return pm;
}

struct dlHandleDelete
{
	void operator()(void * dlHandle) {
#ifdef DEBUG
		std::cout << "delete dlHandle " << dlHandle
			     << std::endl;
#endif
		dlclose(dlHandle);
	}
};

std::shared_ptr<Plugin>
PluginManager::loadPlugin(const std::string & file)
{
	char *dlerr;
	std::shared_ptr<void> dlHandle;
	std::shared_ptr<Plugin> plugin;
	std::shared_ptr<Plugin> (*get_plugin)();

	std::cout << "load Plugin " << file << std::endl;

	dlHandle = std::shared_ptr<void>(
		dlopen(file.c_str(), RTLD_NOW),
		dlHandleDelete()
	);

	if(!dlHandle.get()) {
		dlerr = dlerror();
		std::cerr << "err: " << dlerr << std::endl;
		throw std::runtime_error(std::string(dlerr));
	}

	std::cout << "dlopen of " << file << " succeeded" << std::endl;

	dlerror();

	/* don't ask me, DLOPEN(3) told me so :D */
	*(void **) (&get_plugin) = dlsym(dlHandle.get(), "get_plugin");

	if((dlerr = dlerror()) != NULL) {
		std::cerr << "err: " << dlerr << std::endl;
		throw std::runtime_error(std::string(dlerr));
	}

	std::cout << "dlsym(get_plugin) on " << file << " succeeded"
		  << std::endl;

	dlerror();

	plugin = (*get_plugin)();

	if(!plugin.get()) {
		std::cerr << "err: plugin returned nothing" << std::endl;
		throw std::runtime_error("err: plugin returned nothing");
	}

	dlHandles.push_back(dlHandle);

	plugins.insert(std::pair<unsigned long, std::shared_ptr<Plugin>>(
			       (unsigned long) dlHandle.get(), plugin));

	return plugin;
}

std::vector<std::shared_ptr<Plugin>>
PluginManager::loadPlugins(const std::string & dir)
{
	return std::vector<std::shared_ptr<Plugin>>();
}
