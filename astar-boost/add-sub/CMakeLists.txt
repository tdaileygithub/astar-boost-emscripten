# CMakeList.txt : CMake project for astar-boost, include source and define
# project specific logic here.
#

# https://emscripten.org/docs/compiling/Building-Projects.html#emscripten-ports
#  emcc --show-ports

set(Boost_USE_STATIC_LIBS ON) 
set(Boost_USE_MULTITHREADED OFF)  
set(Boost_USE_STATIC_RUNTIME OFF) 
#set(Boost_INCLUDE_DIR /usr/include)

if (${CMAKE_HOST_SYSTEM_NAME} MATCHES "Windows")

    set (Boost_ROOT C:/boost_1_82_0)
    set (BOOST_INCLUDE_DIR C:/boost_1_82_0)
    set (BOOST_LIBRARYDIR C:/boost_1_82_0/lib64-msvc-14.3)

    set (SDL2_ROOT C:/SDL2-2.30.3)
    set (SDL2_INCLUDE_DIRS "${SDL2_ROOT}/include")

    # Support both 32 and 64 bit builds
    if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
      set(SDL2_LIBRARIES "${SDL2_ROOT}/lib/x64/SDL2.lib;${SDL2_ROOT}/lib/x64/SDL2main.lib")
    else ()
      set(SDL2_LIBRARIES "${SDL2_ROOT}/lib/x86/SDL2.lib;${SDL2_ROOT}/lib/x86/SDL2main.lib")
    endif ()

    string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)
    
else()
    set(Boost_INCLUDE_DIR /usr/include)
endif()

if( ${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    set(CMAKE_TOOLCHAIN_FILE "/home/tim/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake" )
    #https://emscripten.org/docs/porting/Debugging.html

    set(USE_FLAGS "-s USE_BOOST_HEADERS=1 -s DISABLE_EXCEPTION_CATCHING=0 -s USE_SDL=2 -s USE_SDL_GFX=2 --bind")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXECUTABLE_SUFFIX .html)
else()
    find_package(SDL2 REQUIRED)
    find_package(Boost REQUIRED)
endif()

set(HEADER_FILES 
    "add-sub.h"
)

set(SOURCE_FILES 
    "main.cpp"     
    "add-sub.cpp"
)

# Add source to this project's executable.
include_directories(add-sub-exe ${SDL2_INCLUDE_DIRS})
add_executable (add-sub-exe ${SOURCE_FILES} ${HEADER_FILES} )
target_link_libraries(add-sub-exe ${SDL2_LIBRARIES})

