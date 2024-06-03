# CMakeList.txt : CMake project for astar-boost, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (astar-boost-exe "astar-boost.cpp" "astar-boost.h" "astar-boost.h" "maze.h" "maze.cpp" "euclidean_heuristic.h" "astar_goal_visitor.h" "astar_definitions.h" "random_num_utils.h" "random_num_utils.cpp")

if( ${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    set(USE_FLAGS "-s USE_BOOST_HEADERS=1 -s DISABLE_EXCEPTION_CATCHING=0")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXECUTABLE_SUFFIX .html)
else()
    find_package(Boost REQUIRED)
endif()

# TODO: Add tests and install targets if needed.
set(Boost_USE_STATIC_LIBS ON) 
set(Boost_USE_MULTITHREADED OFF)  
set(Boost_USE_STATIC_RUNTIME OFF) 
set(Boost_INCLUDE_DIR /usr/include)

#find_package(Boost 1.74.0 COMPONENTS graph REQUIRED)
