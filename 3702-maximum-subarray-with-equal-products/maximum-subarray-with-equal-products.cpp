class Solution {
public:
    int maxLength(vector<int>& nums) {
        const int LIM = 2520 * 10;

        int n = nums.size();
        int ans = 0;

        for(int i  = 0;i < n;i++)
        {
            long long  temp = nums[i];
            int g = nums[i];
            int l = nums[i];
            for(int j = i+1;j < n;j++)
            {
                temp *= nums[j];
                if(temp > LIM)break;
                g = gcd(g,nums[j]);
                l = lcm(l,nums[j]);
                if(temp == (g * l))
                {
                    ans =max(ans,j-i+1);
                }
            }
        }

        return ans;
        
    }
};