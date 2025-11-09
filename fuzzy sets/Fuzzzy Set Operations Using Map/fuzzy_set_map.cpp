#include <iostream>
#include <map>
#include <cmath>
using namespace std;

// -------------------- MEMBERSHIP FUNCTION 1 --------------------
// This function gives how much a person belongs to the "Tall" group.
float MemberShipFunction1(float X)
{
    if (X <= 160)
    {
        return 0;   // Below 160 → not tall
    }
    else if (X > 160 && X < 190)
    {
        return ((X - 160) / 30.0); // between 160–190 → partly tall (gradually increases)
    }
    else
    {
        return 1;   // Above 190 → fully tall
    }
}

// -------------------- MEMBERSHIP FUNCTION 2 --------------------
// Another function (for example “Very Tall”) using an exponential formula
// It grows or decreases smoothly (not sharply like linear).
double MembershipFunction2(float X)
{
    float c = 175; // center point of curve
    float k = -0.1; // controls steepness
    double exponent = k * (X - c);
    return 1.0 / pow(2.71828, exponent); // exponential equation → gives smooth curve
}

int main()
{
    // -------------------- SAMPLE HEIGHTS --------------------
    // Two fuzzy sets with different elements (heights)
    float height1[] = {150, 160, 165, 170, 175, 180};
    float height2[] = {155, 160, 170, 175, 185, 190};

    // -------------------- MAPS FOR FUZZY SETS --------------------
    // map<height, membership_value>
    // Map automatically stores unique heights in sorted order
    map<float, double> set1;     // for function 1
    map<float, double> set2;     // for function 2
    map<float, double> finalSet; // to store final union result

    // -------------------- STEP 1: FILL FIRST SET --------------------
    for (float h : height1)
    {
        set1[h] = MemberShipFunction1(h); // store height and its membership
    }

    // -------------------- STEP 2: FILL SECOND SET --------------------
    for (float h : height2)
    {
        set2[h] = MembershipFunction2(h); // store height and its membership
    }

    // -------------------- STEP 3: UNION OPERATION --------------------
    // For fuzzy union: take MAX of membership values for same height.
    for (auto &p : set1)
    {
        float h = p.first;   // height
        double v1 = p.second; // membership in set1

        // If height is also in set2 → take its value
        // else if not present → take 0
        double v2 = (set2.find(h) != set2.end()) ? set2[h] : 0;

        // Union → take larger (max) membership value
        finalSet[h] = max(v1, v2);
    }

    // -------------------- STEP 4: ADD REMAINING HEIGHTS FROM SET2 --------------------
    // Some heights exist only in set2 (not in set1)
    for (auto &p : set2)
    {
        float h = p.first;
        // If not already added to finalSet, add it now
        if (finalSet.find(h) == finalSet.end())
        {
            finalSet[h] = p.second;
        }
    }

    // -------------------- STEP 5: PRINT FINAL RESULT --------------------
    cout << "Height -> Final Membership" << endl;
    for (auto &p : finalSet)
    {
        cout << p.first << " -> " << p.second << endl;
    }

    return 0;
}
