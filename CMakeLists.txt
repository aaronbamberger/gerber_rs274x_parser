project(GerberRS274XParser)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11")
set(CXX_STANDARD cxx_std_11)
set(CXX_STANDARD_REQUIRED ON)

include_directories(${GerberRS274XParser_SOURCE_DIR}/include)
include_directories(${CMAKE_BINARY_DIR}/src)

add_subdirectory(src)
