class Solution {
public:
    int longestMonotonicSubarray(vector<int>& nums) {

        if(nums.size() == 1) return 1;

        int maxi = 1;
        int mini = 1;
        int ans = 0;

        for(int i = 0;i < nums.size()-1;i++)
        {
            if(nums[i] > nums[i+1])
            {
                maxi++;
                mini = 1;
            }

            if(nums[i] < nums[i+1])
            {
                mini++;
                maxi = 1;
            }

            if(nums[i] == nums[i+1])
            {
                maxi = 1;
                mini = 1;
            }

            ans = max(ans,max(maxi,mini));
        }

       

        return ans;
        
    }
};