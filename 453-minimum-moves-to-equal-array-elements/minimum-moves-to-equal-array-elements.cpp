class Solution {
public:
    int minMoves(vector<int>& nums) {

        int ans = 0;

        int mini = *min_element(nums.begin(),nums.end());

        for(int x : nums)
        {
            ans += x - mini;
        }

        return ans;
        
        
    }
};