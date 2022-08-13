#include <iostream>
#include <algorithm>

using namespace std;

int list[1000 + 9];

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> list[i];

    int ans = 0;
    sort(list, list + n);
    for (int i = 0; i < n - 1; i++)
        if (list[i + 1] - list[i] == 1) ans++;

    cout << ans << endl;
    return 0;
}
