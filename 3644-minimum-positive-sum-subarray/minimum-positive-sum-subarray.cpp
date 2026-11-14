class Solution {
public:
    int minimumSumSubarray(vector<int>& nums, int l, int r) {

        int ans = 0;
        int n = nums.size();

        for(int i = 0;i < n;i++)
        {
            int temp = 0;
            for(int j = i;j < n;j++)
            {
               temp += nums[j];

               if(j - i+1 <= r && j-i+1 >= l)
               {
                    if(temp > 0 && ans != 0)
                    {
                        ans = min(ans,temp);
                     }
                    else if(ans == 0 && temp > 0)
                    {
                        ans = temp;
                    }

               }
               
                
            }
        }

        return ans == 0 ?-1 : ans;
        
    }
};