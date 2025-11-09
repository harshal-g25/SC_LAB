#include <bits/stdc++.h>  
// This header file includes *all* standard C++ libraries (like iostream, vector, algorithm, etc.)
// It's commonly used in competitive programming for convenience.

using namespace std;  
// This line allows us to use standard C++ names (like cout, vector) without writing std:: before each.

int main() {  
// The main() function — program execution starts here.

    vector<vector<int>> CostGraph = {  
        {0, 5, 15, 4},  
        {5, 0, 4, 8},  
        {15, 4, 0, 1},  
        {4, 8, 1, 0}  
    };  
    // 'CostGraph' is a 2D vector (matrix) representing the cost between cities (or nodes).
    // Each element CostGraph[i][j] represents the cost to travel from node i to node j.
    // Here we have 4 nodes: a, b, c, d.
    // Example: CostGraph[0][1] = 5 means cost from 'a' to 'b' is 5.

    int n = CostGraph.size();  
    // 'n' stores the total number of nodes (4 in this case).

    vector<int> nodes;  
    // 'nodes' is a vector to store all nodes except the starting node 'a' (i.e., 0).

    for (int i = 1; i < n; i++) nodes.push_back(i);  
    // This loop fills 'nodes' with [1, 2, 3] representing nodes b, c, and d.
    // We start from 1 because node 0 ('a') is always the starting and ending point.

    cout << "All possible paths starting and ending at 'a':\n";  
    // This line prints a heading message before listing all the paths.

  
    do {  
        // The 'do...while' loop will generate all possible permutations (orders)
        // of visiting the other nodes using next_permutation() below.

        int cost = 0;  
        // 'cost' variable will store the total travel cost for the current path.

        int current = 0;  
        // 'current' keeps track of the current node (starting from 'a' → index 0).

        cout << "a -> ";  
        // Print starting node 'a'.

        for (int i : nodes) {  
            // Loop through each node in the current permutation of 'nodes'.

            cost += CostGraph[current][i];  
            // Add the cost from current node to next node.

            cout << char('a' + i) << " -> ";  
            // Print the next node as a letter (0='a', 1='b', 2='c', etc.)
            // Example: if i=1 → char('a'+1) = 'b'.

            current = i;  
            // Move to the next node.
        }

        cost += CostGraph[current][0];  
        // Finally, add the cost of returning back to the starting node 'a' (index 0).

        cout << "a  |  Cost = " << cost << endl;  
        // Print 'a' to show we returned to start and display the total cost of this route.

    } while (next_permutation(nodes.begin(), nodes.end()));  
    // next_permutation() rearranges 'nodes' into the next lexicographical permutation.
    // The loop continues until all permutations are generated.
    // This effectively lists all possible paths starting and ending at 'a'.

    return 0;  
    // Return 0 means the program executed successfully.
}
//Summary of what this code does:

//Summary of what this code does:

//This program solves the Travelling Salesman Problem (TSP) by:
//Listing all possible routes starting and ending at 'a' (node 0).

//Calculating the total travel cost for each route.

//Printing the route and its corresponding cost.

//So for 4 nodes (a, b, c, d), it will show every possible way to go from a, visit all other nodes exactly once, and return to a.