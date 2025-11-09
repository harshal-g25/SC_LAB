#include <bits/stdc++.h>
using namespace std;

int main() {
    // -------------------- SHUFFLE CROSSOVER --------------------
    // Shuffle Crossover is a variation of single-point crossover.
    // Before performing crossover, the positions (indices) of genes
    // are randomly shuffled. After crossover, the genes are restored
    // back to their original positions using the same shuffle order.
    //
    // This adds randomness to which genes are combined — not just based
    // on their positions — helping improve diversity in the population.

    vector<int> p1 = {1,0,1,1,0,0,1,0};
    // Parent 1 chromosome represented as a binary vector.

    vector<int> p2 = {0,1,0,0,1,1,0,1};
    // Parent 2 chromosome represented as a binary vector.

    int n = p1.size();
    // Total number of genes (bits) in each parent.

    // -------------------- STEP 1: SHUFFLE INDEX ORDER --------------------
    vector<int> index(n);
    iota(index.begin(), index.end(), 0);
    // 'iota' fills 'index' with values 0, 1, 2, 3, ..., n-1.
    // This represents all gene positions.

    random_shuffle(index.begin(), index.end());
    // Randomly shuffle the indices to mix up the gene order.
    // Example: index might become [3,0,7,5,1,4,6,2]

    // -------------------- STEP 2: REORDER GENES ACCORDING TO SHUFFLE --------------------
    vector<int> s1(n), s2(n);
    // Temporary shuffled versions of parent chromosomes.

    for(int i = 0; i < n; i++) {
        s1[i] = p1[index[i]];
        s2[i] = p2[index[i]];
    }
    // Now 's1' and 's2' are the parents but with genes rearranged
    // according to the shuffled index order.

    // -------------------- STEP 3: APPLY SINGLE-POINT CROSSOVER --------------------
    int point = rand() % n;
    // Randomly choose a crossover point (between 0 and n-1).

    for(int i = point; i < n; i++)
        swap(s1[i], s2[i]);
    // Perform standard single-point crossover *on the shuffled genes*.
    // After the crossover point, genes are swapped between the two parents.

    // -------------------- STEP 4: UNSHUFFLE (RESTORE ORIGINAL ORDER) --------------------
    vector<int> c1(n), c2(n);
    // These will store the final child chromosomes in original order.

    for(int i = 0; i < n; i++) {
        c1[index[i]] = s1[i];
        c2[index[i]] = s2[i];
    }
    // Restore the shuffled genes to their original positions
    // using the same index array.

    // -------------------- STEP 5: OUTPUT CHILDREN --------------------
    cout << "Child1: ";
    for(int b : c1) cout << b;

    cout << "\nChild2: ";
    for(int b : c2) cout << b;

    // -------------------- SUMMARY --------------------
    // 1️⃣ Shuffle the order of genes randomly.
    // 2️⃣ Perform single-point crossover on the shuffled genes.
    // 3️⃣ Unshuffle them back to original order.
    //
    // This prevents crossover from always happening on the same positions,
    // leading to more diverse and unbiased offspring combinations.
}
