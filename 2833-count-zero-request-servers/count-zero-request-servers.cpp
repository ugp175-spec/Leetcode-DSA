class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
        // sort logs by time
        sort(logs.begin(), logs.end(), [](const auto& a, const auto& b) {
            return a[1] < b[1];
        });

        // sort queries with original indices
        int m = queries.size();
        vector<pair<int,int>> qs(m);
        for (int i = 0; i < m; i++) qs[i] = {queries[i], i};
        sort(qs.begin(), qs.end());

        vector<int> cnt(n + 1, 0);
        int active = 0;
        int L = 0, R = 0; // window is logs[L..R-1]
        int sz = logs.size();
        vector<int> ans(m);

        for (auto& [q, idx] : qs) {
            // add logs with time <= q
            while (R < sz && logs[R][1] <= q) {
                if (cnt[logs[R][0]]++ == 0) active++;
                R++;
            }
            // remove logs with time < q - x
            while (L < R && logs[L][1] < q - x) {
                if (--cnt[logs[L][0]] == 0) active--;
                L++;
            }
            ans[idx] = n - active;
        }
        return ans;
    }
};