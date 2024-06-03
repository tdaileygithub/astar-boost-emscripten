# CMakeList.txt : CMake project for astar-boost, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (astar-boost-exe "astar-boost.cpp" "astar-boost.h" "astar-boost.h" "maze.h" "maze.cpp" "euclidean_heuristic.h" "astar_goal_visitor.h" "astar_definitions.h" "random_num_utils.h" "random_num_utils.cpp")

include_directories(SYSTEM "/usr/include/boost")

#set(CMAKE_TOOLCHAIN_FILE "/home/tim/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake" CACHE STRING "")

# TODO: Add tests and install targets if needed.
set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
set(Boost_INCLUDE_DIR /usr/include)

find_package(Boost 1.74.0 COMPONENTS graph REQUIRED)
