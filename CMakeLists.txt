project(MyTools)

#set program running path 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/output)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

FILE(GLOB TEST_FILES "${CMAKE_CURRENT_SOURCE_DIR}/tool_*.cpp")
FOREACH(TEST_FILE ${TEST_FILES})
    STRING(REGEX REPLACE ".*/(.*)/(.*)/*.cpp" "\\2" EX_NAME ${TEST_FILE})
    MESSAGE("BUILD TEST PROGRAM " ${EX_NAME})
    add_executable(${EX_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/${EX_NAME}.cpp) 
    target_link_libraries(${EX_NAME} ${TwoFrame} -lpthread)
ENDFOREACH()
  