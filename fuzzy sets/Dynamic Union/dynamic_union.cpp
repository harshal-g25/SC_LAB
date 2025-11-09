#include <iostream>
#include <cmath>
using namespace std;

// -------------------- MEMBERSHIP FUNCTION 1 --------------------
// This function gives how much a person belongs to the "Tall" group based on height.
float MemberShipFunction1(float X)
{
    if (X <= 160)
    {
        return 0;   // Height 160 or below → not tall at all (0)
    }
    else if (X > 160 && X < 190)
    {
        // Between 160 and 190 → partially tall (increases gradually)
        // Example: X=175 → (175-160)/30 = 0.5
        return ((X - 160) / 30);
    }
    else
    {
        return 1;   // Above 190 → fully tall (1)
    }

    return -1; // extra return (never used)
}

// -------------------- MEMBERSHIP FUNCTION 2 --------------------
// Another function (for example: “Very Tall”) using an exponential curve.
// Here we use double because exponential values can be very small or large,
// and double gives more precision than float (more accurate for math).
double MembershipFunction2(float X)
{
    float c = 175; // center point of the curve
    float k = -0.1; // controls how fast curve goes up or down
    float e = 2.71828; // 'e' (Euler's number) is the base of natural log

    // base = e (2.71828)
    // exponent = -0.1 * (X - 175)
    double base = e;
    double exponent = k * (X - c);

    // pow(base, exponent) = e^(exponent)
    // Here we take 1 / (e^(exponent))
    double final = 1 / pow(base, exponent);

    return final; // return the exponential membership value
}

int main()
{
    // -------------------- HEIGHT VALUES --------------------
    // These are height samples for which we’ll calculate membership.
    float height1[] = {150, 160, 165, 170, 175, 180, 185, 190, 195, 200};
    float height2[] = {150, 160, 165, 170, 175, 180, 185, 190, 195, 200};

    float final[100][100]; // array to store results (height + final value)

    // -------------------- FIND UNION --------------------
    for (int i = 0; i < 10; i++)
    {
        // Take both membership values for same height
        double first = MemberShipFunction1(height1[i]);   // from function 1
        double second = MembershipFunction2(height2[i]);  // from function 2
        double final_v;

        // Union in fuzzy logic = MAX value of both memberships
        // So whichever is larger, we take that.
        if (first >= second)
        {
            final_v = first;
        }
        else
        {
            final_v = second;
        }

        // Store height and final (union) membership
        final[i][0] = height1[i];
        final[i][1] = final_v;
    }

    // -------------------- PRINT RESULT --------------------
    // Show height and union membership for each
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cout << final[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
