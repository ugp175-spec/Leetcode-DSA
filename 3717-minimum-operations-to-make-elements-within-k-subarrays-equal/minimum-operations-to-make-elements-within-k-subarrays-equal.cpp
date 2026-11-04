class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();

        // coordinate compression
        vector<int> vals(nums.begin(), nums.end());
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        int m = vals.size();

        auto idx = [&](int v) {
            return int(lower_bound(vals.begin(), vals.end(), v) - vals.begin()) + 1;
        };

        // Fenwick trees: count and sum
        vector<long long> cnt(m + 1, 0), sm(m + 1, 0);

        auto upd = [&](int i, long long c, long long s) {
            for (; i <= m; i += i & -i) {
                cnt[i] += c;
                sm[i] += s;
            }
        };

        int LOG = 1;
        while ((LOG << 1) <= m) LOG <<= 1;

        // smallest position whose prefix count >= kk
        auto kth = [&](long long kk) {
            int pos = 0;
            for (int b = LOG; b > 0; b >>= 1) {
                if (pos + b <= m && cnt[pos + b] < kk) {
                    pos += b;
                    kk -= cnt[pos];
                }
            }
            return pos + 1;
        };

        auto query = [&](int i) {
            long long c = 0, s = 0;
            for (; i > 0; i -= i & -i) {
                c += cnt[i];
                s += sm[i];
            }
            return make_pair(c, s);
        };

        // cost of every window of length x
        vector<long long> cost(n - x + 1, 0);
        long long total = 0;
        for (int i = 0; i < n; i++) {
            upd(idx(nums[i]), 1, nums[i]);
            total += nums[i];
            if (i >= x) {
                upd(idx(nums[i - x]), -1, -nums[i - x]);
                total -= nums[i - x];
            }
            if (i >= x - 1) {
                int pos = kth((x + 1) / 2);
                long long med = vals[pos - 1];
                auto [cl, sl] = query(pos);
                cost[i - x + 1] = med * cl - sl + (total - sl) - med * (x - cl);
            }
        }

        // DP over number of chosen windows
        const long long INF = LLONG_MAX / 4;
        vector<long long> prev(n + 1, 0), cur(n + 1, INF);
        for (int j = 1; j <= k; j++) {
            fill(cur.begin(), cur.end(), INF);
            for (int i = j * x; i <= n; i++) {
                cur[i] = min(cur[i - 1], prev[i - x] + cost[i - x]);
            }
            swap(prev, cur);
        }
        return prev[n];
    }
};