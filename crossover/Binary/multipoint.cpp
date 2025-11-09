#include <bits/stdc++.h>  
using namespace std;  

int main() {  
    // -------------------- MULTI-POINT CROSSOVER --------------------
    // In genetic algorithms, Multi-Point Crossover uses multiple crossover
    // points to swap segments between two parents.
    // Example: if crossover points are at 2, 4, 6 — it alternates swapping
    // segments between those positions.
    // It helps combine traits from both parents more diversely than single-point crossover.

    vector<int> p1 = {1,0,1,1,0,0,1,0};  
    // Parent 1 chromosome represented as a binary vector.

    vector<int> p2 = {0,1,0,0,1,1,0,1};  
    // Parent 2 chromosome represented as a binary vector.

    int n = p1.size();  
    // Total number of genes (bits) in each parent.

    vector<int> points = {2,4,6};  
    // These are the crossover points (positions where swapping starts/stops).
    // For example:
    //  - From 0 to 2  → no swap
    //  - From 2 to 4  → swap
    //  - From 4 to 6  → no swap
    //  - From 6 to end → swap (if flip remains true)
    // You can change these points to experiment.

    bool flip = false;  
    // 'flip' determines whether the current segment should be swapped or not.
    // It alternates (true ↔ false) at each crossover point.

    int last = 0;  
    // 'last' keeps track of where the previous crossover segment ended.

    // Iterate through each crossover point.
    for(int c : points) {
        // If 'flip' is true, swap the segment from index 'last' to 'c-1'.
        if(flip)
            for(int i = last; i < c; i++) swap(p1[i], p2[i]);
        // Toggle 'flip' after each point to alternate swap/no-swap.
        flip = !flip;
        // Update 'last' to mark end of this segment.
        last = c;
    }

    // After all crossover points, if flip is still true,
    // it means the last segment (after the final point) should be swapped.
    if(flip)
        for(int i = last; i < n; i++) swap(p1[i], p2[i]);

    // -------------------- OUTPUT --------------------
    cout << "Child1: ";
    // Display the first child (modified p1).
    for(int b : p1) cout << b;

    cout << "\nChild2: ";
    // Display the second child (modified p2).
    for(int b : p2) cout << b;

    // -------------------- EXPLANATION SUMMARY --------------------
    // Multi-Point Crossover steps:
    // 1️⃣ Define multiple crossover points.
    // 2️⃣ Alternate swapping segments between parents at each point.
    // 3️⃣ Resulting children inherit alternating gene segments from each parent.
    // Example:
    // If points = {2,4,6}, swapping occurs between:
    //   [2-4) and [6-end)
    // producing mixed genetic combinations from both parents.
}
