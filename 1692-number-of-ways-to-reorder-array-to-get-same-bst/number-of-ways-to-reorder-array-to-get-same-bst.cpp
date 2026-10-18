class Solution {
    static constexpr long long MOD = 1'000'000'007;
    vector<long long> fact, inv;

    long long power(long long b, long long e) {
        long long r = 1;
        b %= MOD;
        while (e > 0) {
            if (e & 1) r = r * b % MOD;
            b = b * b % MOD;
            e >>= 1;
        }
        return r;
    }

    long long comb(int a, int b) {
        return fact[a] * inv[b] % MOD * inv[a - b] % MOD;
    }

    long long ways(const vector<int>& arr) {
        if (arr.size() <= 2) return 1;
        int root = arr[0];
        vector<int> left, right;
        for (int i = 1; i < (int)arr.size(); i++) {
            if (arr[i] < root) left.push_back(arr[i]);
            else right.push_back(arr[i]);
        }
        long long res = comb(left.size() + right.size(), left.size());
        res = res * ways(left) % MOD;
        res = res * ways(right) % MOD;
        return res;
    }

public:
    int numOfWays(vector<int>& nums) {
        int n = nums.size();
        fact.assign(n + 1, 1);
        inv.assign(n + 1, 1);
        for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i % MOD;
        inv[n] = power(fact[n], MOD - 2);
        for (int i = n; i >= 1; i--) inv[i - 1] = inv[i] * i % MOD;

        return (ways(nums) - 1 + MOD) % MOD;
    }
};