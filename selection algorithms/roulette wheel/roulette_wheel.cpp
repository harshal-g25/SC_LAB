#include <iostream>     // Header file for input-output operations like cout and cin
#include <vector>       // Header file to use dynamic arrays (vectors)
using namespace std;    // So we can write cout instead of std::cout

//----------------------------------------------
// Function 1: To calculate the probability (pi)
//----------------------------------------------
vector<float> calculate_pi(vector<float>&fitness){  // Takes 'fitness' values of all individuals
    float sum=0;    // Variable to store total fitness
    vector<float>pi;    // Vector to store individual probabilities

    // Step 1: Calculate the total sum of all fitness values
    for(int i=0;i<fitness.size();i++){  // Loop through all fitness values
        sum+=fitness[i];                 // Add each fitness value to sum
    }

    // Step 2: Calculate individual probability = fitness / total sum
    for(int j=0;j<fitness.size();j++){   // Loop again through fitness
        pi.push_back(fitness[j]/sum);    // Store each probability in vector pi
    }

    return pi;   // Return vector containing probability values
}

//-----------------------------------------------------
// Function 2: To calculate cumulative probability (Pi)
//-----------------------------------------------------
vector<float> calculate_Pi(vector<float>&pi){    // Takes probability vector as input
    vector<float>Pi;     // Vector to store cumulative probabilities

    Pi.push_back(pi[0]); // First cumulative value is same as first probability

    // Step 1: Each next value is sum of all previous probabilities
    for(int i=1;i<pi.size();i++){   // Start from index 1
        Pi.push_back(Pi[i-1]+pi[i]); // Add current pi to previous cumulative value
    }

    return Pi;  // Return the cumulative probability list
}

//---------------------------------------------------------
// Function 3: Perform Roulette Wheel Selection Operation
//---------------------------------------------------------
vector<int> roulette_wheel(vector<float>&random,vector<float>&Pi){
    vector<int>tally(Pi.size(),0);  // Create a vector 'tally' initialized to 0 for counting selections

    // Step 1: For every random number, check where it fits in cumulative range
    for(int i=0;i<Pi.size();i++){    // Loop through all random numbers
        for(int j=1;j<Pi.size()-1;j++){   // Loop through all cumulative probabilities
            if(random[i]>Pi[j-1] && random[i]<=Pi[j]){  
                // If random number falls in this range, that individual is selected
                tally[j] = tally[j] + 1;  // Increase its count by 1
                cout<<j<<" ----> "<<Pi[j]<<" Selected.."<<endl; // Display which index is selected
            }
        }
    }
    return tally;   // Return tally of selected individuals
}


//-------------------------------
// MAIN FUNCTION (Program start)
//-------------------------------
int main(){

// Step 1: Random numbers between 0 and 1 to simulate wheel spin
vector<float> random = {0.26,0.06,0.48,0.43,0.09,0.30,0.61};

// Step 2: Fitness values of each individual
vector<float> fitness = {1.01,2.11,3.11,4.01,1.91,1.93,4.51};

// Step 3: Calculate individual selection probabilities
vector<float> pi = calculate_pi(fitness);

// Step 4: Calculate cumulative probabilities (to form the wheel)
vector<float> Pi = calculate_Pi(pi);

// Step 5: Perform the Roulette Wheel Selection using random numbers
vector<int> tally = roulette_wheel(random,Pi);

// Step 6: Print the cumulative probability wheel values
for(int i=0;i<Pi.size();i++){
    cout<<Pi[i]<<" "<<endl;  // Display each cumulative probability
}

return 0;  // End of main function
}


//-----------------------------------------------
// PSEUDOCODE (Roulette Wheel Selection Concept)
//-----------------------------------------------

/*
1. Input: List of fitness values for each individual.
2. Compute total fitness = sum of all fitness values.
3. For each individual:
       pi[i] = fitness[i] / total fitness     → probability of selection.
4. Compute cumulative probability:
       Pi[i] = Pi[i-1] + pi[i]
   → This creates the "wheel" divided into proportional sections.
5. Generate random numbers between 0 and 1.
6. For each random number:
       If Pi[j-1] < random[i] ≤ Pi[j], select individual j.
7. Count how many times each individual is selected (stored in tally).
8. Output the selected individuals and their probabilities.

Example:
   Fitness = [1, 2, 3, 4]
   Probabilities (pi) = [0.1, 0.2, 0.3, 0.4]
   Cumulative (Pi) = [0.1, 0.3, 0.6, 1.0]
   Random = 0.25 → falls between 0.1 and 0.3 → Select 2nd individual.
*/
