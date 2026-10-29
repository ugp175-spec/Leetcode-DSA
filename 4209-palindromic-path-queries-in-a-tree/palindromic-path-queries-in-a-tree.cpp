class Solution {
    int n, LOG, timer = 0;
    vector<int> bit, tin, tout, dep;
    vector<vector<int>> up;

    void upd(int i, int v) {            // point xor at position i
        for (i++; i <= n + 1; i += i & -i) bit[i] ^= v;
    }
    int qry(int i) {                    // prefix xor up to position i
        int r = 0;
        for (i++; i > 0; i -= i & -i) r ^= bit[i];
        return r;
    }
    void rangeXor(int l, int r, int v) { // xor v over [l, r]
        upd(l, v);
        upd(r + 1, v);
    }
    int lca(int a, int b) {
        if (dep[a] < dep[b]) swap(a, b);
        int diff = dep[a] - dep[b];
        for (int k = 0; k < LOG; k++)
            if (diff >> k & 1) a = up[k][a];
        if (a == b) return a;
        for (int k = LOG - 1; k >= 0; k--)
            if (up[k][a] != up[k][b]) {
                a = up[k][a];
                b = up[k][b];
            }
        return up[0][a];
    }

public:
    vector<bool> palindromePath(int n_, vector<vector<int>>& edges, string s,
                                vector<string>& queries) {
        n = n_;
        LOG = 1;
        while ((1 << LOG) < n) LOG++;

        vector<vector<int>> g(n);
        for (auto& e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }

        bit.assign(n + 2, 0);
        tin.assign(n, 0);
        tout.assign(n, 0);
        dep.assign(n, 0);
        up.assign(LOG, vector<int>(n, 0));

        // iterative DFS from root 0
        vector<pair<int, int>> st;
        st.push_back({0, 0});
        up[0][0] = 0;
        tin[0] = timer++;
        while (!st.empty()) {
            auto& [u, idx] = st.back();
            if (idx < (int)g[u].size()) {
                int v = g[u][idx++];
                if (v == up[0][u] && u != 0) continue;
                if (u == 0 && v == 0) continue;
                up[0][v] = u;
                dep[v] = dep[u] + 1;
                tin[v] = timer++;
                st.push_back({v, 0});
            } else {
                tout[u] = timer - 1;
                st.pop_back();
            }
        }
        for (int k = 1; k < LOG; k++)
            for (int i = 0; i < n; i++)
                up[k][i] = up[k - 1][up[k - 1][i]];

        // initial prefix-xor values: node x contributes its mask to its subtree
        for (int i = 0; i < n; i++)
            rangeXor(tin[i], tout[i], 1 << (s[i] - 'a'));

        vector<bool> ans;
        for (auto& q : queries) {
            istringstream ss(q);
            string type;
            ss >> type;
            if (type == "update") {
                int u;
                char c;
                ss >> u >> c;
                int delta = (1 << (s[u] - 'a')) ^ (1 << (c - 'a'));
                if (delta) {
                    rangeXor(tin[u], tout[u], delta);
                    s[u] = c;
                }
            } else {
                int u, v;
                ss >> u >> v;
                int l = lca(u, v);
                int x = qry(tin[u]) ^ qry(tin[v]) ^ (1 << (s[l] - 'a'));
                ans.push_back((x & (x - 1)) == 0);   // popcount <= 1
            }
        }
        return ans;
    }
};