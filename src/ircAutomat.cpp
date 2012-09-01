#include <iostream>
#include <string>
#include <cstdio>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include "info.h"
#include "pluginManager/pluginManager.hpp"
#include "log.h"

using namespace std;

int
main(int argc, char ** argv)
{
	FILELog::ReportingLevel().Set(logDEBUG);

	try {
		FILE_LOG(logDEBUG) << "starting cli-options-reading";

		po::options_description desc("Allowed options");
		desc.add_options()
			("help,h", "produce help message")
			("version,v", "shows version")
		;

		po::variables_map vm;
		po::store(
			po::command_line_parser(argc, argv).options(desc).run(),
			vm);
		po::notify(vm);

		if (vm.count("help")) {
			cout << desc;
			return 0;
		}

		if (vm.count("version")) {
			cout << APPLICATION_NAME
			     << " (" << APPLICATION_CODENAME << ") "
				"- " << APPLICATION_VERSION_STRING << endl
			     << "Copyright (c) " << APPLICATION_COPYRIGHT_YEARS
			     << " @ " << APPLICATION_VENDOR_NAME << endl
			     << "There is NO warranty; not even for "
			     << "MERCHANTABILITY or FITNESS FOR A PARTICULAR" << endl
			     << "PURPOSE." << endl;

			return 0;
		}
	}
	catch(exception& e) {
		FILE_LOG(logERROR) << "error: " << e.what();
		return 1;
	}

	PluginManager& pm = PluginManager::getPluginManager();

	auto plugins = pm.loadPlugins("plugins");
	FILE_LOG(logDEBUG) << "loaded plugins: " << plugins.size();

	for (auto it = plugins.begin(); it != plugins.end(); ++it)
		FILE_LOG(logDEBUG) << "plugin: <" << (*it).get() <<">,"
				   << " count: " << (*it).use_count();

	return 0;
}

