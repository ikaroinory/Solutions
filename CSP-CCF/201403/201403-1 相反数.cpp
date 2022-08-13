#include <iostream>

using namespace std;

int positiveList[1000 + 9];
int negativeList[1000 + 9];

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int temp;
        cin >> temp;
        if (temp == 0) continue;
        if (temp > 0) positiveList[temp]++;
        else negativeList[-temp]++;
    }

    int ans = 0;
    for (int i = 1; i < 1000 + 9; i++)
        if (positiveList[i] && positiveList[i] == negativeList[i]) ans++;
    cout << ans << endl;
    return 0;
}
