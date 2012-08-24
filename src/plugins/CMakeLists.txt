#
# TARGET: testPlugin
#

SET (testPlugin_VERSION		1)

SET (testPlugin_SRC		testplugin.cpp)
SET (testPlugin_INCLUDE		)
SET (testPlugin_LIBS		${Boost_LIBRARIES} ${libircclient_LIBRARIES})
SET (testPlugin_BIN		testplugin)

ADD_LIBRARY(${testPlugin_BIN} MODULE ${testPlugin_INCLUDE} ${testPlugin_SRC})

TARGET_LINK_LIBRARIES(${testPlugin_BIN} ${testPlugin_LIBS})
SET_TARGET_PROPERTIES(${testPlugin_BIN} PROPERTIES VERSION "${testPlugin_VERSION}"
					LIBRARY_OUTPUT_DIRECTORY ${PLUGIN_OUTPUT_PATH}
					PREFIX "${PLUGIN_PREFIX}")
					
INSTALL(TARGETS ${testPlugin_BIN} DESTINATION bin/plugins)
