#include <iostream>   // For input-output operations (like cout, cin)
#include <fstream>    // For file handling (writing data into a file)
#include <cmath>      // For mathematical functions like exp(), pow()
using namespace std;  // Allows direct use of standard C++ library functions without std::

/*  
   🔹 gaussian() function:
   - This function defines the Gaussian (bell-shaped) membership function 
     commonly used in fuzzy logic.
   - It returns a value between 0 and 1, representing how much x belongs 
     to a fuzzy set (like “medium temperature” or “high speed”).
*/
double gaussian(double x, double mean, double sigma) {
    // Formula: exp(-0.5 * ((x - mean) / sigma)^2)
    // exp() = exponential function e^(value)
    // pow(a, 2) = a squared
    // mean = center of the curve
    // sigma = standard deviation (controls the width of the curve)
    return exp(-0.5 * pow((x - mean) / sigma, 2));
}

int main() {
    // Create a file named "gaussian_sigma_6.txt" to store results
    ofstream fout("gaussian_sigma_6.txt");

    // Fixed values of x (input variable) and mean (center of Gaussian curve)
    double x = 6, mean = 2;   

    /*
       Loop through different sigma values (spread/width of the curve)
       - Starts from sigma = -2 up to 12
       - Increases by 0.5 each time
       - For each sigma value, we calculate the Gaussian membership
         of x = 6 for that sigma.
    */
    for (double sigma = -2; sigma <= 12; sigma += 0.5) {
        // Write (x, membership_value) into the file
        fout << x << " " << gaussian(x, mean, sigma) << endl;
    }

    // Close the file after writing all values
    fout.close();
    return 0;
}

/*
--------------------------------------------
🧠 EASY EXPLANATION:
--------------------------------------------
The code shows how the Gaussian (bell curve) changes 
for different "sigma" (width/spread) values.

💡 Mean (μ) = 2 → center of the curve  
💡 Sigma (σ) = spread → controls how flat or narrow the curve is  
💡 x = 6 → point where membership value is calculated  

As σ increases → curve becomes wider → membership value decreases slowly  
As σ decreases → curve becomes sharper → membership value drops quickly  

--------------------------------------------
📘 FORMULA:
--------------------------------------------
Gaussian Membership Function:
μ(x) = exp( -0.5 * ((x - mean) / sigma)^2 )

--------------------------------------------
📋 PSEUDOCODE:
--------------------------------------------
Start
  Define gaussian(x, mean, sigma):
      return exp(-0.5 * ((x - mean)/sigma)^2)

  Open file "gaussian_sigma_6.txt"
  Set x = 6
  Set mean = 2

  For sigma = -2 to 12 step 0.5:
      Calculate membership = gaussian(x, mean, sigma)
      Write x and membership to file

  Close file
End
--------------------------------------------
*/
