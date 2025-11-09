#include <iostream>   // For input/output operations
#include <fstream>    // For writing results to a file
using namespace std;  // To avoid writing std:: before every command

/*
------------------------------------------------------------
🎯 TRIANGULAR MEMBERSHIP FUNCTION — EXPLANATION
------------------------------------------------------------
A **Triangular Membership Function** is a simple fuzzy function 
that looks like a **triangle** when plotted.

It increases linearly, reaches a peak (value = 1), 
and then decreases linearly.

It is defined by 3 points: a, b, c

          1.0 |          /\
               |         /  \
               |        /    \
          0.0 |_______/      \_______
                a     b        c

------------------------------------------------------------
FORMULA:
------------------------------------------------------------
μ(x) =  0                     , if x ≤ a or x ≥ c
        (x - a) / (b - a)     , if a < x < b  (rising slope)
        (c - x) / (c - b)     , if b < x < c  (falling slope)
        1                     , if x = b  (peak point)

where:
  - a = start of the triangle (left base)
  - b = peak (where membership = 1)
  - c = end of the triangle (right base)
------------------------------------------------------------
*/

double triangular(double x, double a, double b, double c) {
    // CASE 1: If x is outside the triangle range → membership = 0
    if (x <= a || x >= c) 
        return 0.0;

    // CASE 2: If x is exactly at the peak → membership = 1
    else if (x == b) 
        return 1.0;

    // CASE 3: If x lies between a and b → rising slope
    // membership increases linearly from 0 to 1
    else if (x > a && x < b) 
        return (x - a) / (b - a);

    // CASE 4: If x lies between b and c → falling slope
    // membership decreases linearly from 1 to 0
    else 
        return (c - x) / (c - b);
}

int main() {
    // Create an output file to save results
    ofstream fout("triangular_c_12.txt");

    // Define the triangle shape points
    double a = 0, b = 5, c = 12;   

    /*
       Loop through x values from -2 to 12 (step = 0.5)
       For each x, calculate its membership using triangular()
       and write it to the file.
    */
    for (double x = -2; x <= 12; x += 0.5) {
        fout << x << " " << triangular(x, a, b, c) << endl;
    }

    // Close the file after writing
    fout.close();
    return 0;
}

/*
------------------------------------------------------------
🧠 EASY UNDERSTANDING:
------------------------------------------------------------
This function shows how “belonging” of a value (x)
changes between 0 and 1 in the shape of a **triangle**.

Example:
   If we describe “medium temperature” as:
   - a = 0°C  (start)
   - b = 5°C  (peak of medium)
   - c = 12°C (end)

Then:
   - Below 0°C → not medium (μ = 0)
   - Between 0°C and 5°C → becoming medium (μ increases)
   - Exactly 5°C → perfectly medium (μ = 1)
   - Between 5°C and 12°C → becoming less medium (μ decreases)
   - Above 12°C → not medium (μ = 0)

------------------------------------------------------------
📈 OUTPUT (in triangular_c_12.txt):
------------------------------------------------------------
Each line in the file contains:
     x-value     μ(x)
Example:
    -2   0
     0   0
     2.5 0.5
     5   1
     8.5 0.5
    12   0
------------------------------------------------------------
📘 PSEUDOCODE:
------------------------------------------------------------
Start
   Define triangular(x, a, b, c)
        if (x ≤ a or x ≥ c) then μ = 0
        else if (x == b) then μ = 1
        else if (x > a and x < b) then μ = (x - a) / (b - a)
        else μ = (c - x) / (c - b)
        return μ

   Open file "triangular_c_12.txt"
   Set a = 0, b = 5, c = 12

   For x = -2 to 12 step 0.5:
        μ = triangular(x, a, b, c)
        Write (x, μ) to file

   Close file
End
------------------------------------------------------------
*/
