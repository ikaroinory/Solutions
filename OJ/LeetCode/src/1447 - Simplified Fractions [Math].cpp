class Solution {
public:
    int gcd(int x, int y) {
        return y ? gcd(y, x % y) : x;
    }
    vector<string> simplifiedFractions(int n) {
        vector<string> list;
        for (int i = 2; i <= n; i++)
            for (int j = 1; j < i; j++)
                if (j == 1 || gcd(i, j) == 1) list.emplace_back(to_string(j) + "/" + to_string(i));

        return list;
    }
};
