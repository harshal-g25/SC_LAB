#include <iostream>    // For input/output operations
#include <limits.h>    // For INT_MAX (maximum integer value)
#include <cfloat>      // For DBL_MAX (maximum double value)
#include <fstream>     // For writing results to a file
using namespace std;   // To use standard library functions without std:: prefix

/*
-------------------------------------------------------------
🎯 PARTICLE SWARM OPTIMIZATION (PSO)
-------------------------------------------------------------
🧠 IDEA:
PSO is inspired by the behavior of a **swarm of birds** or **a school of fish** 
searching for food. Each particle represents a possible solution in the search space.

Every particle moves based on:
- Its **own best experience** (personal best = pbest)
- The **group’s best experience** (global best = gbest)

The goal: minimize the given function (find the best solution).

-------------------------------------------------------------
⚙️ FUNCTION TO MINIMIZE — Rosenbrock function:
-------------------------------------------------------------
The function used here is:
   f(x1, x2) = 100 * (x2 - x1²)² + (1 - x1)²

It is commonly used to test optimization algorithms.
The function has a minimum value (best point) at x1 = 1, x2 = 1, where f = 0.
*/
double function(double x1, double x2)
{
    double first = x2 - (x1 * x1);      // (x2 - x1²)
    double second = (1 - x1) * (1 - x1); // (1 - x1)²
    double third = first * first;         // (x2 - x1²)²
    double answer = (100 * third) + second; // Final result
    return answer;                         // Return the function value (fitness)
}

/*
-------------------------------------------------------------
🔹 FUNCTION: pgb_index()
Finds the index of the **particle with the best (minimum) fitness value**
-------------------------------------------------------------
*/
int pgb_index(double fitness[])
{
    float min = INT_MAX;  // Start with a very large number
    int index = -1;       // Store best index
    for (int i = 0; i < 8; i++)
    {
        if (fitness[i] < min)
        {
            min = fitness[i]; // Update if smaller fitness found
            index = i;        // Store index of best particle
        }
    }
    return index; // Return index of best particle
}

