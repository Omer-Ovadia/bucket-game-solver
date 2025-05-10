#pragma once
#include "Graph.h"
#include "Common.h"
/**
 * @brief Implements the first solution method (Way1) for solving the water jug problem.
 *
 * This method constructs the full state graph in advance and performs
 * a breadth-first search (BFS) to find the shortest sequence of operations
 * that results in exactly W units in the large jug.
 */
class Way1
{
private:
    int L, S, W;     ///< Capacities of the large and small jugs, and the desired target amount
    Graph* G1;       ///< Pointer to the graph representing all valid jug states

    /**
     * @brief Performs a BFS search on the full graph to find a solution path.
     *
     * The BFS finds the shortest path from the initial state (0,0) to the target state (W,0),
     * and prints the number of operations and the exact sequence of actions taken.
     */
    void BFS();

public:
    /**
     * @brief Constructor - builds the graph and initiates the BFS process.
     *
     * @param _L Capacity of the large jug
     * @param _S Capacity of the small jug
     * @param _W Target amount to be reached in the large jug
     */
    Way1(int _L, int _S, int _W)
        : L(_L), S(_S), W(_W)
    {
        G1 = new Graph(L, S);
        BFS();
    }

    /**
     * @brief Destructor - releases the dynamically allocated graph.
     */
    ~Way1()
    {
        delete G1;
    }
};
