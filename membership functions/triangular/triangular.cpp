#include <iostream>
#include <fstream>
using namespace std;

double triangular(double x, double a, double b, double c) {
    if (x <= a || x >= c) return 0.0;
    else if (x == b) return 1.0;
    else if (x > a && x < b) return (x - a) / (b - a);
    else return (c - x) / (c - b);
}

int main() {
    ofstream fout("triangular_c_12.txt");
    double a = 0, b = 5, c = 12;   
    for (double x = -2; x <= 12; x += 0.5) {
        fout << x << " " << triangular(x, a, b, c) << endl;
    }
    fout.close();
    return 0;
}
