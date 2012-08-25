#
# TARGET: logging
#

SET (logging_SRC		logman.cpp)
SET (logging_INCLUDE		fenced.h logman.h log.h)
SET (logging_LIBS		${Boost_LIBRARIES})
SET (logging_TARGET		logging)

ADD_LIBRARY(${logging_TARGET} STATIC ${logging_INCLUDE} ${logging_SRC})

TARGET_LINK_LIBRARIES(${logging_TARGET} ${logging_LIBS})
SET_TARGET_PROPERTIES(${logging_TARGET} PROPERTIES 
	VERSION	"2")

INSTALL(TARGETS ${logging_TARGET} DESTINATION lib/static)

#
# you can compile the examples if you want to
#

SET (CompileExamples	OFF)

if(CompileExamples)
	ADD_EXECUTABLE(logging_example_1 ${logging_INCLUDE} main1.cpp)
	TARGET_LINK_LIBRARIES(logging_example_1 ${Boost_LIBRARIES} logging)
	
	ADD_EXECUTABLE(logging_example_2 ${logging_INCLUDE} main2.cpp)
	TARGET_LINK_LIBRARIES(logging_example_2 ${Boost_LIBRARIES} logging)
	
	ADD_EXECUTABLE(logging_example_3 ${logging_INCLUDE} main3.cpp)
	TARGET_LINK_LIBRARIES(logging_example_3 ${Boost_LIBRARIES} logging)
	
	ADD_EXECUTABLE(logging_example_4 ${logging_INCLUDE} main4.cpp)
	TARGET_LINK_LIBRARIES(logging_example_4 ${Boost_LIBRARIES} logging)
	
	ADD_EXECUTABLE(logging_example_5 ${logging_INCLUDE} main5.cpp)
	TARGET_LINK_LIBRARIES(logging_example_5 ${Boost_LIBRARIES} logging)
	
	ADD_EXECUTABLE(logging_example_6 ${logging_INCLUDE} main6.cpp)
	TARGET_LINK_LIBRARIES(logging_example_6 ${Boost_LIBRARIES} logging)
	
	ADD_EXECUTABLE(logging_example_7 ${logging_INCLUDE} main7.cpp)
	TARGET_LINK_LIBRARIES(logging_example_7 ${Boost_LIBRARIES} logging)
endif(CompileExamples)
