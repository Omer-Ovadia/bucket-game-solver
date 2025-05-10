#include "Way1.h"
#include "Common.h"

/**
 * @brief Performs a breadth-first search (BFS) on the full graph
 * to find the shortest sequence of legal operations to reach state (W, 0).
 *
 * If a solution is found, prints the number of operations and their descriptions.
 * If no solution exists, prints a corresponding message.
 */
void Way1::BFS()
{
    int n = (L + 1) * (S + 1);                  // Total number of possible states
    int* d = new int[n];                        // Distance array (shortest number of steps to reach state)
    std::pair<int, int>* prev = new std::pair<int, int>[n]; // Parent array to reconstruct path

    // === Initialize distances and parents ===
    for (int i = 0; i < n; i++)
    {
        d[i] = INT_MAX;             // Unvisited
        prev[i] = { -1, -1 };       // No parent
    }

    d[0] = 0;  // Starting point: (0, 0)
    std::queue<std::pair<int, int>> Q;
    Q.push(G1->vertices[0]->data);  // Start BFS from (0, 0)

    std::pair<int, int> u;
    int big, small, U, V;
    std::list<std::pair<int, int>> NeighborsList;
    bool found = false;

    // === Perform BFS ===
    while (!Q.empty())
    {
        u = Q.front();
        Q.pop();

        big = u.first;
        small = u.second;
        U = big * (S + 1) + small;

        if (big == W && small == 0) // Goal state reached
        {
            found = true;
            break;
        }

        NeighborsList = G1->findVertex(u)->neighbors;
        for (auto& var : NeighborsList)
        {
            big = var.first;
            small = var.second;
            V = big * (S + 1) + small;

            if (d[V] == INT_MAX) // If not visited
            {
                d[V] = d[U] + 1;
                prev[V] = u;     // Record parent for backtracking
                Q.push(var);
            }
        }
    }

    // === Reconstruct and print the path if solution found ===
    if (found)
    {
        std::vector<std::pair<int, int>> path;
        std::pair<int, int> curr = { W, 0 };

        while (!(curr.first == 0 && curr.second == 0))
        {
            path.push_back(curr);
            int idx = curr.first * (S + 1) + curr.second;
            curr = prev[idx];
        }

        path.push_back({ 0, 0 });
        std::reverse(path.begin(), path.end());

        std::cout << "Number of operations: " << path.size() - 1 << "\n";
        std::cout << "Operations:\n";

        for (size_t i = 1; i < path.size(); ++i)
        {
            std::pair<int, int> from = path[i - 1];
            std::pair<int, int> to = path[i];

            std::string action;

            // === Determine the operation between two states ===
            if (from.first != to.first && from.second == to.second)
            {
                if (to.first == L) action = "Fill large jug";
                else if (to.first == 0) action = "Empty large jug";
                else action = "Transfer from small jug to large jug";
            }
            else if (from.second != to.second && from.first == to.first)
            {
                if (to.second == S) action = "Fill small jug";
                else if (to.second == 0) action = "Empty small jug";
                else action = "Transfer from large jug to small jug";
            }
            else
            {
                if (from.first > to.first && from.second < to.second)
                    action = "Transfer from large jug to small jug";
                else
                    action = "Transfer from small jug to large jug";
            }

            std::cout << i << ". " << action << "\n";
        }
    }
    else
    {
        std::cout << "No solution.\n";
    }

    // === Clean up dynamic memory ===
    delete[] d;
    delete[] prev;
}
