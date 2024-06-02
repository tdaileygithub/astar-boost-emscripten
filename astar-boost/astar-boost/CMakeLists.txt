# CMakeList.txt : CMake project for astar-boost, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (astar-boost "astar-boost.cpp" "astar-boost.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET astar-boost PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.74.0 COMPONENTS filesystem graph REQUIRED)  
include_directories ( ${Boost_INCLUDE_DIR} )
