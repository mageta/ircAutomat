#include <iostream>
#include <string>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include "info.h"
#include "pluginManager/pluginManager.hpp"

using namespace std;

int
main(int argc, char ** argv)
{
	try {
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
		cerr << "error: " << e.what() << endl;
		return 1;
	}

	PluginManager& pm = PluginManager::getPluginManager();

	pm.loadPlugin("plugins/plugin_testplugin.so");

	return 0;
}

