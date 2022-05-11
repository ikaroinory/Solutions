#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

struct Function {
    static int htod(string s) {
        int ans = 0;
        for (char c : s) {
            ans *= 16;
            if (c >= '0' && c <= '9') ans += c - '0';
            else ans += c - 'a' + 10;
        }
        return ans;
    }
    static string htos(int hex) {
        deque<char> list;
        while (hex) {
            if (hex % 16 < 10) list.push_front((hex % 16) + '0');
            else list.push_front((hex % 16) - 10 + 'a');
            hex /= 16;
        }
        while (list.size() < 2) list.push_front('0');
        return string(list.begin(), list.end());
    }
};

class RC4 {
private:
    const int N = 256;

    vector<int> msgList;
    vector<int> keyList;
    vector<int> S;
    vector<int> T;

    void KSA() {
        int j = 0;
        for (int i = 0; i < N; i++) {
            j = (j + S[i] + T[i]) % N;
            swap(S[i], S[j]);
        }
    }
    void PRGA() {
        int i = 0;
        int j = 0;
        int msgLen = msgList.size();
        for (int r = 0; r < msgLen; r++) {
            i = (i + 1) % N;
            j = (j + S[i]) % N;
            swap(S[i], S[j]);
            int t = (S[i] + S[j]) % N;
            keyList[r] = S[t];
        }
    }
public:
    string msg;
    string key;

    RC4(string msg, string key) : msg(msg), key(key) {
        int msgLen = msg.length();
        for (int i = 0; i < msgLen; i += 2)
            msgList.push_back(Function::htod(msg.substr(i, 2)));
        keyList = vector<int>(msg.length());
        int keyLen = key.length();
        for (int i = 0; i < N; i++) {
            S.push_back(i);
            T.push_back(Function::htod(key.substr(2 * i % keyLen, 2)));
        }
    }

    string encryption() {
        KSA();
        PRGA();

        string ans = "";
        int msgLen = msgList.size();
        for (int i = 0; i < msgLen; i++)
            ans += Function::htos(msgList[i] ^ keyList[i]);
        return ans;
    }
    string decryption() {
        return encryption();
    }
};
