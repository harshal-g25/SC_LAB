#include <iostream>
#include <cmath>
using namespace std;

// ------------------ MEMBERSHIP FUNCTION 1 ------------------
// This function gives how much a value (height) belongs to Set 1.
// Example: represents "Tall" people
float MemberShipFunction1(float X)
{
    if (X <= 160)
    {
        return 0;   // If height ≤ 160 → not tall
    }
    else if (X > 160 && X < 190)
    {
        return ((X - 160) / 30.0);  // Between 160–190 → partly tall (increases linearly)
    }
    else
    {
        return 1;   // If height ≥ 190 → fully tall
    }
}

// ------------------ MEMBERSHIP FUNCTION 2 ------------------
// Another fuzzy function (for example “Very Tall”).
// Uses exponential formula → smooth curve, not straight line.
double MembershipFunction2(float X)
{
    float c = 175;  // center or midpoint
    float k = -0.1; // slope or rate of change
    double exponent = k * (X - c);
    // e = 2.71828 (base of natural log)
    return 1.0 / pow(2.71828, exponent); // gives gradual growth/decay pattern
}

int main()
{
    // ------------------ INPUT HEIGHTS FOR TWO SETS ------------------
    float height1[] = {150, 160, 165, 170, 175, 180}; // Set 1 elements
    float height2[] = {155, 160, 170, 175, 185, 190}; // Set 2 elements

    int n1 = sizeof(height1) / sizeof(height1[0]); // total elements in set 1
    int n2 = sizeof(height2) / sizeof(height2[0]); // total elements in set 2

    float final[100][2]; // to store final set → column 0 = height, column 1 = membership value
    int index = 0;       // to keep track of filled rows in 'final'

    // ------------------ STEP 1: PROCESS ALL ELEMENTS FROM SET 1 ------------------
    for (int i = 0; i < n1; i++)
    {
        float h = height1[i];             // current height from set 1
        double mf1 = MemberShipFunction1(h); // its membership value in set 1

        double mf2 = 0; // assume 0 → if height not in set 2
        for (int j = 0; j < n2; j++)
        {
            if (height2[j] == h) // if same height found in set 2
            {
                mf2 = MembershipFunction2(height2[j]); // take its membership value
                break;
            }
        }

        // Union = maximum membership from both sets
        final[index][0] = h;             // height
        final[index][1] = max(mf1, mf2); // membership value (max of both)
        index++;                         // move to next position in 'final'
    }

    // ------------------ STEP 2: ADD ELEMENTS THAT EXIST ONLY IN SET 2 ------------------
    for (int j = 0; j < n2; j++)
    {
        float h = height2[j];
        bool found = false;

        // check if height from set2 already in set1
        for (int i = 0; i < n1; i++)
        {
            if (height1[i] == h)
            {
                found = true; // already added → skip it
                break;
            }
        }

        // if not found → directly add it to final
        if (!found)
        {
            double mf2 = MembershipFunction2(h); // membership from set2
            final[index][0] = h;  // height
            final[index][1] = mf2; // membership
            index++;
        }
    }

    // ------------------ STEP 3: PRINT FINAL UNION SET ------------------
    cout << "Height -> Final Membership" << endl;
    for (int i = 0; i < index; i++)
    {
        cout << final[i][0] << " -> " << final[i][1] << endl; // display result
    }

    return 0;
}
//Two fuzzy sets are represented by two height arrays.

//Each height has a membership value (how strongly it belongs).

//Union (A ∪ B) = take the maximum membership value for each height.

//If one set doesn’t have that height, we assume its membership is 0.

//The result shows combined membership for both sets.