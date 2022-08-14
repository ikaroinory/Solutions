#include <iostream>
#include <cmath>

using namespace std;

int a[1000 + 9];

int main() {
    int n;
    cin >> n;
    double avg = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        avg += a[i];
    }
    avg /= n;
    double var = 0;
    for (int i = 0; i < n; i++) {
        var += (avg - a[i]) * (avg - a[i]);
    }
    var /= n;

    for (int i = 0; i < n; i++)
        cout << (a[i] - avg) / sqrt(var) << endl;

    return 0;
}
