cmake_minimum_required (VERSION 3.1)
project (blueprintc)

set(blueprintc_VERSION_MAJOR 0)
set(blueprintc_VERSION_MINOR 1)

set(CMAKE_CXX_STANDARD 17)

set(Boost_DEBUG 1)

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost REQUIRED COMPONENTS) 

include_directories(include ${Boost_INCLUDE_DIRS}) 
add_executable(apibc src/main.cpp src/backend/canonical.cpp) 
target_link_libraries(apibc ${Boost_LIBRARIES})
