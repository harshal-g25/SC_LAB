#include <iostream>   // To use input-output like cout or cin
#include <fstream>    // To write output to a text file
#include <cmath>      // For math functions like exp() and pow()
using namespace std;  // To avoid writing std:: again and again

/*
----------------------------------------------------
🌸 GAUSSIAN MEMBERSHIP FUNCTION EXPLANATION
----------------------------------------------------

A Gaussian (normal) membership function creates a smooth, bell-shaped curve 
that defines how strongly an input (x) belongs to a fuzzy set.

For example:
   - In a fuzzy logic system for “Temperature”,
     you might define a Gaussian set for “Warm” centered around mean = 25°C.

Formula:
   μ(x) = exp( -0.5 * ((x - mean) / sigma)² )

where:
   - μ(x): the membership value (between 0 and 1)
   - x: the input value
   - mean: the center or peak of the bell curve
   - sigma: the spread (how wide or narrow the curve is)
----------------------------------------------------
*/

double gaussian(double x, double mean, double sigma) {
    // ((x - mean) / sigma) → measures how far x is from mean in units of sigma
    // pow(..., 2) → squares that difference
    // exp(-0.5 * (...)) → creates the bell curve using exponential function
    // Result is between 0 and 1 (like fuzzy membership)
    return exp(-0.5 * pow((x - mean) / sigma, 2));
}

int main() {
    // Open a file to store the output results
    ofstream fout("gaussian_mean_5.txt");

    // Fixing one x value (x = 5)
    // and one sigma value (spread = 2)
    double x = 5, sigma = 2;

    /*
       We will vary "mean" (the center of the curve)
       from -2 to 12 in steps of 0.5
       For each mean, we calculate the membership of x = 5
       and write it into a file.
    */
    for (double mean = -2; mean <= 12; mean += 0.5) {
        fout << x << " " << gaussian(x, mean, sigma) << endl;
    }

    // Close the file after writing all data
    fout.close();
    return 0;
}

/*
----------------------------------------------------
🧠 SIMPLE EXPLANATION:
----------------------------------------------------
- We’re checking how “belongingness” of x = 5 changes 
  as the mean (center of Gaussian curve) moves.

- When mean = 5 → membership is highest (μ ≈ 1)
- When mean is far from 5 → membership drops (μ ≈ 0)

Basically:
  the closer x is to the mean, the higher its membership value.

----------------------------------------------------
📈 WHAT HAPPENS:
----------------------------------------------------
As mean changes from -2 → 12:
   - The Gaussian peak slides along the axis.
   - For each position, the code measures 
     how much x = 5 belongs to that curve.
   - All results are saved to "gaussian_mean_5.txt".

----------------------------------------------------
📋 PSEUDOCODE:
----------------------------------------------------
Start
   Define function gaussian(x, mean, sigma):
        return exp(-0.5 * ((x - mean) / sigma)^2)

   Open file “gaussian_mean_5.txt”
   Set x = 5
   Set sigma = 2

   For mean = -2 to 12 step 0.5:
       Calculate membership = gaussian(x, mean, sigma)
       Write (x, membership) to file

   Close file
End
----------------------------------------------------
*/
