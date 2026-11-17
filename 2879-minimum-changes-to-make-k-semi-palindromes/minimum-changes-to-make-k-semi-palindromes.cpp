class Solution {
public:
    int minimumChanges(string s, int k) {
        int n = s.size();
        const int INF = 1e9;

        // cost[i][j]: min changes to make s[i..j] a semi-palindrome
        vector<vector<int>> cost(n, vector<int>(n, INF));
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int len = j - i + 1;
                int best = INF;
                for (int d = 1; d < len; d++) {
                    if (len % d != 0) continue;
                    int m = len / d;          // elements per group
                    int changes = 0;
                    for (int r = 0; r < d; r++) {
                        for (int a = 0; a < m / 2; a++) {
                            int x = i + r + a * d;
                            int y = i + r + (m - 1 - a) * d;
                            if (s[x] != s[y]) changes++;
                        }
                    }
                    best = min(best, changes);
                }
                cost[i][j] = best;
            }
        }

        // dp[p][i]: min cost to split first i chars into p parts
        vector<vector<int>> dp(k + 1, vector<int>(n + 1, INF));
        dp[0][0] = 0;
        for (int p = 1; p <= k; p++) {
            for (int i = 2 * p; i <= n; i++) {
                for (int j = 2 * (p - 1); j <= i - 2; j++) {
                    if (dp[p - 1][j] == INF || cost[j][i - 1] == INF) continue;
                    dp[p][i] = min(dp[p][i], dp[p - 1][j] + cost[j][i - 1]);
                }
            }
        }
        return dp[k][n];
    }
};