#include <bits/stdc++.h>
using namespace std;

int main() {
    // -------------------- TWO-POINT CROSSOVER --------------------
    // In genetic algorithms, Two-Point Crossover selects *two random crossover points*
    // on the parent chromosomes and swaps the genes between those two points.
    // This allows exchanging a middle segment of genes instead of just one tail portion.

    vector<int> p1 = {1,0,1,1,0,0,1,0};
    // Parent 1 chromosome represented as a binary vector.

    vector<int> p2 = {0,1,0,0,1,1,0,1};
    // Parent 2 chromosome represented as a binary vector.

    int n = p1.size();
    // Total number of genes (bits) in each parent.

    // -------------------- STEP 1: SELECT TWO CROSSOVER POINTS --------------------
    int c1 = rand() % n, c2 = rand() % n;
    // Randomly choose two crossover points (between 0 and n-1).

    if(c1 > c2) swap(c1, c2);
    // Ensure c1 is the smaller index and c2 is the larger index
    // so that the crossover segment is well-defined.
    //
    // Example:
    // If c1 = 2, c2 = 6, crossover will happen between positions 2 and 6 (exclusive of 6).

    // -------------------- STEP 2: PERFORM CROSSOVER --------------------
    for(int i = c1; i < c2; i++)
        swap(p1[i], p2[i]);
    // Swap all genes between c1 and c2.
    //
    // Example:
    // p1: 10110010
    // p2: 01001101
    // If c1 = 2, c2 = 6
    // Segment to swap: indices [2,3,4,5]
    // Result:
    // Child1: 10001110
    // Child2: 01110001

    // -------------------- STEP 3: OUTPUT CHILDREN --------------------
    cout << "Child1: ";
    for(int b : p1) cout << b;
    // Print all bits of Child 1.

    cout << "\nChild2: ";
    for(int b : p2) cout << b;
    // Print all bits of Child 2.

    // -------------------- SUMMARY --------------------
    // Two-Point Crossover Steps:
    // 1️⃣ Choose two random crossover points (c1, c2).
    // 2️⃣ Copy genes before c1 and after c2 from the same parent.
    // 3️⃣ Swap the middle segment (between c1 and c2) between parents.
    // 4️⃣ Result: Offspring that share both early and late genes from their own
    //    parent but a middle section from the other parent.
}
