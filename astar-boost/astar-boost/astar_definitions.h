#pragma once

#define BARRIER "#"

#include <boost/graph/filtered_graph.hpp>
#include <boost/graph/grid_graph.hpp>

#include <boost/unordered_set.hpp>

// Distance traveled in the maze
typedef double distance;

#define GRID_RANK 2
typedef boost::grid_graph<GRID_RANK> grid;
typedef boost::graph_traits<grid>::vertex_descriptor vertex_descriptor;
typedef boost::graph_traits<grid>::vertices_size_type vertices_size_type;

#ifdef EMSCRIPTEN
// A hash function for vertices.
struct vertex_hash {
    constexpr std::size_t operator()(vertex_descriptor const& u) const {
        std::size_t seed = 0;
        boost::hash_combine(seed, u[0]);
        boost::hash_combine(seed, u[1]);
        return seed;
    }
};
#else
// A hash function for vertices.
struct vertex_hash : std::unary_function<vertex_descriptor, std::size_t> {
    std::size_t operator()(vertex_descriptor const& u) const {
        std::size_t seed = 0;
        boost::hash_combine(seed, u[0]);
        boost::hash_combine(seed, u[1]);
        return seed;
    }
};
#endif

typedef boost::unordered_set<vertex_descriptor, vertex_hash> vertex_set;
typedef boost::vertex_subset_complement_filter<grid, vertex_set>::type filtered_grid;

// Exception thrown when the goal vertex is found
struct found_goal {};