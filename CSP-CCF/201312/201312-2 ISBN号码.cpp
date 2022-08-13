#include <iostream>

using namespace std;

int main() {
    string s;
    cin >> s;

    int w = 1;
    int sum = 0;
    for (int i = 0; i < 11; i++) {
        if (s[i] == '-') continue;
        sum += w++ * (s[i] - '0');
    }
    sum %= 11;

    int c = 'X';
    if (sum < 10) c = '0' + sum;

    if (c == s.back()) cout << "Right" << endl;
    else {
        s.back() = c;
        cout << s << endl;
    }
    return 0;
}
