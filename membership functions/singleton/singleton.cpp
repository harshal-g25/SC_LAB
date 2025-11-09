#include <iostream>
#include <fstream>
using namespace std;


double singleton(double x, double a) {
    return (x == a) ? 1.0 : 0.0;
}

int main() {
    ofstream fout("singleton.txt");
    double a = 5;   
    for (double x = -2; x <= 12; x += 0.5) {
        fout << x << " " << singleton(x, a) << endl;
    }
    fout.close();
    return 0;
}
