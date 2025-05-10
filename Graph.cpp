#include "Graph.h"
#include "Common.h"

/**
 * @brief Initializes all possible states of the jugs (vertices) and stores them in the graph.
 *
 * Each state is represented as a pair (big, small), where:
 * - big = amount in the large jug
 * - small = amount in the small jug
 *
 * The total number of vertices is (L + 1) * (S + 1).
 * The vertices are stored in row-major order in the `vertices` vector.
 */
void Graph::MakeEmptyGraph(int n)
{
    vertices.reserve(n);
    for (int i = 0; i < n; i++)
    {
        int big = i / (S + 1);            // integer division: row
        int small = i % (S + 1);      // remainder: column
        vertices.push_back(new VertexNode({ big, small }));
    }
}

/**
 * @brief Finds and returns a pointer to the vertex representing the given state.
 *
 * @param vertex The target state (big, small)
 * @return Pointer to the corresponding VertexNode, or nullptr if out of bounds.
 */
Graph::VertexNode* Graph::findVertex(std::pair<int, int> vertex)
{
    int big = vertex.first;
    int small = vertex.second;

    if (big < 0 || big > L || small < 0 || small > S)
        return nullptr; // invalid state

    int index = big * (S + 1) + small;
    return vertices[index];
}

/**
 * @brief Adds a directed edge between two states in the graph.
 *
 * @param from Origin state
 * @param to Destination state
 */
void Graph::addEdge(std::pair<int, int> from, std::pair<int, int> to)
{
    VertexNode* fromNode = findVertex(from);
    if (fromNode)
        fromNode->neighbors.push_back(to);
}

/**
 * @brief Generates all legal transitions (edges) between states in the water jug problem.
 *
 * For each state (big, small), applies all valid operations:
 * - Fill large jug
 * - Fill small jug
 * - Empty large jug
 * - Empty small jug
 * - Transfer from large to small
 * - Transfer from small to large
 *
 * Neighbor lists are sorted in lexicographic order after all edges are added.
 */
void Graph::generateAllEdges()
{
    for (auto v : vertices)
    {
        int big = v->data.first;
        int small = v->data.second;

        // 1. Fill large jug
        if (big < L)
            addEdge({ big, small }, { L, small });

        // 2. Fill small jug
        if (small < S)
            addEdge({ big, small }, { big, S });

        // 3. Empty large jug
        if (big > 0)
            addEdge({ big, small }, { 0, small });

        // 4. Empty small jug
        if (small > 0)
            addEdge({ big, small }, { big, 0 });

        // 5. Transfer from large to small
        if (big > 0 && small < S)
        {
            int pour = std::min(big, S - small);
            addEdge({ big, small }, { big - pour, small + pour });
        }

        // 6. Transfer from small to large
        if (small > 0 && big < L)
        {
            int pour = std::min(small, L - big);
            addEdge({ big, small }, { big + pour, small - pour });
        }

        // Sort neighbors in lexicographic order
        v->neighbors.sort();
    }
}

/**
 * @brief Prints the graph's adjacency list for all states.
 *
 * For each vertex, prints the state and its sorted neighbors.
 */
void Graph::printGraph() const
{
    for (const auto& v : vertices)
    {
        std::cout << "(" << v->data.first << ", " << v->data.second << ") -> ";
        for (const auto& n : v->neighbors)
            std::cout << "(" << n.first << ", " << n.second << ") ";
        std::cout << std::endl;
    }
}

/**
 * @brief Returns the sorted list of neighbors for a given state.
 *
 * @param u The state (big, small)
 * @return Sorted list of adjacent states (legal next moves)
 */
std::list<std::pair<int, int>> Graph::GetAdjList(std::pair<int, int> u) const
{
    int big = u.first;
    int small = u.second;

    if (big < 0 || big > L || small < 0 || small > S)
        return {}; // invalid state

    int index = big * (S + 1) + small;
    return vertices[index]->neighbors; // already sorted
}
