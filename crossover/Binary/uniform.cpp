#include <bits/stdc++.h>
using namespace std;

int main() {
    // -------------------- UNIFORM CROSSOVER --------------------
    // In this crossover method, every gene (bit) has an equal probability
    // of being swapped between the two parents — typically 50%.
    // This creates highly diverse offspring by mixing genes freely.

    vector<int> p1 = {1,0,1,1,0,0,1,0};  // Parent 1
    vector<int> p2 = {0,1,0,0,1,1,0,1};  // Parent 2

    // -------------------- STEP 1: RANDOMLY SWAP GENES --------------------
    // For each position, generate a random number (0 or 1)
    // If it's 1 → swap the genes at that position.
    // This means every gene has 50% chance of crossover.
    for(int i = 0; i < p1.size(); i++)
        if(rand() % 2) swap(p1[i], p2[i]);

    // -------------------- STEP 2: DISPLAY OFFSPRING --------------------
    cout << "Child1: ";
    for(int b : p1) cout << b;  // Prints child 1 genes
    cout << "\nChild2: ";
    for(int b : p2) cout << b;  // Prints child 2 genes

    // -------------------- EXAMPLE --------------------
    // Parent1: 10110010
    // Parent2: 01001101
    // Random swap decisions (50% chance each): [1, 0, 1, 0, 1, 0, 0, 1]
    //
    // Child1:  00110111
    // Child2:  11001000
    //
    // -------------------- SUMMARY --------------------
    // ✅ Uniform Crossover swaps genes independently with 50% chance.
    // ✅ Allows maximum mixing of genetic material.
    // ✅ Usefu
