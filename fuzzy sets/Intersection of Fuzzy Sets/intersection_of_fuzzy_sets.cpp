#include <iostream>
using namespace std;

int main() {

    // Creating first fuzzy set A with 4 elements
    // Each element has 2 values: first → element value, second → membership value
    // Example: (2,1) means element '2' has membership 1 in the fuzzy set
    float A[4][2] = {{2,1},{4,0.3},{6,0.5},{8,0.2}};

    // Creating second fuzzy set B with same number of elements
    // Each membership value may be different from A
    float B[4][2] = {{2,0.5},{4,0.4},{6,0.1},{8,1}};

    // Declaring a new array to store the intersection result of A and B
    float Intersection[4][2];

    // Loop through all elements of the fuzzy sets
    for(int i = 0; i < 4; i++) {

        // Loop through both columns (element value and membership value)
        for(int j = 0; j < 2; j++) {

            // Intersection rule in fuzzy logic:
            // µ(A ∩ B)(x) = min(µA(x), µB(x))
            // So, for each element, we take the minimum membership value
            Intersection[i][j] = min(A[i][j], B[i][j]);
        }
    }

    // Displaying the final intersection set
    for(int i = 0; i < 4; i++) {

        // Print opening curly bracket for each element pair
        cout << "{ ";

        // Print both element value and its new membership value
        for(int j = 0; j < 2; j++) {
            cout << Intersection[i][j] << "  ";
        }

        // Close the element pair and leave space for next one
        cout << "}  ";
    }

    // Return 0 means successful program execution
    return 0;
}
