#include "pluginManager.hpp"

#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>
#include <algorithm>

#include <boost/filesystem.hpp>

#include <dlfcn.h>

#include "log.h"

const char * PluginManager::DEFAULT_PATH = "./plugins/";

PluginManager::PluginManager() :
	dlHandles(), plugins()
{
	FILE_LOG(logDEBUG) << "create PluginManager (singleton)";
}

PluginManager::~PluginManager()
{
	FILE_LOG(logDEBUG) << "destory PluginManager";

	FILE_LOG(logDEBUG) << "clear Plugins";
	plugins.clear();

	FILE_LOG(logDEBUG) << "clear loaded dlHandles";
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
		FILE_LOG(logDEBUG) << "delete dlHandle"
				   << " (adr: " << dlHandle << ")";
		dlclose(dlHandle);
	}
};

std::shared_ptr<Plugin>
PluginManager::loadPlugin(const std::string & file)
{
	char *dlerr;
	std::shared_ptr<void> dlHandle;
	std::shared_ptr<Plugin> plugin;
	std::shared_ptr<Plugin> (*get_plugin)(); /* function-pointer */

	FILE_LOG(logDEBUG) << "load Plugin (file: " << file << ")";

	dlHandle = std::shared_ptr<void>(
		dlopen(file.c_str(), RTLD_NOW),
		dlHandleDelete()
	);

	if(!dlHandle.get()) {
		dlerr = dlerror();

		FILE_LOG(logERROR) << "couldn't get a dlHandle (file: " << file
				   << "), (err: " << dlerr << ")";
		throw std::runtime_error(std::string(dlerr));
	}

	FILE_LOG(logDEBUG) << "got dlHandle (adr: " << dlHandle.get() << ")"
			   << " (file: " << file << ")";

	if (std::count(dlHandles.begin(), dlHandles.end(), dlHandle)) {
		FILE_LOG(logWARNING) << "plugin already loaded"
				     << " (file: " << file << ")";

		dlerror(); /* clear error-state */

		try {
			plugin = plugins.at((unsigned long) dlHandle.get());

			return plugin;
		} catch(std::out_of_range& e) {
			FILE_LOG(logERROR) << "no plugin found for a already "
					   << "loaded dlHandle"
					   << " (file: " << file << ")";
			throw;
		}
	}

	dlerror(); /* clear error-state */

	/* don't ask me, DLOPEN(3) told me so :D */
	*(void **) (&get_plugin) = dlsym(dlHandle.get(), "get_plugin");

	if((dlerr = dlerror()) != NULL) {
		FILE_LOG(logERROR) << "couldn't find the get_plugin-symbol"
				   << " (file: " << file << "), (err: " << dlerr
				   << ")";
		throw std::runtime_error(std::string(dlerr));
	}

	FILE_LOG(logDEBUG) << "got get_plugin-symbol (file: " << file << ")";

	dlerror(); /* clear error-state */

	plugin = (*get_plugin)();

	if(!plugin.get()) {
		FILE_LOG(logERROR) << "the plugin returned (null)"
				   << " (file: " << file << ")";
		throw std::runtime_error("err: plugin returned nothing");
	}

	FILE_LOG(logDEBUG) << "loaded plugin (adr: " << plugin.get() << ")"
			   << " (file: " << file << ")";

	dlHandles.push_back(dlHandle);

	plugins.insert(std::pair<unsigned long, std::shared_ptr<Plugin>>(
			       (unsigned long) dlHandle.get(), plugin));

	return plugin;
}

std::vector<std::shared_ptr<Plugin>>
PluginManager::loadPlugins(const std::string & dir)
{
	std::vector<std::shared_ptr<Plugin>> foundPlugins;

	using namespace boost::filesystem;

	path pdir(dir);

	try {
		if(exists(pdir) && is_directory(pdir)) {
			for(auto entries = directory_iterator(pdir);
			    entries != directory_iterator(); ++entries) {
				FILE_LOG(logDEBUG) << "PluginManager::"
						   << "loadPlugin("
						   << *entries << ");";

				try {
					foundPlugins.push_back(loadPlugin(
						entries->path().native()));
				} catch (const std::runtime_error& re) {
					FILE_LOG(logWARNING) << "loadPlugin("
							     << *entries << ");"
							     << " failed with: "
							     << re.what();
				}
			}
		} else {
			FILE_LOG(logWARNING) << "'" << dir << "'"
					     << "could not be found or is not"
					     << " a directory!";
		}
	} catch(const filesystem_error& fe) {
		FILE_LOG(logERROR) << "filesystem error: " << fe.what();
		throw std::runtime_error(fe.what());
	}

	/*
	 * remove plugins that were inserted multiple times due to be tried to
	 * be loaded multiple times
	 */
	std::sort(foundPlugins.begin(), foundPlugins.end());

	auto last = std::unique(foundPlugins.begin(), foundPlugins.end());
	foundPlugins.erase(last, foundPlugins.end());

	return foundPlugins;
}
