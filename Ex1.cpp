#include "Way1.h"
#include "Graph.h"
#include "Way2.h"
#include "Common.h"
using namespace std;

int main()
{
    int L, S, W, Way, Time;

    cout << "Enter L (capacity of large jug): ";
    cin >> L;

    cout << "Enter S (capacity of small jug): ";
    cin >> S;

    cout << "Enter W (desired amount in large jug): ";
    cin >> W;

    // === Input validation ===
    if (L <= S || W > L || L < 0 || S < 0 || W < 0) 
    {
        cerr << "Invalid input." << endl;
        exit(1);
    }

    cout << "Enter Way (1 for full graph, 2 for on-the-fly): ";
    cin >> Way;

    // === Way validation ===
    if (Way != 1 && Way != 2)
    {
        cerr << "Invalid way choice. Must be 1 or 2." << endl;
        exit(1);
    }

    cout << "Do you want to measure time? (1 = yes, 0 = no): ";
    cin >> Time;

    // === Time validation ===
    if (Time != 0 && Time != 1)
    {
        cerr << "Invalid way choice. Must be 0 or 1." << endl;
        exit(1);
    }

    // === Output user selection ===
    cout << "You selected: L = " << L << ", S = " << S << ", W = " << W
        << ", Way = " << Way << ", Time = " << (Time ? "yes" : "no") << "\n";

    // === Run selected implementation ===
    std::cout << "\n\n";
    if (Time == 1)
    {
        auto start = chrono::high_resolution_clock::now();

        if (Way == 1)
           Way1(L, S, W);
        else
           Way2(L, S, W);

        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << "Function took " << duration.count() << " microseconds." << endl;
    }
    else 
    {
        if (Way == 1)
            Way1(L, S, W);
        else
            Way2(L, S, W);
    }

    return 0;
}
