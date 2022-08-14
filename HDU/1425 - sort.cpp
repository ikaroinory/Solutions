#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int list[1000000 + 9];

int main() {
    int n, m;
    while (scanf("%d%d", &n, &m) != EOF) {
        memset(list, 0, sizeof(list));
        for (int i = 0; i < n; i++) scanf("%d", &list[i]);

        sort(list, list + n, [](int a, int b) { return a > b; });

        for (int i = 0; i < m; i++) {
            if (i) putchar(' ');
            printf("%d", list[i]);
        }
        putchar('\n');
    }
    return 0;
}
