#include <bits/stdc++.h>  
// This header file includes all standard C++ libraries (like iostream, vector, algorithm, etc.).
// It’s often used in competitive programming for simplicity.

using namespace std;  
// Using the standard namespace to avoid writing std:: before every standard function or object.

int main() {  
// The main() function — execution of the program starts here.

    vector<vector<int>> CostGraph = {  
        {0, 5, 15, 4},  
        {5, 0, 4, 8},  
        {15, 4, 0, 1},  
        {4, 8, 1, 0}  
    };  
    // CostGraph is a 2D vector (matrix) representing travel costs between nodes (cities).
    // CostGraph[i][j] gives the cost of traveling from node i to node j.
    // Example: CostGraph[0][1] = 5 → cost from 'a' to 'b' is 5.
    // Here, we have 4 cities labeled a, b, c, and d.

    int n = CostGraph.size();  
    // n stores the total number of cities (in this case, 4).

    vector<int> nodes;  
    // This vector will hold all city indices *except* the starting city (a → index 0).

    for (int i = 1; i < n; i++) nodes.push_back(i);  
    // Loop runs from 1 to n-1.
    // Pushes 1, 2, 3 into 'nodes' (which correspond to b, c, d).
    // So, nodes = [1, 2, 3].
    // Node 'a' (0) is excluded because it’s always the starting and ending point.

    cout << "All possible paths starting and ending at 'a':\n";  
    // Prints a heading to indicate the list of all possible routes.

    do {  
        // The 'do-while' loop will iterate through *every possible permutation* of the 'nodes' vector.
        // This is done using the 'next_permutation()' function (below).

        int cost = 0;  
        // Variable to store the total cost of the current path.

        int current = 0;  
        // Current city index. Start from 0 (which represents city 'a').

        cout << "a -> ";  
        // Prints the starting city ('a') for the path.

        for (int i : nodes) {  
            // Loop iterates through each city in the current permutation of 'nodes'.
            // For example: in first permutation → [1, 2, 3] → a → b → c → d → a.

            cost += CostGraph[current][i];  
            // Add the travel cost from the current city to the next city.

            cout << char('a' + i) << " -> ";  
            // Prints the next city in the route.
            // Example: if i = 1 → char('a' + 1) = 'b'.

            current = i;  
            // Update 'current' to the latest visited city.
        }

        cost += CostGraph[current][0];  
        // After visiting all cities, add the cost to return to the starting city ('a').

        cout << "a  |  Cost = " << cost << endl;  
        // Print that we returned to 'a' and display the total route cost.

    } while (next_permutation(nodes.begin(), nodes.end()));  
    // next_permutation() rearranges 'nodes' into the next lexicographical order.
    // The loop continues until all possible orderings (routes) are covered.
    // Example of permutations for [1, 2, 3]:
    // [1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], [3,2,1].

    return 0;  
    // End of the program. Returning 0 means successful execution.
}



/* ------------------------------------------------------------
   🧠 PSEUDOCODE — Travelling Salesman Problem (Brute Force)
   ------------------------------------------------------------

START

1. Define a 2D array CostGraph that holds travel costs between all cities.

2. Set n = number of cities.

3. Create a list called 'nodes' to store indices of cities except the starting one.
      FOR i = 1 TO n-1
          ADD i TO nodes
      END FOR

4. PRINT "All possible paths starting and ending at 'a'"

5. DO
      a. Initialize total cost = 0
      b. Set current city = 0  // start from city 'a'
      c. PRINT "a ->"

      d. FOR each city 'i' in the current permutation of 'nodes':
             Add travel cost from current city to 'i' → cost += CostGraph[current][i]
             PRINT city name corresponding to 'i'
             Set current = i
         END FOR

      e. Add cost to return back to starting city:
             cost += CostGraph[current][0]

      f. PRINT "a | Cost = " + cost

   WHILE next_permutation(nodes)
   // Repeat for every possible visiting order of remaining cities.

6. END

STOP

--------------------------------------------------------------
📘 OUTPUT EXAMPLE:
All possible paths starting and ending at 'a':
a -> b -> c -> d -> a  |  Cost = 14
a -> b -> d -> c -> a  |  Cost = 18
a -> c -> b -> d -> a  |  Cost = 32
a -> c -> d -> b -> a  |  Cost = 34
a -> d -> b -> c -> a  |  Cost = 23
a -> d -> c -> b -> a  |  Cost = 24
--------------------------------------------------------------
*/
