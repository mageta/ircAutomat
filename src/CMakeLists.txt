#
# TARGET: ircAutomat
#

SET (ircAutomat_SRC		ircAutomat.cpp pluginManager/pluginManager.cpp)
SET (ircAutomat_INCLUDE		info.h pluginManager/pluginManager.hpp)
SET (ircAutomat_LIBS		${Boost_LIBRARIES} ${libircclient_LIBRARIES})
SET (ircAutomat_BIN		${CMAKE_PROJECT_NAME})

ADD_EXECUTABLE(${ircAutomat_BIN} ${ircAutomat_INCLUDE} ${ircAutomat_SRC})

TARGET_LINK_LIBRARIES(${ircAutomat_BIN} ${ircAutomat_LIBS})
SET_TARGET_PROPERTIES(${ircAutomat_BIN} PROPERTIES
        VERSION "${APPLICATION_VERSION_STRING}"
        LINK_FLAGS "-ldl")

INSTALL(TARGETS ${ircAutomat_BIN} DESTINATION bin)

#
# Subdirectories
#

if(Plugins)
        ADD_SUBDIRECTORY(plugins)
endif(Plugins)
