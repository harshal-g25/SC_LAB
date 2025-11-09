#include <bits/stdc++.h>
using namespace std;

int main() {
    // -------------------- SINGLE-POINT CROSSOVER --------------------
    // In genetic algorithms, Single-Point Crossover selects one random
    // crossover point between two parent chromosomes and swaps all genes
    // beyond that point to create two new offspring.

    vector<int> p1 = {1,0,1,1,0,0,1,0};
    // Parent 1 chromosome represented as a binary vector.

    vector<int> p2 = {0,1,0,0,1,1,0,1};
    // Parent 2 chromosome represented as a binary vector.

    int n = p1.size();
    // Total number of genes (bits) in each parent.

    int point = rand() % n;
    // Randomly select a crossover point between 0 and n-1.
    // Example: if n = 8 and point = 4, crossover happens after the 4th gene.

    // -------------------- PERFORM CROSSOVER --------------------
    for(int i = point; i < n; i++)
        swap(p1[i], p2[i]);
    // Swap all genes from the crossover point till the end of chromosome.
    // This mixes genetic material between both parents.
    //
    // Example:
    // p1: 10110010
    // p2: 01001101
    // If point = 4
    // Swap part [4..7]
    // → Child1: 10111101
    // → Child2: 01000010

    // -------------------- OUTPUT CHILDREN --------------------
    cout << "Child1: ";
    for(int b : p1) cout << b;
    // Print all bits of Child 1.

    cout << "\nChild2: ";
    for(int b : p2) cout << b;
    // Print all bits of Child 2.

    // -------------------- SUMMARY --------------------
    // Single-Point Crossover Steps:
    // 1️⃣ Choose one random crossover point.
    // 2️⃣ Copy all genes before that point from each parent.
    // 3️⃣ Swap all genes after that point between the two parents.
    // 4️⃣ Result: Two children that share early genes with their own parent
    //    and later genes with the other parent.
}
