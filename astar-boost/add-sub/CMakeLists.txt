# CMakeList.txt : CMake project for astar-boost, include source and define
# project specific logic here.
#

add_library(add-sub-lib SHARED "add-sub.h" "add-sub.cpp")

# Add source to this project's executable.
add_executable (add-sub-exe "main.cpp"  )
target_link_libraries(add-sub-exe PUBLIC add-sub-lib)


set(LINK_OPTIONS)
set(CMAKE_TOOLCHAIN_FILE /home/tim/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake)
#set(CMAKE_EXECUTABLE_SUFFIX ".html")
set(LINK_OPTIONS ${LINK_OPTIONS} -sWASM=1 -sALLOW_MEMORY_GROWTH=1 -sNO_EXIT_RUNTIME=0 -sASSERTIONS=1)
