#pragma once
#include <unordered_set>
#include <utility>
#include <functional>
#include <list>

/**
 * @brief Hash function for std::pair<int, int> to be used in unordered_set/map.
 */
struct pair_hash
{
    std::size_t operator()(const std::pair<int, int>& p) const
    {
        return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
    }
};

/**
 * @brief Second implementation of the water jug problem using on-the-fly graph generation.
 *
 * This class avoids building the full state graph in advance. Instead, it generates neighbors dynamically during BFS.
 */
class Way2
{
private:
    int L, S, W;   ///< Large jug size, small jug size, target amount
    std::unordered_set<std::pair<int, int>, pair_hash> unorderedSet; ///< Set of already visited states

    /**
     * @brief Dynamically calculates valid neighbor states from a given state.
     *
     * @param vertex The current state (big, small)
     * @return List of reachable states, sorted lexicographically
     */
    std::list<std::pair<int, int>> CalculateAdjList(std::pair<int, int> vertex);

    /**
     * @brief Runs BFS starting from (0, 0), generating states and transitions on-the-fly.
     */
    void BFS();

public:
    /**
     * @brief Constructor - initializes state and starts BFS immediately.
     */
    Way2(int _L, int _S, int _W) : L(_L), S(_S), W(_W)
    {
        BFS();
    }

    /**
     * @brief Destructor - currently does nothing as all memory is managed automatically.
     */
    ~Way2() {}
};


