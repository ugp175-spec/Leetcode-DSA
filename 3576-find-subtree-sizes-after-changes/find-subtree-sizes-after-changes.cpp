class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();
        vector<vector<int>> children(n);
        for (int i = 1; i < n; i++) children[parent[i]].push_back(i);

        vector<int> ans(n, 1);
        int last[26];
        fill(last, last + 26, -1);

        function<void(int)> dfs = [&](int x) {
            int c = s[x] - 'a';
            int prev = last[c];      // closest ancestor with same char
            last[c] = x;
            for (int y : children[x]) dfs(y);
            last[c] = prev;          // backtrack

            if (x != 0) {
                int target = (prev != -1) ? prev : parent[x];
                ans[target] += ans[x];
            }
        };

        dfs(0);
        return ans;
    }
};