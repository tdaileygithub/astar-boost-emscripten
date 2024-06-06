#include "maze.h"

#include "euclidean_heuristic.h"
#include "astar_goal_visitor.h"
#include "random_num_utils.h"

// Solve the maze using A-star search.  Return true if a solution was found.
bool maze::solve() {
    boost::static_property_map<distance> weight(1);
    // The predecessor map is a vertex-to-vertex mapping.
    typedef boost::unordered_map<vertex_descriptor,
        vertex_descriptor,
        vertex_hash> pred_map;
    pred_map predecessor;
    boost::associative_property_map<pred_map> pred_pmap(predecessor);
    // The distance map is a vertex-to-distance mapping.
    typedef boost::unordered_map<vertex_descriptor,
        distance,
        vertex_hash> dist_map;
    dist_map distance;
    boost::associative_property_map<dist_map> dist_pmap(distance);

    vertex_descriptor s = source();
    vertex_descriptor g = goal();
    euclidean_heuristic heuristic(g);
    astar_goal_visitor visitor(g);

    try {
        astar_search(m_barrier_grid, s, heuristic,
            boost::weight_map(weight).
            predecessor_map(pred_pmap).
            distance_map(dist_pmap).
            visitor(visitor));
    }
    catch (found_goal fg) {
        // Walk backwards from the goal through the predecessor chain adding
        // vertices to the solution path.
        for (vertex_descriptor u = g; u != s; u = predecessor[u])
            m_solution.insert(u);
        m_solution.insert(s);
        m_solution_length = distance[g];
        return true;
    }

    return false;
}

// Print the maze as an ASCII map.
std::ostream& operator<<(std::ostream& output, const maze& m) {
    // Header
    for (vertices_size_type i = 0; i < m.length(0) + 2; i++)
        output << BARRIER;
    output << std::endl;
    // Body
    for (int y = m.length(1) - 1; y >= 0; y--) {
        // Enumerate rows in reverse order and columns in regular order so that
        // (0,0) appears in the lower left-hand corner.  This requires that y be
        // int and not the unsigned vertices_size_type because the loop exit
        // condition is y==-1.
        for (vertices_size_type x = 0; x < m.length(0); x++) {
            // Put a barrier on the left-hand side.
            if (x == 0)
                output << BARRIER;
            // Put the character representing this point in the maze grid.
            vertex_descriptor u = { {x, vertices_size_type(y)} };
            if (m.solution_contains(u))
                output << ".";
            else if (m.has_barrier(u))
                output << BARRIER;
            else
                output << " ";
            // Put a barrier on the right-hand side.
            if (x == m.length(0) - 1)
                output << BARRIER;
        }
        // Put a newline after every row except the last one.
        output << std::endl;
    }
    // Footer
    for (vertices_size_type i = 0; i < m.length(0) + 2; i++)
        output << BARRIER;
    if (m.solved())
        output << std::endl << "Solution length " << m.m_solution_length;
    return output;
}

// Generate a maze with a random assignment of barriers.
std::unique_ptr<maze> random_maze(std::size_t x, std::size_t y) {
    //maze m(x, y);
    maze* mz = new maze(x, y);

    vertices_size_type n = num_vertices(mz->m_grid);
    vertex_descriptor s = mz->source();
    vertex_descriptor g = mz->goal();
    // One quarter of the cells in the maze should be barriers.
    int barriers = n / 4;
    while (barriers > 0) {
        // Choose horizontal or vertical direction.
        std::size_t direction = random_int(0, 1);
        // Walls range up to one quarter the dimension length in this direction.
        vertices_size_type wall = random_int(1, mz->length(direction) / 4);
        // Create the wall while decrementing the total barrier count.
        vertex_descriptor u = vertex(random_int(0, n - 1), mz->m_grid);
        while (wall) {
            // Start and goal spaces should never be barriers.
            if (u != s && u != g) {
                wall--;
                if (!mz->has_barrier(u)) {
                    mz->m_barriers.insert(u);
                    barriers--;
                }
            }
            vertex_descriptor v = mz->m_grid.next(u, direction);
            // Stop creating this wall if we reached the maze's edge.
            if (u == v)
                break;
            u = v;
        }
    }
    //return m;
    return std::unique_ptr<maze>(mz);
}