#include <iostream>
#include <vector>
#include <deque>

#define visit(v) v.begin(), v.end()

using namespace std;

struct Function {
private:
    static int TIMES(int v) {
        if (v >> 7)
            return ((v << 1) & 0xff) ^ 0x1b;
        else
            return (v << 1);
    }
    static int TIMES(int p, int v) {
        if (p == 0x04) return TIMES(TIMES(v));
        if (p == 0x08) return TIMES(TIMES(TIMES(v)));
        if (p == 0x09) return TIMES(8, v) ^ v;
        if (p == 0x0b) return TIMES(8, v) ^ TIMES(v) ^ v;
        if (p == 0x0d) return TIMES(8, v) ^ TIMES(4, v) ^ v;
        if (p == 0x0e) return TIMES(8, v) ^ TIMES(4, v) ^ TIMES(v);
        return v;
    }
    static vector<int> XOR(vector<int> obj, int rc) {
        obj[0] ^= rc;
        return obj;
    }
    static vector<int> XOR(vector<int> obj1, vector<int> obj2) {
        int size = obj1.size();
        for (int i = 0; i < size; i++)
            obj1[i] ^= obj2[i];
        return obj1;
    }

    static int htod(string s) {
        int ans = 0;
        for (char c : s) {
            ans *= 16;
            if (c >= '0' && c <= '9')
                ans += c - '0';
            else
                ans += c - 'a' + 10;
        }
        return ans;
    }
    static string htos(int hex) {
        deque<char> list;
        while (hex) {
            if (hex % 16 < 10)
                list.push_front((hex % 16) + '0');
            else
                list.push_front((hex % 16) - 10 + 'a');
            hex /= 16;
        }
        while (list.size() < 2)
            list.push_front('0');
        return string(list.begin(), list.end());
    }
};

class AES {
#pragma region ConstValue
    const int Nk = 4;
    const int SBox[16][16] = {
        0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
        0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
        0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
        0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
        0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
        0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
        0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
        0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
        0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
        0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
        0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
        0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
        0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
        0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
        0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
        0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
    };
    const int InvSBox[16][16] = {
        0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
        0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
        0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
        0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
        0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
        0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
        0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
        0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
        0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
        0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
        0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
        0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
        0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
        0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
        0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
        0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
    };
    const int RC[10] = {
        0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36
    };
#pragma endregion

#pragma region TemporaryValue
    vector<vector<int>> msgMatrix;
    vector<vector<int>> keyMatrix;
    vector<vector<int>> wMatrix;
#pragma endregion

#pragma region KeyGenerator
    vector<int> RotByte(vector<int> w) {
        deque<int> temp(visit(w));
        int front = temp.front();
        temp.pop_front();
        temp.push_back(front);
        return vector<int>(visit(temp));
    }
    vector<int> SubByte(vector<int> w) {
        for (int i = 0; i < Nk; i++) {
            int x = w[i] / 0x10;
            int y = w[i] % 0x10;
            w[i] = SBox[x][y];
        }
        return w;
    }
    void KeyExpansion() {
        for (int i = Nk; i < 44; i++) {
            vector<int> temp = wMatrix[i - 1];
            if (i % Nk == 0)
                temp = Function::XOR(SubByte(RotByte(temp)), RC[i / Nk - 1]);
            wMatrix.push_back(Function::XOR(wMatrix[i - Nk], temp));
        }
    }
#pragma endregion

#pragma region RoundFunction
    void ByteSub(vector<vector<int>>& state) {
        for (int i = 0; i < Nk; i++) {
            for (int j = 0; j < Nk; j++) {
                int x = state[i][j] / 16;
                int y = state[i][j] % 16;
                state[i][j] = SBox[x][y];
            }
        }
    }
    void ShiftRow(vector<vector<int>>& state) {
        for (int i = 1; i < Nk; i++) {
            deque<int> tempList(visit(state[i]));
            for (int j = 0; j < i; j++) {
                int front = tempList.front();
                tempList.pop_front();
                tempList.push_back(front);
            }
            state[i].assign(visit(tempList));
        }
    }
    void MixColumn(vector<vector<int>>& state) {
        vector<vector<int>> oldState(visit(state));
        for (int j = 0; j < 4; j++) {
            state[0][j] = Function::TIMES(oldState[0][j]) ^ Function::TIMES(oldState[1][j])
                ^ oldState[1][j] ^ oldState[2][j] ^ oldState[3][j];
            state[1][j] = oldState[0][j] ^ Function::TIMES(oldState[1][j])
                ^ Function::TIMES(oldState[2][j]) ^ oldState[2][j] ^ oldState[3][j];
            state[2][j] = oldState[0][j] ^ oldState[1][j]
                ^ Function::TIMES(oldState[2][j]) ^ Function::TIMES(oldState[3][j]) ^ oldState[3][j];
            state[3][j] = Function::TIMES(oldState[0][j]) ^ oldState[0][j]
                ^ oldState[1][j] ^ oldState[2][j] ^ Function::TIMES(oldState[3][j]);
        }
    }
    void AddRoundKey(vector<vector<int>>& state, vector<vector<int>> roundKey) {
        for (int i = 0; i < Nk; i++)
            for (int j = 0; j < Nk; j++)
                state[j][i] ^= roundKey[i][j];
    }

