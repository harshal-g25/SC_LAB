#include <iostream>        // for input/output operations
#include <vector>          // for using dynamic arrays (vectors)
#include <random>          // for generating random numbers
#include <cfloat>          // for constants like FLT_MAX (if needed)
#include <cmath>           // for mathematical functions like fabs(), pow()
using namespace std;       // to avoid writing std:: repeatedly


// --------------------------- FUNCTION: Initialize_Positions ---------------------------
// Purpose: Create initial random positions of all wolves in 2D space
// Each wolf has 2 coordinates (x, y)
vector<vector<float>> Initialize_Positions(float Upper_Bound, float Lower_Bound, int Population_Size)
{
    // Create a 2D vector of size [Population_Size x 2]
    vector<vector<float>> Initial_Positions(Population_Size, vector<float>(2));

    // Random number generator setup
    random_device rd;           // used as a seed for random generation
    mt19937 gen(rd());          // Mersenne Twister engine (produces high-quality random numbers)
    uniform_real_distribution<> dist(0.0, 1.0); // generates numbers between 0 and 1

    // Loop through each wolf to assign random positions
    for (int i = 0; i < Population_Size; i++)
    {
        // Generate two random numbers for X and Y coordinates
        float rand1 = dist(gen);
        float rand2 = dist(gen);

        // Scale the random numbers within given bounds
        Initial_Positions[i][0] = Lower_Bound + rand1 * (Upper_Bound - Lower_Bound);
        Initial_Positions[i][1] = Lower_Bound + rand2 * (Upper_Bound - Lower_Bound);
    }
    // Return the list of initialized wolf positions
    return Initial_Positions;
}


// --------------------------- FUNCTION: Mini_Value ---------------------------
// Calculates the objective function value for a given position (X, Y)
// The function to minimize is: f(x,y) = x² - xy + y² + 2x + 4y + 3
float Mini_Value(vector<float> &Points)
{
    float Minimized_Value = (Points[0] * Points[0]) - (Points[0] * Points[1]) +
                            (Points[1] * Points[1]) + 2 * Points[0] + 4 * Points[1] + 3;
    return Minimized_Value;
}


// --------------------------- FUNCTION: Minimize_Function ---------------------------
// Calculates objective values for all wolves in population
vector<float> Minimize_Function(vector<vector<float>> &Positions, int Population_Size)
{
    vector<float> Minimized_Values(Population_Size);  // store fitness of each wolf
    for (int i = 0; i < Population_Size; i++)
    {
        Minimized_Values[i] = (Positions[i][0] * Positions[i][0]) -
                              (Positions[i][0] * Positions[i][1]) +
                              (Positions[i][1] * Positions[i][1]) +
                              2 * Positions[i][0] + 4 * Positions[i][1] + 3;
    }
    return Minimized_Values;
}


// --------------------------- FUNCTION: Best_Values ---------------------------
// Finds the top 3 wolves with the smallest fitness values
// These are Alpha (best), Beta (second best), and Delta (third best)
vector<vector<float>> Best_Values(vector<vector<float>> &Positions, int Population_Size)
{
    vector<float> Min = Minimize_Function(Positions, Population_Size); // calculate all fitness values
    vector<vector<float>> Best_Positions(3, vector<float>(2));         // store top 3 wolves

    int index_Xa = 0; // index of Alpha wolf
    int index_Xb = 0; // index of Beta wolf
    int index_Xd = 0; // index of Delta wolf

    // Step 1: Find Alpha (lowest fitness)
    for (int i = 0; i < Population_Size; i++)
    {
        if (Min[i] < Min[index_Xa])
        {
            index_Xa = i;
            index_Xb = i + 1;
            index_Xd = i + 2;
        }
    }

    // Step 2: Find Beta (second best)
    for (int j = 0; j < Population_Size; j++)
    {
        if (j != index_Xa && Min[j] < Min[index_Xb])
        {
            index_Xb = j;
            index_Xd = j + 1;
        }
    }

    // Step 3: Find Delta (third best)
    for (int k = 0; k < Population_Size; k++)
    {
        if (k != index_Xa && k != index_Xb && Min[k] < Min[index_Xd])
        {
            index_Xd = k;
        }
    }

    // Store the best three wolves’ positions
    Best_Positions[0] = Positions[index_Xa];
    Best_Positions[1] = Positions[index_Xb];
    Best_Positions[2] = Positions[index_Xd];

    return Best_Positions;
}


// --------------------------- FUNCTION: a(iteration) ---------------------------
// Linearly decreases ‘a’ from 2 to 0 as iterations progress
float a(int iteration, int max_iteration)
{
    return 2 * (1 - (float)iteration / max_iteration);
}


// --------------------------- FUNCTION: c() ---------------------------
// Returns a random value between 0 and 2
float c()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(0.0, 1.0);
    float random = dist(gen);
    return 2 * random;
}


// --------------------------- FUNCTION: A(a) ---------------------------
// Calculates vector A = 2*a*r - a (a: shrinking factor, r: random number)
float A(float a)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(0.0, 1.0);
    float random = dist(gen);
    return 2 * (a * random) - a;
}


