#include <bits/stdc++.h>
using namespace std;

int main() {
    // -------------------- UNIFORM CROSSOVER (WITH MASK) --------------------
    // In this method, crossover does NOT depend on fixed points like single- or two-point.
    // Instead, a random binary mask decides which genes to swap between the parents.
    // Each position in the mask corresponds to a gene — if mask[i] = 1, genes are swapped.

    vector<int> p1 = {1,0,1,1,0,0,1,0};  // Parent 1
    vector<int> p2 = {0,1,0,0,1,1,0,1};  // Parent 2
    int n = p1.size();                   // Chromosome length

    // -------------------- STEP 1: GENERATE RANDOM MASK --------------------
    // The mask determines which genes to swap.
    // Example mask: [1, 0, 1, 0, 0, 1, 0, 1]
    // => Swap bits at positions where mask[i] = 1.
    vector<int> mask(n);
    for(int i = 0; i < n; i++)
        mask[i] = rand() % 2;  // Randomly assign 0 or 1

    // -------------------- STEP 2: APPLY CROSSOVER BASED ON MASK --------------------
    for(int i = 0; i < n; i++)
        if(mask[i]) swap(p1[i], p2[i]);
    // If mask[i] = 1 → Swap p1[i] and p2[i]
    // If mask[i] = 0 → Keep them as they are

    // -------------------- STEP 3: DISPLAY RESULTS --------------------
    cout << "Mask: ";
    for(int m : mask) cout << m;
    // The crossover mask shows where swapping occurred.

    cout << "\nChild1: ";
    for(int b : p1) cout << b;
    // Child 1 is a mix of Parent 1 and Parent 2 genes based on the mask.

    cout << "\nChild2: ";
    for(int b : p2) cout << b;
    // Child 2 is the complementary mix.

    // -------------------- EXAMPLE --------------------
    // Parent1: 10110010
    // Parent2: 01001101
    // Mask:    10100101
    // Child1:  00110111
    // Child2:  11001000
    //
    // Each '1' in the mask caused a swap — giving very high genetic diversity.
    //
    // -------------------- SUMMARY --------------------
    // ✅ Mask acts as a per-gene swap decision.
    // ✅ Provides higher randomness compared to single or two-point crossover.
    // ✅ Helps avoid premature convergence by mixing genes more evenly.
}
