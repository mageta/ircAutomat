#
# TARGET: ircAutomat
#

# SET (ircAutomat_SRC		ircAutomat.cpp)
# SET (ircAutomat_INCLUDE		info.h)
# SET (ircAutomat_LIBS		${Boost_LIBRARIES} ${libircclient_LIBRARIES})
# SET (ircAutomat_BIN		${CMAKE_PROJECT_NAME})
# 
# ADD_EXECUTABLE(${ircAutomat_BIN} ${ircAutomat_INCLUDE} ${ircAutomat_SRC})
# 
# TARGET_LINK_LIBRARIES(${ircAutomat_BIN} ${ircAutomat_LIBS})
# SET_TARGET_PROPERTIES(${ircAutomat_BIN} PROPERTIES VERSION "${APPLICATION_VERSION_STRING}")
# 					
# INSTALL(TARGETS ${ircAutomat_BIN} DESTINATION bin)

# ADD_CUSTOM_TARGET(check ALL "${MAINFOLDER}/bin/${test_BIN}" DEPENDS ${test_BIN} COMMENT "Executing unit tests..." VERBATIM SOURCES ${test_SRCS})
# ADD_CUSTOM_TARGET(test "${MAINFOLDER}/bin/${test_BIN}" DEPENDS ${test_BIN} COMMENT "Executing unit tests..." VERBATIM SOURCES ${test_SRCS})
