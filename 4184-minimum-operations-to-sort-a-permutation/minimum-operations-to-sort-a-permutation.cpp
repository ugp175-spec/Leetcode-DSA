class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int p = 0;
        bool inc = true, dec = true;

        for (int i = 0; i < n; i++) {
            if (nums[i] == 0) p = i;
            int nx = nums[(i + 1) % n];
            if (nx != (nums[i] + 1) % n)     inc = false;
            if (nx != (nums[i] - 1 + n) % n) dec = false;
        }

        int ans = INT_MAX;
        if (inc) ans = min(ans, min(p, n - p + 2));
        if (dec) ans = min(ans, min(n - p, p + 2));
        return ans == INT_MAX ? -1 : ans;
    }
};