#include <iostream>

using namespace std;

int list[1000 + 9];

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int temp;
        cin >> temp;
        cout << ++list[temp] << " ";
    }
    cout << endl;
    return 0;
}
