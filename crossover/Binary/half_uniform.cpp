#include <bits/stdc++.h>  
using namespace std;  

int main() {  
    // -------------------- HALF-UNIFORM CROSSOVER (HUX) --------------------
    // In genetic algorithms, HUX is a variation of uniform crossover.
    // It swaps exactly half of the differing genes between two parent chromosomes.
    // This ensures balanced genetic diversity in the offspring.

    vector<int> p1 = {1,0,1,1,0,0,1,0};  
    // Parent 1 chromosome represented as a binary vector.

    vector<int> p2 = {0,1,0,0,1,1,0,1};  
    // Parent 2 chromosome represented as a binary vector.

    vector<int> diff;  
    // 'diff' will store all the indices (positions) where p1 and p2 differ.

    // Loop through each gene (bit) in both parents.
    for(int i = 0; i < p1.size(); i++)
        // If the gene differs at position i, record that index.
        if(p1[i] != p2[i]) diff.push_back(i);

    // Randomly shuffle the differing indices.
    // This ensures randomness in which positions will be swapped.
    random_shuffle(diff.begin(), diff.end());

    // Calculate how many positions to swap = half of the differing genes.
    int swaps = diff.size() / 2;

    // Perform swapping for exactly half of the differing positions.
    for(int i = 0; i < swaps; i++)
        // Exchange the bits at those indices between Parent 1 and Parent 2.
        swap(p1[diff[i]], p2[diff[i]]);

    // -------------------- OUTPUT --------------------
    // After crossover, p1 and p2 now become two new child chromosomes.

    cout << "Child1: ";
    // Display the first child (modified p1).
    for(int b : p1) cout << b;

    cout << "\nChild2: ";
    // Display the second child (modified p2).
    for(int b : p2) cout << b;

    // The result: each child differs from its parent in exactly half
    // of the positions where the parents were different — that’s the
    // essence of the Half-Uniform Crossover (HUX) technique.
}
