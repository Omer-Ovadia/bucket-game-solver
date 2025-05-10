#pragma once
#include "Common.h"

/**
 * @brief A directed graph representing all possible states and transitions in the water jug problem.
 *
 * The graph stores all vertices (states) using a vector for fast indexed access,
 * and uses a linked list to represent the adjacency list (outgoing edges) of each vertex.
 */
class Graph
{
public:

    /**
     * @brief Represents a single vertex in the graph.
     *
     * Each vertex holds a state as a pair of integers (big jug, small jug),
     * and a list of neighboring vertices reachable by one legal operation.
     */
    struct VertexNode
    {
        std::pair<int, int> data;                   ///< The state: (amount in big jug, amount in small jug)
        std::list<std::pair<int, int>> neighbors;   ///< List of adjacent vertices (possible next states)

        VertexNode(std::pair<int, int> d) : data(d) {}
    };

    int L, S;  ///< Maximum capacities of the large and small jugs

    /**
     * @brief Vector of pointers to all vertices in the graph.
     *
     * The vertices are stored in row-major order:
     * index = big * (S + 1) + small
     */
    std::vector<VertexNode*> vertices;

    /**
     * @brief Constructs the graph by generating all possible vertices and legal transitions (edges).
     *
     * @param _L Capacity of the large jug
     * @param _S Capacity of the small jug
     */
    Graph(int _L, int _S) : L(_L), S(_S)
    {
        int n = (L + 1) * (S + 1);
        MakeEmptyGraph(n);     // Create all vertices
        generateAllEdges();    // Connect them with legal moves
    }

    /**
     * @brief Destructor - releases all dynamically allocated vertex nodes.
     */
    ~Graph()
    {
        for (auto v : vertices)
            delete v;
    }

    /**
     * @brief Initializes the graph with all possible states (vertices), without edges.
     *
     * @param n Total number of vertices = (L + 1) * (S + 1)
     */
    void MakeEmptyGraph(int n);

    /**
     * @brief Returns a pointer to the vertex representing the given state.
     *
     * @param vertex The state (big, small)
     * @return Pointer to the corresponding VertexNode, or nullptr if out of bounds.
     */
    VertexNode* findVertex(std::pair<int, int> vertex);

    /**
     * @brief Adds a directed edge from one state to another.
     *
     * @param from Origin vertex (state)
     * @param to Destination vertex (state)
     */
    void addEdge(std::pair<int, int> from, std::pair<int, int> to);

    /**
     * @brief Generates all legal transitions (edges) for the water jug problem.
     *
     * Includes fill, empty, and transfer operations, and sorts each neighbor list lexicographically.
     */
    void generateAllEdges();

    /**
     * @brief Prints the entire graph: all vertices and their sorted neighbor lists.
     */
    void printGraph() const;

    /**
     * @brief Returns the sorted adjacency list of a given vertex (state).
     *
     * @param u The vertex state (big, small)
     * @return A list of adjacent states reachable from u, sorted lexicographically.
     */
    std::list<std::pair<int, int>> GetAdjList(std::pair<int, int> u) const;
};
