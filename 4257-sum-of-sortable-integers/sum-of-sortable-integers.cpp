class Solution {
public:
    long long sortableIntegers(vector<int>& nums) {

        int n = nums.size();
         
        long long ans = 0;
         
        for (int k = 1; k <= n; k++) { 

            if (n % k) continue;

            bool ok = true;
            int prevMax = 0;

            for (int s = 0; s < n && ok; s += k) {

                int desc = 0, pos = -1;
                for (int i = s; i < s + k - 1; i++) {
                    if (nums[i] > nums[i + 1]) {
                        desc++;
                        pos = i;
                    }
                }
                int lo, hi;

                if (desc == 0) {
                    lo = nums[s];
                    hi = nums[s + k - 1];

                } 
                else if (desc == 1 && nums[s + k - 1] <= nums[s]) {
                    lo = nums[pos + 1];
                    hi = nums[pos];
                } 
                else {
                    ok = false;
                    break;
                }
                if (lo < prevMax) {
                    ok = false;
                    break;
                }
                prevMax = hi;
            }
            if (ok) ans += k;
        }
        return ans;
    }
};