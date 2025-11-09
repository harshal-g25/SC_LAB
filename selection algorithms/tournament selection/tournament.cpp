#include <iostream>     // For input-output (cout, endl)
#include <vector>       // For using vectors (dynamic arrays)
#include <random>       // For generating random numbers
using namespace std;

const int Nu = 2;  // Constant (represents number of individuals compared in each tournament)

//------------------------------------------
// Function: solution()
// Performs Tournament Selection
//------------------------------------------
vector<vector<float>> solution(vector<vector<float>> input, int Np) {
    // input → list of individuals with their fitness values
    // Np → number of tournaments to perform (number of selections)

    vector<vector<float>> solution;  // To store tournament results (competitors + winner)

    // Loop to perform Np tournaments
    for (int i = 0; i < Np; i++) {

        // Random number generator setup
        static random_device rd;     // Random device as seed
        static mt19937 gen(rd());    // Mersenne Twister random generator
        uniform_int_distribution<> dist(0, input.size() - 1);  // Uniform distribution from 0 to last index

        // Select two random individuals
        int rand1 = dist(gen);    // First random index
        int rand2 = dist(gen);    // Second random index

        // Ensure both individuals are different
        while (rand2 == rand1)
            rand2 = dist(gen);

        // Get their fitness values
        float first_individual = input[rand1][1];
        float second_individual = input[rand2][1];

        // Step: Compare who has higher fitness
        float selected = max(first_individual, second_individual);
        int select;  // To store index of selected individual

        // Determine which index corresponds to the winner
        if (selected == input[rand1][1]) {
            select = rand1;   // First one wins
        } else {
            select = rand2;   // Second one wins
        }

        // Store result as {first, second, winner}
        // Adding +1 to make it human-readable (since index starts from 0)
        solution.push_back({float(rand1 + 1), float(rand2 + 1), float(select + 1)});
    }

    return solution;  // Return final tournament results
}

//------------------------------------------
// Function: print_solution_table()
// Prints the tournament results
//------------------------------------------
void print_solution_table(vector<vector<float>> solution) {
    for (int i = 0; i < solution.size(); i++) {
        cout << "(" << solution[i][0] << "," << solution[i][1] << ")"
             << "  ----------> " << solution[i][2] << endl;
        // Example: (2,5) ---> 5  means between individuals 2 and 5, 5 won
    }
}

//------------------------------------------
// MAIN FUNCTION
//------------------------------------------
int main() {
    // Step 1: Input list of individuals with their fitness values
    // Format: {Individual Number, Fitness Value}
    vector<vector<float>> input = {
        {1, 1.0}, {2, 2.1}, {3, 3.1}, {4, 4.0},
        {5, 4.6}, {6, 1.9}, {7, 1.8}, {8, 4.5}
    };

    // Step 2: Perform Tournament Selection for 8 individuals
    vector<vector<float>> output = solution(input, 8);

    // Step 3: Print results in table format
    print_solution_table(output);

    return 0;  // Program ends
}

/* ------------------------------------------------------
   PSEUDOCODE – TOURNAMENT SELECTION ALGORITHM (EASY)
   ------------------------------------------------------

1. Input: 
      - A list of individuals with their fitness values
      - Np = number of tournaments to perform

2. For i = 1 to Np do:
      a. Randomly select two different individuals (rand1, rand2)
      b. Compare their fitness values:
             If fitness[rand1] > fitness[rand2]
                   Winner = rand1
             Else
                   Winner = rand2
      c. Record result → (rand1, rand2) → Winner

3. Repeat until all Np tournaments are done.

4. Output: 
      - A table showing which individual competed and who won.

Example:
   Input fitness values:
     ID: 1  2  3  4
     F:  2  4  1  5

   Tournament Example:
     (2,4) → Winner = 4
     (1,3) → Winner = 1
     (4,2) → Winner = 4

   Final Selected Individuals: [4, 1, 4]

------------------------------------------------------ */
