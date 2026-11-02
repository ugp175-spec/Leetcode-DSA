class Solution {
public:
    int minMoves2(vector<int>& nums) {

        sort(nums.begin(),nums.end());
        int n = nums.size();
        int ans = 0;

        for(int i = 0;i < nums.size();i++)
        {
            if(nums[i] >= nums[(n-1)/2])
            {
                ans += nums[i] - nums[(n-1)/2];
            }
            else
            {
                ans += nums[(n-1)/2] - nums[i];
            }
        }

        return ans;
        
    }
};