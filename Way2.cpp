#include "Way2.h"
#include "Common.h"

/**
 * @brief Dynamically generates the adjacency list for a given vertex (state).
 *
 * Only returns neighbor states that have not been visited before.
 * Each state is added to the visited set (unorderedSet) as soon as it is generated.
 *
 * @param vertex The current state (big, small)
 * @return A sorted list of legal next states (neighbors)
 */
std::list<std::pair<int, int>> Way2::CalculateAdjList(std::pair<int, int> vertex)
{
    std::list<std::pair<int, int>> AdjList;

    int big = vertex.first;
    int small = vertex.second;

    // 1. Fill large jug
    if (big < L)
    {
        if (unorderedSet.find({ L, small }) == unorderedSet.end())
        {
            AdjList.push_back({ L, small });
            unorderedSet.insert({ L, small });
        }
    }

    // 2. Fill small jug
    if (small < S)
    {
        if (unorderedSet.find({ big, S }) == unorderedSet.end())
        {
            AdjList.push_back({ big, S });
            unorderedSet.insert({ big, S });
        }
    }

    // 3. Empty large jug
    if (big > 0)
    {
        if (unorderedSet.find({ 0, small }) == unorderedSet.end())
        {
            AdjList.push_back({ 0, small });
            unorderedSet.insert({ 0, small });
        }
    }

    // 4. Empty small jug
    if (small > 0)
    {
        if (unorderedSet.find({ big, 0 }) == unorderedSet.end())
        {
            AdjList.push_back({ big, 0 });
            unorderedSet.insert({ big, 0 });
        }
    }

    // 5. Transfer from large to small
    if (big > 0 && small < S)
    {
        int pour = std::min(big, S - small);
        if (unorderedSet.find({ big - pour, small + pour }) == unorderedSet.end())
        {
            AdjList.push_back({ big - pour, small + pour });
            unorderedSet.insert({ big - pour, small + pour });
        }
    }

    // 6. Transfer from small to large
    if (small > 0 && big < L)
    {
        int pour = std::min(small, L - big);
        if (unorderedSet.find({ big + pour, small - pour }) == unorderedSet.end())
        {
            AdjList.push_back({ big + pour, small - pour });
            unorderedSet.insert({ big + pour, small - pour });
        }
    }

    AdjList.sort(); // Maintain lexicographic order
    return AdjList;
}

/**
 * @brief Performs BFS to find the shortest sequence of operations
 *        that leads from (0,0) to (W,0), generating neighbors on-the-fly.
 */
void Way2::BFS()
{
    int n = (L + 1) * (S + 1);
    int* d = new int[n];                                   // Distance array
    std::pair<int, int>* prev = new std::pair<int, int>[n]; // Parent tracking

    // === Initialization ===
    for (int i = 0; i < n; i++) {
        d[i] = INT_MAX;
        prev[i] = { -1, -1 };
    }

    d[0] = 0; // Distance from (0,0) to itself
    std::queue<std::pair<int, int>> Q;
    Q.push({ 0, 0 });
    unorderedSet.insert({ 0, 0 });

    std::pair<int, int> u;
    int big, small, U, V;
    std::list<std::pair<int, int>> NeighborsList;
    bool found = false;

    // === BFS loop ===
    while (!Q.empty())
    {
        u = Q.front();
        Q.pop();

        big = u.first;
        small = u.second;
        U = big * (S + 1) + small;

        // Goal reached
        if (big == W && small == 0) {
            found = true;
            break;
        }

        NeighborsList = CalculateAdjList(u);
        for (auto& var : NeighborsList)
        {
            big = var.first;
            small = var.second;
            V = big * (S + 1) + small;

            d[V] = d[U] + 1;
            prev[V] = u;
            Q.push(var);
        }
    }

    // === Output result ===
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

            // === Determine action type ===
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
    else {
        std::cout << "No solution.\n";
    }

    // === Cleanup ===
    delete[] d;
    delete[] prev;
}

