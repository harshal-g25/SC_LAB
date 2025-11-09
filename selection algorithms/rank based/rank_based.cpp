#include <iostream>     // For input/output operations (cout, endl)
#include <vector>       // To use the vector container (dynamic array)
using namespace std;    // To avoid writing std:: repeatedly

/* -------------------------------------------------------------
   🔹 Function: calulate_Rank()
   Purpose:
     - Sorts the fitness values in ascending order.
     - Assigns ranks to individuals based on fitness value.
     - The fittest individuals get the highest rank.
--------------------------------------------------------------*/
vector<double> calulate_Rank(vector<double>& fitness) {

    // Sorting fitness values using insertion sort (ascending order)
    for (int j = 1; j < fitness.size(); j++) {
        for (int k = j; k > 0; k--) {
            if (fitness[k] < fitness[k - 1]) {
                swap(fitness[k], fitness[k - 1]); // Swap if out of order
            } else {
                break;  // Stop if order is correct
            }
        }
    }

    // Return sorted (ranked) fitness vector
    return fitness;
}

/* -------------------------------------------------------------
   🔹 Function: calculate_area()
   Purpose:
     - Converts ranks into percentage probability.
     - Simulates a “roulette wheel” where each rank gets
       a portion of the wheel proportional to its rank.
     - The higher the rank, the larger the area (chance to be selected).
--------------------------------------------------------------*/
vector<vector<double>> calculate_area(vector<double> rank) {

    int size = rank.size();            // Number of individuals
    int total = (size * (size + 1)) / 2;  // Sum of first N natural numbers → 1 + 2 + ... + N

    vector<vector<double>> area;       // To store {fitness_value, area_percentage}

    for (int i = 0; i < rank.size(); i++) {
        double a = (double)(i + 1) / total;   // Rank weight divided by total
        area.push_back({rank[i], a * 100});   // Store fitness and corresponding percentage
    }

    return area;  // Return the computed rank-percentage pairs
}

/* -------------------------------------------------------------
   🔹 Function: print_wheel()
   Purpose:
     - Displays the fitness values along with their selection
       probability percentage (wheel area).
     - This helps visualize how rank affects selection chance.
--------------------------------------------------------------*/
void print_wheel(vector<vector<double>> wheel) {

    for (int i = 0; i < wheel.size(); i++) {
        cout << wheel[i][0] << " " << "--->" << " " << wheel[i][1] << "%" << endl;
        // Example output: 0.02 ---> 10%
    }
}

/* -------------------------------------------------------------
   🔹 MAIN FUNCTION
   Steps:
     1. Define fitness values for all individuals.
     2. Rank them based on fitness.
     3. Assign roulette-wheel area based on rank.
     4. Display the wheel (fitness vs probability).
--------------------------------------------------------------*/
int main() {

    // Step 1: Initial fitness values of population
    vector<double> fitness = {0.4, 0.05, 0.03, 0.02};

    // Step 2: Rank the individuals (sorted ascending)
    vector<double> rank = calulate_Rank(fitness);

    // Step 3: Compute area (selection probability) based on rank
    vector<vector<double>> area = calculate_area(rank);

    // Step 4: Print the wheel with fitness and percentage area
    print_wheel(area);

    return 0;
}

/* ------------------------------------------------------------------------
   🧠 EASY EXPLANATION — RANK-BASED SELECTION
   ------------------------------------------------------------------------
   ✅ Purpose:
      - Used in Genetic Algorithms for fairer selection.
      - Instead of directly using raw fitness values,
        individuals are ranked and assigned probabilities
        based on their rank position.

   ✅ Why rank-based?
      - It avoids dominance by extremely high fitness values.
      - Ensures weaker individuals still have a small chance to reproduce.

   ✅ Working Steps:
      1️⃣ Sort all individuals by fitness (lowest → highest).
      2️⃣ Assign rank numbers: 1, 2, 3, ..., N.
      3️⃣ Calculate total of all ranks (1 + 2 + ... + N).
      4️⃣ For each individual:
            Probability = (Rank / Total_Rank_Sum) × 100
      5️⃣ Display probabilities (used for roulette wheel selection).

   ✅ Example:
      Fitness = [0.4, 0.05, 0.03, 0.02]
      After Sorting → [0.02, 0.03, 0.05, 0.4]
      Total Rank Sum = 1+2+3+4 = 10

      Assigned Probabilities:
        Rank 1 → (1/10)*100 = 10%
        Rank 2 → (2/10)*100 = 20%
        Rank 3 → (3/10)*100 = 30%
        Rank 4 → (4/10)*100 = 40%

      So, the best individual (0.4) gets the largest share (40%)
      in the selection wheel.

   ✅ Output Example:
      0.02 ---> 10%
      0.03 ---> 20%
      0.05 ---> 30%
      0.4  ---> 40%

------------------------------------------------------------------------*/

/* ------------------------------------------------------------------------
   📋 PSEUDOCODE — Rank-Based Selection
   ------------------------------------------------------------------------
   START
       Initialize fitness values for population
       Sort fitness values in ascending order
       Compute total = N * (N + 1) / 2
       FOR each individual i from 1 to N:
           Probability = (i / total) * 100
           Store {fitness[i], Probability}
       END FOR
       Print fitness vs probability
   END
------------------------------------------------------------------------*/