/*
-------------------------------------------------------------
🔹 MAIN FUNCTION — where PSO steps happen
-------------------------------------------------------------
*/
int main()
{
    // Search space limits (boundaries)
    float lower_limit = -5.0;
    float upper_limit = 5.0;

    // Initialize constants used in PSO
    float gbest = 14.222; // initial global best value (high to start)
    float c1 = 1.5;       // cognitive coefficient (importance of personal experience)
    float c2 = 2.0;       // social coefficient (importance of group experience)
    float w = 0.75;       // inertia weight (how much past velocity affects motion)

    /*
    -------------------------------------------------------------
    🔹 Particle Data Structure:
    Each row = one particle
    Columns: 
      [0] → x1 (position 1)
      [1] → x2 (position 2)
      [2] → v1 (velocity 1)
      [3] → v2 (velocity 2)
    -------------------------------------------------------------
    */
    double data[8][4] = {
        {2.212, 3.009, 0.0, 0.0},
        {-2.289, -2.396, 0.0, 0.0},
        {-2.393, -4.790, 0.0, 0.0},
        {-0.639, 1.692, 0.0, 0.0},
        {-3.168, 0.706, 0.0, 0.0},
        {0.215, -2.350, 0.0, 0.0},
        {-0.742, 1.934, 0.0, 0.0},
        {-4.563, 4.791, 0.0, 0.0}
    };

    // Initialize fitness array (each particle’s result)
    double fitness[8] = {DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX};

    // Store each particle’s best known position
    double local_best[8][2];
    for (int i = 0; i < 8; i++)
    {
        local_best[i][0] = data[i][0];
        local_best[i][1] = data[i][1];
    }

    // Random factors for exploration (usually random, but fixed here)
    float r1[8] = {0.661, 0.919, 0.782, 0.299, 0.874, 0.133, 0.031, 0.366};
    float r2[8] = {0.312, 0.271, 0.824, 0.055, 0.595, 0.582, 0.736, 0.954};

    // Output file to store progress
    ofstream fout("particles.txt");

    int iteration = 0; // Iteration counter

    /*
    -------------------------------------------------------------
    🔹 MAIN PSO LOOP
    -------------------------------------------------------------
    Continues until global best (gbest) becomes less than or equal to 14.222
    */
    while (gbest >= 14.222)
    {
        // STEP 1: Calculate fitness and update local bests
        for (int i = 0; i < 8; i++)
        {
            double last = fitness[i];                      // old fitness
            double current = function(data[i][0], data[i][1]); // new fitness

            if (current < last) // if better, update local best
            {
                fitness[i] = current;
                local_best[i][0] = data[i][0];
                local_best[i][1] = data[i][1];
            }

            if (fitness[i] < gbest) // check if global best improves
            {
                gbest = fitness[i];
            }
        }

        // STEP 2: Update velocities for all particles
        cout << "Printing Particle Velocity" << endl;
        cout << "---------------------------------------------------------------" << endl;

        for (int i = 0; i < 8; i++)
        {
            int g_index = pgb_index(fitness); // index of best particle globally

            // Velocity update formula:
            // v = w*v + c1*r1*(pbest - x) + c2*r2*(gbest - x)
            data[i][2] = w * data[i][2] + c1 * r1[i] * (local_best[i][0] - data[i][0]) +
                         c2 * r2[i] * (data[g_index][0] - data[i][0]);
            data[i][3] = w * data[i][3] + c1 * r1[i] * (local_best[i][1] - data[i][1]) +
                         c2 * r2[i] * (data[g_index][1] - data[i][1]);

            cout << data[i][2] << " " << data[i][3] << endl;
        }

        // STEP 3: Update particle positions
        cout << "Printing Particles: " << endl;
        cout << "---------------------------------------------------------------" << endl;

        for (int i = 0; i < 8; i++)
        {
            // Update position based on velocity
            data[i][0] = data[i][0] + data[i][2];
            data[i][1] = data[i][1] + data[i][3];

            // Keep particles within search space limits
            if (data[i][0] < lower_limit) data[i][0] = -5.0;
            else if (data[i][0] > upper_limit) data[i][0] = 5.0;

            if (data[i][1] < lower_limit) data[i][1] = -5.0;
            else if (data[i][1] > upper_limit) data[i][1] = 5.0;

            // Print and log results
            cout << data[i][0] << " " << data[i][1] << endl;
            fout << iteration << " " << i << " " << data[i][0] << " " << data[i][1]
                 << " " << function(data[i][0], data[i][1]) << endl;
        }

        // STEP 4: Write global best info to file
        int g_index = pgb_index(fitness);
        fout << "GLOBAL " << iteration << " "
             << g_index << " "
             << data[g_index][0] << " "
             << data[g_index][1] << " "
             << fitness[g_index] << endl;

        // Increment iteration
        iteration++;

        // Print fitness of all particles
        cout << "Printing Final Fitness:" << endl;
        cout << "---------------------------------------------------------------" << endl;
        for (int i = 0; i < 8; i++)
        {
            cout << fitness[i] << " " << endl;
        }
    }

    fout.close();
    cout << "---------------------------------------------------------------" << endl;
    return 0;
}

/*
-------------------------------------------------------------
📘 PSEUDOCODE (Simplified)
-------------------------------------------------------------
Start
  Initialize swarm of particles with random positions and velocities
  Set each particle’s local_best = current position
  Set global_best = best among all particles

  While (gbest not reached threshold):
     For each particle:
        Compute fitness using f(x1, x2)
        If current fitness < local_best → update local_best
        If local_best < global_best → update global_best

     For each particle:
        Update velocity:
           v = w*v + c1*r1*(pbest - x) + c2*r2*(gbest - x)
        Update position:
           x = x + v
        Keep x within limits [-5, 5]

     Print positions, velocities, fitness
     Save data to file

  End While
End
-------------------------------------------------------------
🧩 KEY FORMULAS:
-------------------------------------------------------------
Velocity Update:
   v = w*v + c1*r1*(pbest - x) + c2*r2*(gbest - x)
Position Update:
   x = x + v

-------------------------------------------------------------
✅ SUMMARY:
-------------------------------------------------------------
🔹 PSO starts with random particles (solutions).
🔹 Each particle moves towards:
     → its own best position (personal learning)
     → the best position found by the group (social learning)
🔹 Over time, all particles converge toward the best solution (minimum value).
-------------------------------------------------------------
*/
