#include <bitset>
#include <vector>
using namespace std;

class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        const int K = 1024;

        vector<bitset<K>> dp(n);

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int v = grid[i][j];
                bitset<K> src;

                if (i == 0 && j == 0) {
                    src[0] = 1;
                } else {
                    if (i > 0) src |= dp[j];
                    if (j > 0) src |= dp[j - 1];
                }

                bitset<K> cur;
                for (int x = 0; x < K; x++) {
                    if (src[x]) cur[x ^ v] = 1;
                }
                dp[j] = cur;
            }
        }

        for (int x = 0; x < K; x++) {
            if (dp[n - 1][x]) return x;
        }
        return -1;
    }
};