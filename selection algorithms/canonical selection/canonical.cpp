#include <iostream>     // for input-output operations
#include <vector>       // to use the vector container
using namespace std;    // to avoid using std:: repeatedly

//------------------------------------------------------
// Function: calculate_F_bar()
// Purpose : To calculate the average fitness value (F̄)
//------------------------------------------------------
float calulate_F_bar(vector<float>& fitness) {
    float sum = 0;   // variable to store total sum of all fitness values
    
    // loop to calculate total fitness
    for (int i = 0; i < fitness.size(); i++) {
        sum += fitness[i];  // adding each fitness value to the total
    }
    
    // calculate average (F̄ = total_fitness / population_size)
    float avg = sum / fitness.size();
    return avg;  // return average fitness value
}

//------------------------------------------------------
// Function: canonical()
// Purpose : To normalize fitness values using F̄
//           and then sort them in ascending order
//------------------------------------------------------
void canonical(vector<float>& fitness, float avg_f) {
    vector<float> canonical;   // new vector to store normalized fitness values
    
    // Step 1: Normalize each fitness value
    // Formula: normalized_value = fitness[i] / F̄
    for (int i = 0; i < fitness.size(); i++) {
        canonical.push_back(fitness[i] / avg_f);
    }

    // Step 2: Sort fitness values using insertion sort (ascending)
    for (int j = 1; j < fitness.size(); j++) {
        for (int k = j; k > 0; k--) {
            if (fitness[k] < fitness[k - 1]) {
                swap(fitness[k], fitness[k - 1]); // swap if out of order
            } else {
                break;  // stop if correct order is reached
            }
        }
    }
}

//------------------------------------------------------
// Function: print_canonical()
// Purpose : To print top Np_no canonical fitness values
//------------------------------------------------------
void print_canonical(vector<float> &canonical, int Np_no) {
    // Print the Np_no highest fitness values
    for (int i = canonical.size() - 1; i >= canonical.size() - Np_no; i--) {
        cout << canonical[i] << " ";   // printing selected values
    }
}

//------------------------------------------------------
// MAIN FUNCTION
//------------------------------------------------------
int main() {

    // Step 1: Define fitness values of all individuals in population
    vector<float> fitness = {1.01, 2.11, 3.11, 4.01, 1.91, 1.93, 4.51};

    // Step 2: Calculate the average fitness F̄
    float F_bar = calulate_F_bar(fitness);

    // Step 3: Apply canonical transformation and sorting
    canonical(fitness, F_bar);

    // Step 4: Select and print top 5 individuals (fittest)
    print_canonical(fitness, 5);

    return 0;
}

/* -------------------------------------------------------------------------
   💡 EXPLANATION OF CODE (Canonical Selection Algorithm)
   -------------------------------------------------------------------------
   ✅ Objective:
      - To select the best individuals from a population based on fitness values.
      - The canonical method normalizes and ranks individuals using average fitness.

   ✅ Steps:
      1. Compute the average fitness F̄ of the population.
      2. Normalize each individual's fitness = fitness[i] / F̄.
      3. Sort the individuals in ascending order of fitness.
      4. Select top 'Np_no' (best) individuals based on fitness.

   ✅ Example:
      Fitness Values: [1.01, 2.11, 3.11, 4.01, 1.91, 1.93, 4.51]
      Average F̄ = 2.655
      Normalized Values = [0.38, 0.79, 1.17, 1.51, 0.72, 0.73, 1.70]
      After Sorting → Select Top 5 (highest)

   ✅ Output:
      Displays the top 5 fittest normalized values.
--------------------------------------------------------------------------*/

/* -------------------------------------------------------------------------
   🧠 PSEUDOCODE: Canonical Selection Algorithm
   -------------------------------------------------------------------------
   START
       Initialize population with fitness values
       Calculate F̄ = (sum of all fitness values) / (population size)
       FOR each individual i in population
           Normalize fitness[i] = fitness[i] / F̄
       END FOR
       Sort population based on fitness values (ascending)
       Select top N individuals with highest fitness
       Display selected individuals
   END
--------------------------------------------------------------------------*/
