#include <iostream>
using namespace std;

int main() {
    // -------------------- FUZZY SET COMPLEMENT --------------------
    // In fuzzy logic, every element has a value between 0 and 1.
    // This value shows how much that element belongs to the set.
    // The "complement" means the opposite — how much it does NOT belong.
    // Formula:  new value = 1 - old value

    // Here we have a fuzzy set A with 4 elements.
    // Each row has two values: { element, membership_value }
    float A[4][2] = {
        {2, 1},     // element = 2, belongs fully (1 means 100%)
        {4, 0.3},   // element = 4, belongs 30%
        {6, 0.5},   // element = 6, belongs 50%
        {8, 0.2}    // element = 8, belongs 20%
    };

    // This array will store the complement (opposite) values.
    float Compliment[4][2];

    // -------------------- STEP 1: FIND COMPLEMENT --------------------
    for(int i = 0; i < 4; i++) {
        // Keep the same element value (like 2, 4, 6, 8)
        Compliment[i][0] = A[i][0];

        // Calculate its opposite membership
        // Example: if element was 0.3, new one = 1 - 0.3 = 0.7
        Compliment[i][1] = 1 - A[i][1];
    }

    // -------------------- STEP 2: SHOW OUTPUT --------------------
    // Print all elements of the complement set
    for(int i = 0; i < 4; i++) {
        cout << "{ ";
        for(int j = 0; j < 2; j++) {
            cout << Compliment[i][j] << "  ";  // show element and its new value
        }
        cout << "}  "; // space between elements
    }

    return 0;
}
