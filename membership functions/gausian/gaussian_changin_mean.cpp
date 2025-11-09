#include <iostream>   // For input/output operations
#include <fstream>    // For writing output to a file
#include <cmath>      // For mathematical functions like exp() and pow()
using namespace std;  // Allows direct use of standard C++ library names

/*
   🔹 gaussian() function:
   This function represents the Gaussian (bell-shaped) membership function.
   It returns a value between 0 and 1, indicating how much the input value x 
   belongs to a fuzzy set (like “medium temperature” or “fast speed”).

   Formula used:
   μ(x) = exp( -0.5 * ((x - mean) / sigma)² )

   where:
   - x      → the input value
   - mean   → the center (where curve peaks)
   - sigma  → the spread (width) of the curve
*/
double gaussian(double x, double mean, double sigma) {
    // exp() → exponential function e^(value)
    // pow(a, 2) → squares a value
    // The closer x is to mean, the higher the membership value (closer to 1)
    return exp(-0.5 * pow((x - mean) / sigma, 2));
}

int main() {
    // Create an output file named "gaussian_mean_5.txt" to save results
    ofstream fout("gaussian_mean_5.txt");

    // Fixed input (x) and spread (sigma)
    double x = 5, sigma = 2;   

    /*
       Loop changes the "mean" value from -2 to 12 in steps of 0.5
       For each mean, we calculate how much x = 5 belongs 
       to the Gaussian curve centered at that mean.
    */
    for (double mean = -2; mean <= 12; mean += 0.5) {
        // Write x and corresponding membership value to file
        fout << x << " " << gaussian(x, mean, sigma) << endl;
    }

    // Close file after writing all values
    fout.close();
    return 0;
}

/*
--------------------------------------------
🧠 EASY EXPLANATION:
--------------------------------------------
This code studies how the Gaussian membership function changes 
when the **mean (center)** of the curve changes, 
while keeping **sigma (spread)** fixed at 2.

💡 Here:
   - x = 5 (the point we’re testing)
   - sigma = 2 (the width of the curve)
   - mean varies from -2 to 12

The Gaussian function gives higher membership values 
when x is close to the mean and lower values when it’s far away.

👉 So, as the mean moves from -2 to 12, 
   the peak of the Gaussian curve “slides” across the x-axis,
   and we see how the membership of x = 5 changes for each mean.

--------------------------------------------
📘 FORMULA:
--------------------------------------------
μ(x) = exp( -0.5 * ((x - mean) / sigma)² )

--------------------------------------------
📋 PSEUDOCODE:
--------------------------------------------
Start
  Define gaussian(x, mean, sigma):
       return exp(-0.5 * ((x - mean)/sigma)^2)

  Open file "gaussian_mean_5.txt"
  Set x = 5
  Set sigma = 2

  For mean = -2 to 12 step 0.5:
       membership = gaussian(x, mean, sigma)
       Write x and membership to file

  Close file
End
--------------------------------------------
*/ 
