#pragma once

#include "astar_definitions.h"

// Visitor that terminates when we find the goal vertex
struct astar_goal_visitor :public boost::default_astar_visitor {
    astar_goal_visitor(vertex_descriptor goal) :m_goal(goal) {};

    void examine_vertex(vertex_descriptor u, const filtered_grid&) {
        if (u == m_goal)
            throw found_goal();
    }

private:
    vertex_descriptor m_goal;
};
