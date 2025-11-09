#include <iostream>     // Used for input and output (cout, cin)
#include <vector>       // Used for dynamic arrays (vectors)
#include <random>       // Used to generate random numbers for wolf positions
#include <cfloat>       // Contains constants for float limits
#include <cmath>        // Used for mathematical functions like fabs(), pow()
#include <fstream>      // Used to write data to a text file
using namespace std;    // Allows us to use names like cout, vector directly without std::

/////////////////////////////////////////////////////////////////////////////////////////////////
// Function: Initialize_Positions
// Purpose: Randomly initialize the positions of all wolves within the given bounds.
/////////////////////////////////////////////////////////////////////////////////////////////////
vector<vector<float>> Initialize_Positions(float Upper_Bound, float Lower_Bound, int Population_Size) {

    // Create a 2D vector with 'Population_Size' rows and 2 columns (x and y coordinates)
    vector<vector<float>> Initial_Positions(Population_Size, vector<float>(2));

    // Random number generator setup
    random_device rd;   // Creates a random seed from hardware
    mt19937 gen(rd());  // Mersenne Twister generator for random numbers
    uniform_real_distribution<> dist(0.0, 1.0); // Uniform distribution between 0 and 1

    // Loop to assign random x and y values for each wolf
    for (int i = 0; i < Population_Size; i++) {
        float rand1 = dist(gen);  // Random number 1 for x
        float rand2 = dist(gen);  // Random number 2 for y

        // Map random values between Lower_Bound and Upper_Bound
        Initial_Positions[i][0] = Lower_Bound + rand1 * (Upper_Bound - Lower_Bound); // x-coordinate
        Initial_Positions[i][1] = Lower_Bound + rand2 * (Upper_Bound - Lower_Bound); // y-coordinate
    }

    return Initial_Positions; // Return the initialized population
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Function: Mini_Value
// Purpose: Objective function that the wolves try to minimize.
// Formula: f(x, y) = x² - xy + y² + 2x + 4y + 3
/////////////////////////////////////////////////////////////////////////////////////////////////
float Mini_Value(vector<float> &Points) {
    return (Points[0] * Points[0]) - (Points[0] * Points[1]) + (Points[1] * Points[1]) + 2 * Points[0] + 4 * Points[1] + 3;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Function: Minimize_Function
// Purpose: Calculate the objective value for all wolves in the population
/////////////////////////////////////////////////////////////////////////////////////////////////
vector<float> Minimize_Function(vector<vector<float>> &Positions, int Population_Size) {
    vector<float> Minimized_Values(Population_Size); // Stores function value for each wolf

    for (int i = 0; i < Population_Size; i++) {
        Minimized_Values[i] = Mini_Value(Positions[i]); // Calculate and store each wolf's value
    }
    return Minimized_Values;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Function: Best_Values
// Purpose: Find the top 3 wolves - Alpha (best), Beta (second best), Delta (third best)
/////////////////////////////////////////////////////////////////////////////////////////////////
vector<vector<float>> Best_Values(vector<vector<float>> &Positions, int Population_Size, vector<int> &indices) {

    // Calculate fitness of all wolves
    vector<float> Min = Minimize_Function(Positions, Population_Size);

    // Create a list to store best three wolf indices (alpha, beta, delta)
    vector<vector<float>> Best_Positions(3, vector<float>(2));
    indices = {0, 1, 2};

    // Find the Alpha wolf (minimum function value)
    for (int i = 0; i < Population_Size; i++) {
        if (Min[i] < Min[indices[0]]) indices[0] = i;
    }

    // Find the Beta wolf (second minimum)
    for (int j = 0; j < Population_Size; j++) {
        if (j != indices[0] && Min[j] < Min[indices[1]]) indices[1] = j;
    }

    // Find the Delta wolf (third minimum)
    for (int k = 0; k < Population_Size; k++) {
        if (k != indices[0] && k != indices[1] && Min[k] < Min[indices[2]]) indices[2] = k;
    }

    // Store positions of the three best wolves
    Best_Positions[0] = Positions[indices[0]]; // Alpha
    Best_Positions[1] = Positions[indices[1]]; // Beta
    Best_Positions[2] = Positions[indices[2]]; // Delta

    return Best_Positions; // Return top three wolves' positions
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Function: a
// Purpose: Control parameter that decreases linearly from 2 to 0
// Formula: a = 2 * (1 - (iteration / max_iteration))
/////////////////////////////////////////////////////////////////////////////////////////////////
float a(int iteration, int max_iteration) {
    return 2 * (1 - (float)iteration / max_iteration);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Function: c
// Purpose: Random coefficient used to calculate distance (C = 2 * random number)
/////////////////////////////////////////////////////////////////////////////////////////////////
float c() {
    random_device rd; mt19937 gen(rd());
    uniform_real_distribution<> dist(0.0, 1.0);
    return 2 * dist(gen);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Function: A
// Purpose: Another coefficient (A = 2a * random - a)
// Controls exploration and exploitation behavior
/////////////////////////////////////////////////////////////////////////////////////////////////
float A(float a) {
    random_device rd; mt19937 gen(rd());
    uniform_real_distribution<> dist(0.0, 1.0);
    return 2 * (a * dist(gen)) - a;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Function: Dabd
// Purpose: Calculate distances Dα, Dβ, Dδ between wolf and best wolves
// Formula: D = |C * X_best - X_current|
/////////////////////////////////////////////////////////////////////////////////////////////////
vector<vector<float>> Dabd(vector<vector<float>> &Best_Positions, vector<float> &curr_pos) {
    vector<vector<float>> Dabd(3, vector<float>(2)); // 3 wolves × 2D positions

    for (int i = 0; i < 3; i++) {
        float C = c(); // Random coefficient for each best wolf
        Dabd[i][0] = fabs(C * Best_Positions[i][0] - curr_pos[0]); // X distance
        Dabd[i][1] = fabs(C * Best_Positions[i][1] - curr_pos[1]); // Y distance
    }
    return Dabd;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Function: Xnew
// Purpose: Calculate new position of wolf using alpha, beta, delta influence
// Formula: X_new = (X1 + X2 + X3) / 3
/////////////////////////////////////////////////////////////////////////////////////////////////
vector<float> Xnew(vector<vector<float>> &Best_Positions, vector<vector<float>> &Dabd, float small_a) {
    vector<vector<float>> X123(3, vector<float>(2));
    float Xnew_x1 = 0, Xnew_x2 = 0;

    for (int i = 0; i < 3; i++) {
        float big_A = A(small_a); // Calculate A for each best wolf

        // Calculate new position based on best wolves
        X123[i][0] = Best_Positions[i][0] - big_A * Dabd[i][0];
        X123[i][1] = Best_Positions[i][1] - big_A * Dabd[i][1];

        // Keep positions within allowed range [-5, 5]
        X123[i][0] = max(-5.0f, min(5.0f, X123[i][0]));
        X123[i][1] = max(-5.0f, min(5.0f, X123[i][1]));

        // Sum up for averaging later
        Xnew_x1 += X123[i][0];
        Xnew_x2 += X123[i][1];
    }

    // Return average position influenced by alpha, beta, delta
    return {Xnew_x1 / 3, Xnew_x2 / 3};
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// MAIN FUNCTION: Starts the Grey Wolf Optimization algorithm
/////////////////////////////////////////////////////////////////////////////////////////////////
int main() {

    float Upper_Bound = 5, Lower_Bound = -5;  // Search space boundaries
    int Population_Size = 5;                  // Number of wolves
    int max_iteration = 200;                  // Maximum iterations

    // Initialize wolf positions randomly
    vector<vector<float>> Positions = Initialize_Positions(Upper_Bound, Lower_Bound, Population_Size);

    // Open file to store output for plotting or analysis
    ofstream fout("gwo_output.txt");

    // Main loop runs for each iteration
    for (int iteration = 1; iteration <= max_iteration; iteration++) {

        float small_a = a(iteration, max_iteration); // Update parameter 'a'

        vector<int> best_indices;  // Stores indices of alpha, beta, delta
        vector<vector<float>> Best_Positions = Best_Values(Positions, Population_Size, best_indices);
        vector<float> Minimized_Values = Minimize_Function(Positions, Population_Size);

        // Write positions and function values of all wolves
        for (int k = 0; k < Population_Size; k++) {
            fout << iteration << " " << k << " " 
                 << Positions[k][0] << " " << Positions[k][1] << " " 
                 << Minimized_Values[k] << endl;
        }

        // Write alpha, beta, delta details separately
        fout << "ALPHA " << iteration << " " << best_indices[0] << " "
             << Best_Positions[0][0] << " " << Best_Positions[0][1] << " "
             << Mini_Value(Best_Positions[0]) << endl;

        fout << "BETA " << iteration << " " << best_indices[1] << " "
             << Best_Positions[1][0] << " " << Best_Positions[1][1] << " "
             << Mini_Value(Best_Positions[1]) << endl;

        fout << "DELTA " << iteration << " " << best_indices[2] << " "
             << Best_Positions[2][0] << " " << Best_Positions[2][1] << " "
             << Mini_Value(Best_Positions[2]) << endl;

        // Update wolf positions using GWO equations
        for (int j = 0; j < Population_Size; j++) {
            vector<float> Current_Position = Positions[j];  // Get current wolf position
            vector<vector<float>> Dalpha_beta_delta = Dabd(Best_Positions, Current_Position);
            vector<float> X_NEW = Xnew(Best_Positions, Dalpha_beta_delta, small_a);

            // Replace with new position only if fitness improved
            if (Mini_Value(X_NEW) < Mini_Value(Current_Position)) {
                Positions[j] = X_NEW;
            }
        }
    }

    fout.close(); // Close output file
    return 0;     // End of program
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// PSEUDOCODE for GREY WOLF OPTIMIZATION
/////////////////////////////////////////////////////////////////////////////////////////////////
/*
Initialize population (positions of wolves) randomly within bounds
Repeat until max iterations:
    Calculate fitness (objective value) of each wolf
    Identify:
        Alpha = best solution
        Beta  = 2nd best solution
        Delta = 3rd best solution
    Update parameter a (linearly decreasing)
    For each wolf:
        Calculate coefficients A and C (randomly)
        Compute distances Dα, Dβ, Dδ from alpha, beta, delta
        Update position based on:
            X1 = Xα - A1 * Dα
            X2 = Xβ - A2 * Dβ
            X3 = Xδ - A3 * Dδ
        New Position = (X1 + X2 + X3) / 3
        If new position improves fitness:
            Replace old position
Return Alpha wolf position as optimal solution
*/
/////////////////////////////////////////////////////////////////////////////////////////////////
