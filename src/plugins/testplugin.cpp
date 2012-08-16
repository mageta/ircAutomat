#include <iostream>
#include <string>

#include "ircAutomat/plugin.h"

extern "C" {
	Plugin * get_plugin();
}

Plugin *
get_plugin()
{

	return 0;
}
