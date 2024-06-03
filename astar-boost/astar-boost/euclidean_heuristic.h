#pragma once

#include "astar_definitions.h"

#include <cmath>

// Euclidean heuristic for a grid
//
// This calculates the Euclidean distance between a vertex and a goal
// vertex.
class euclidean_heuristic :
    public boost::astar_heuristic<filtered_grid, double>
{
public:
    euclidean_heuristic(vertex_descriptor goal) :m_goal(goal) {};

    double inline operator()(vertex_descriptor v) {
        return sqrt(pow(double(m_goal[0] - v[0]), 2) + pow(double(m_goal[1] - v[1]), 2));
    }

private:
    vertex_descriptor m_goal;
};