// astar-boost.cpp : Defines the entry point for the application.
//

#include "astar-boost.h"
#include "maze.h"
#include "random_num_utils.h"

#include <boost/lexical_cast.hpp>

#include <iostream>

//https://www.boost.org/doc/libs/1_70_0/libs/graph/example/astar_maze.cpp

int main(int argc, char const* argv[]) {

    // The default maze size is 20x10.  A different size may be specified on
    // the command line.
    std::size_t x = 20;
    std::size_t y = 10;

    if (argc == 3) {
        x = boost::lexical_cast<std::size_t>(argv[1]);
        y = boost::lexical_cast<std::size_t>(argv[2]);
    }

    global_random_generator.seed(std::time(0));
    maze m = random_maze(x, y);

    if (m.solve())
        std::cout << "Solved the maze." << std::endl;
    else
        std::cout << "The maze is not solvable." << std::endl;
    std::cout << m << std::endl;
    return 0;
}