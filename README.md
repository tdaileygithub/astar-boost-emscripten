# requirements

```
apt install cmake g++ build-essential
apt install libboost-dev libsdl2-dev 
```

# astar-boost-emscripten

https://www.boost.org/doc/libs/1_70_0/libs/graph/example/astar_maze.cpp

//          Copyright W.P. McNeill 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This program uses the A-star search algorithm in the Boost Graph Library to
// solve a maze.  It is an example of how to apply Boost Graph Library
// algorithms to implicit graphs.
//
// This program generates a random maze and then tries to find the shortest
// path from the lower left-hand corner to the upper right-hand corner.  Mazes
// are represented by two-dimensional grids where a cell in the grid may
// contain a barrier.  You may move up, down, right, or left to any adjacent
// cell that does not contain a barrier.
//
// Once a maze solution has been attempted, the maze is printed.  If a
// solution was found it will be shown in the maze printout and its length
// will be returned.  Note that not all mazes have solutions.
//
// The default maze size is 20x10, though different dimensions may be
// specified on the command line.


# Emscripten + Embind

https://web.dev/articles/drawing-to-canvas-in-emscripten
https://emscripten.org/docs/porting/connecting_cpp_and_javascript/embind.html#built-in-type-conversions
https://stackoverflow.com/questions/65566923/is-there-a-more-efficient-way-to-return-arrays-from-c-to-javascript
