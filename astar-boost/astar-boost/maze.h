#pragma once

#include "astar_definitions.h"

#include <boost/graph/astar_search.hpp>
#include <boost/graph/filtered_graph.hpp>
#include <boost/graph/grid_graph.hpp>

#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>


// A searchable maze
//
// The maze is grid of locations which can either be empty or contain a
// barrier.  You can move to an adjacent location in the grid by going up,
// down, left and right.  Moving onto a barrier is not allowed.  The maze can
// be solved by finding a path from the lower-left-hand corner to the
// upper-right-hand corner.  If no open path exists between these two
// locations, the maze is unsolvable.
//
// The maze is implemented as a filtered grid graph where locations are
// vertices.  Barrier vertices are filtered out of the graph.
//
// A-star search is used to find a path through the maze. Each edge has a
// weight of one, so the total path length is equal to the number of edges
// traversed.
class maze {
public:
	friend std::ostream& operator<<(std::ostream&, const maze&);
	friend maze random_maze(std::size_t, std::size_t);

	maze() :m_grid(create_grid(0, 0)), m_barrier_grid(create_barrier_grid()) {};
	maze(std::size_t x, std::size_t y) :m_grid(create_grid(x, y)),
		m_barrier_grid(create_barrier_grid()) {};

	// The length of the maze along the specified dimension.
	vertices_size_type length(std::size_t d) const { return m_grid.length(d); }

	bool has_barrier(vertex_descriptor u) const {
		return m_barriers.find(u) != m_barriers.end();
	}

	// Try to find a path from the lower-left-hand corner source (0,0) to the
	// upper-right-hand corner goal (x-1, y-1).
	vertex_descriptor source() const { return vertex(0, m_grid); }
	vertex_descriptor goal() const {
		return vertex(num_vertices(m_grid) - 1, m_grid);
	}

	bool solve();
	bool solved() const { return !m_solution.empty(); }
	bool solution_contains(vertex_descriptor u) const {
		return m_solution.find(u) != m_solution.end();
	}

private:
	// Create the underlying rank-2 grid with the specified dimensions.
	grid create_grid(std::size_t x, std::size_t y) {
		boost::array<std::size_t, GRID_RANK> lengths = { {x, y} };
		return grid(lengths);
	}

	// Filter the barrier vertices out of the underlying grid.
	filtered_grid create_barrier_grid() {
		return boost::make_vertex_subset_complement_filter(m_grid, m_barriers);
	}

	// The grid underlying the maze
	grid m_grid;
	// The underlying maze grid with barrier vertices filtered out
	filtered_grid m_barrier_grid;
	// The barriers in the maze
	vertex_set m_barriers;
	// The vertices on a solution path through the maze
	vertex_set m_solution;
	// The length of the solution path
	distance m_solution_length;
};

maze random_maze(std::size_t x, std::size_t y);