    void InvShiftRow(vector<vector<int>>& state) {
        for (int i = 1; i < Nk; i++) {
            deque<int> tempList(visit(state[i]));
            for (int j = 0; j < i; j++) {
                int back = tempList.back();
                tempList.pop_back();
                tempList.push_front(back);
            }
            state[i].assign(visit(tempList));
        }
    }
    void InvByteSub(vector<vector<int>>& state) {
        for (int i = 0; i < Nk; i++) {
            for (int j = 0; j < Nk; j++) {
                int x = state[i][j] / 16;
                int y = state[i][j] % 16;
                state[i][j] = InvSBox[x][y];
            }
        }
    }
    void InvMixColumn(vector<vector<int>>& state) {
        vector<vector<int>> oldState(visit(state));
        for (int j = 0; j < 4; j++) {
            state[0][j] = Function::TIMES(0x0e, oldState[0][j]) ^ Function::TIMES(0x0b, oldState[1][j])
                ^ Function::TIMES(0x0d, oldState[2][j]) ^ Function::TIMES(0x09, oldState[3][j]);
            state[1][j] = Function::TIMES(0x09, oldState[0][j]) ^ Function::TIMES(0x0e, oldState[1][j])
                ^ Function::TIMES(0x0b, oldState[2][j]) ^ Function::TIMES(0x0d, oldState[3][j]);
            state[2][j] = Function::TIMES(0x0d, oldState[0][j]) ^ Function::TIMES(0x09, oldState[1][j])
                ^ Function::TIMES(0x0e, oldState[2][j]) ^ Function::TIMES(0x0b, oldState[3][j]);
            state[3][j] = Function::TIMES(0x0b, oldState[0][j]) ^ Function::TIMES(0x0d, oldState[1][j])
                ^ Function::TIMES(0x09, oldState[2][j]) ^ Function::TIMES(0x0e, oldState[3][j]);
        }
    }

    void Round(vector<vector<int>>& state, vector<vector<int>> roundKey) {
        ByteSub(state);
        ShiftRow(state);
        MixColumn(state);
        AddRoundKey(state, roundKey);
    }
    void FinalRound(vector<vector<int>>& state, vector<vector<int>> roundKey) {
        ByteSub(state);
        ShiftRow(state);
        AddRoundKey(state, roundKey);
    }
    void InvRound(vector<vector<int>>& state, vector<vector<int>> roundKey) {
        InvShiftRow(state);
        InvByteSub(state);
        AddRoundKey(state, roundKey);
        InvMixColumn(state);
    }
    void InvFinalRound(vector<vector<int>>& state, vector<vector<int>> roundKey) {
        InvShiftRow(state);
        InvByteSub(state);
        AddRoundKey(state, roundKey);
    }
#pragma endregion

public:
    string msg;
    string key;

    AES(string msg, string key) : msg(msg), key(key) {
        msgMatrix = vector<vector<int>>(Nk);
        keyMatrix = vector<vector<int>>(Nk);
        for (int i = 0; i < Nk; i++) {
            vector<int> temp;
            for (int j = 0; j < Nk; j++) {
                int index = 8 * i + 2 * j;
                string s = msg.substr(index, 2);
                msgMatrix[j].push_back(Function::htod(msg.substr(index, 2)));
                keyMatrix[j].push_back(Function::htod(key.substr(index, 2)));
                temp.push_back(Function::htod(key.substr(index, 2)));
            }
            wMatrix.push_back(temp);
        }
        KeyExpansion();
    }

    string encryption() {
        AddRoundKey(msgMatrix, vector<vector<int>>(wMatrix.begin(), wMatrix.begin() + 4));
        for (int i = 1; i < 10; i++) Round(msgMatrix, vector<vector<int>>(wMatrix.begin() + i * Nk, wMatrix.begin() + i * Nk + 4));
        FinalRound(msgMatrix, vector<vector<int>>(wMatrix.begin() + 10 * Nk, wMatrix.begin() + 10 * Nk + 4));

        msg = "";
        for (int i = 0; i < Nk; i++)
            for (int j = 0; j < Nk; j++)
                msg += Function::htos(msgMatrix[j][i]);

        return msg;
    }
    string decryption() {
        AddRoundKey(msgMatrix, vector<vector<int>>(wMatrix.begin() + 40, wMatrix.begin() + 44));
        for (int i = 1; i < 10; i++)
            InvRound(msgMatrix, vector<vector<int>>(wMatrix.begin() + 40 - i * Nk, wMatrix.begin() + 44 - i * Nk));
        InvFinalRound(msgMatrix, vector<vector<int>>(wMatrix.begin(), wMatrix.begin() + 4));

        msg = "";
        for (int i = 0; i < Nk; i++)
            for (int j = 0; j < Nk; j++)
                msg += Function::htos(msgMatrix[j][i]);

        return msg;
    }
};
