# CMakeList.txt : CMake project for astar-boost, include source and define
# project specific logic here.
#

# https://emscripten.org/docs/compiling/Building-Projects.html#emscripten-ports
#  emcc --show-ports

if( ${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    set(USE_FLAGS "-s USE_BOOST_HEADERS=1")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXECUTABLE_SUFFIX .html)
else()
    find_package(Boost REQUIRED)
endif()

# Add source to this project's executable.
add_executable (add-sub-exe "main.cpp"  "add-sub.h" "add-sub.cpp")