// --------------------------- FUNCTION: Dabd ---------------------------
// Calculates distance between current wolf and Alpha, Beta, Delta
vector<vector<float>> Dabd(vector<vector<float>> &Best_Positions, vector<float> &curr_pos)
{
    vector<vector<float>> Dabd(3, vector<float>(2));
    for (int i = 0; i < 3; i++)
    {
        float C = c(); // random coefficient
        // |C * X_leader - X_wolf|
        Dabd[i][0] = fabs(C * Best_Positions[i][0] - curr_pos[0]);
        Dabd[i][1] = fabs(C * Best_Positions[i][1] - curr_pos[1]);
    }
    return Dabd;
}


// --------------------------- FUNCTION: Xnew ---------------------------
// Updates wolf’s position based on Alpha, Beta, Delta positions
vector<float> Xnew(vector<vector<float>> &Best_Positions, vector<vector<float>> &Dabd, float small_a)
{
    vector<vector<float>> X123(3, vector<float>(2));
    float Xnew_x1 = 0;
    float Xnew_x2 = 0;

    for (int i = 0; i < 3; i++)
    {
        float big_A = A(small_a); // calculate A each time

        // Update position using: X = X_leader - A * D
        X123[i][0] = Best_Positions[i][0] - big_A * Dabd[i][0];
        if (X123[i][0] < -5) X123[i][0] = -5;
        if (X123[i][0] > 5)  X123[i][0] = 5;
        Xnew_x1 += X123[i][0];

        X123[i][1] = Best_Positions[i][1] - big_A * Dabd[i][1];
        if (X123[i][1] < -5) X123[i][1] = -5;
        if (X123[i][1] > 5)  X123[i][1] = 5;
        Xnew_x2 += X123[i][1];
    }

    // Average the three leader influences (α, β, δ)
    float Xnew_avg_x1 = Xnew_x1 / 3;
    float Xnew_avg_x2 = Xnew_x2 / 3;

    return {Xnew_avg_x1, Xnew_avg_x2};
}


// --------------------------- MAIN FUNCTION ---------------------------
int main()
{
    // Define bounds and population size
    float Upper_Bound = 5;
    float Lower_Bound = -5;
    int Population_Size = 5;

    // Step 1: Initialize random positions of wolves
    vector<vector<float>> Positions = Initialize_Positions(Upper_Bound, Lower_Bound, Population_Size);

    // Run GWO for 200 iterations
    for (int i = 1; i <= 200; i++)
    {
        int iteration = i;
        int max_iteration = 200;

        // Update the parameter 'a' which controls exploration vs exploitation
        float small_a = a(iteration, max_iteration);

        // Step 2: Find Alpha, Beta, Delta wolves
        vector<vector<float>> Best_Positions = Best_Values(Positions, Population_Size);

        // Step 3: Evaluate fitness of all wolves
        vector<float> Minimized_Values = Minimize_Function(Positions, Population_Size);

        // Print current positions and their fitness values
        cout << "Printing Positions : " << endl;
        for (int k = 0; k < Population_Size; k++)
            cout << Positions[k][0] << " " << Positions[k][1] << endl;

        cout << "Printing Minimized Values : " << endl;
        for (int m = 0; m < Population_Size; m++)
            cout << Minimized_Values[m] << endl;

        // Step 4: Update each wolf’s position
        for (int j = 0; j < Population_Size; j++)
        {
            vector<float> Current_Position = Positions[j];
            vector<vector<float>> Dalpha_beta_delta = Dabd(Best_Positions, Current_Position);
            vector<float> X_NEW = Xnew(Best_Positions, Dalpha_beta_delta, small_a);

            // Step 5: Replace wolf with new position if improvement found
            float fu_value_Xnew = Mini_Value(X_NEW);
            float fu_value_X = Mini_Value(Current_Position);

            if (fu_value_Xnew < fu_value_X)
            {
                Positions[j][0] = X_NEW[0];
                Positions[j][1] = X_NEW[1];
            }
        }
    }
}



// --------------------------- PSEUDOCODE (GREY WOLF OPTIMIZATION) ---------------------------
/*
Initialize population Xi (i = 1, 2, …, n) randomly
Initialize parameters: max_iter, a (from 2 to 0)

Repeat until max_iter:
    1. Evaluate fitness f(Xi) for all wolves
    2. Identify best three wolves:
       α = best solution (lowest fitness)
       β = second best
       δ = third best
    3. For each wolf Xi:
        For each dimension:
            Compute A = 2*a*r1 - a
            Compute C = 2*r2
            Compute distances:
                Dα = |Cα * Xα - Xi|
                Dβ = |Cβ * Xβ - Xi|
                Dδ = |Cδ * Xδ - Xi|
            Compute new position:
                X1 = Xα - Aα * Dα
                X2 = Xβ - Aβ * Dβ
                X3 = Xδ - Aδ * Dδ
            Xi(new) = (X1 + X2 + X3) / 3
    4. Update a = 2 * (1 - iteration / max_iteration)

Return α (best found solution)
*/
