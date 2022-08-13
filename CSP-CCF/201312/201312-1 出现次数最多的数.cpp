#include <iostream>
#include <algorithm>

using namespace std;

int list[10000 + 9];

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int temp;
        cin >> temp;
        list[temp]++;
    }

    cout << max_element(list, list + 10000 + 9) - list << endl;
    return 0;
}
