class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {

        const int m = 1e9 + 7;

        long long sum = 0,ans = 0;
        long long o = 0,e = 1;

        for(int i = 0;i < arr.size();i++)
        {
            sum += arr[i];

            if(sum % 2 == 0)
            {
                ans += o;
                e++;
            }

            else
            {
                ans += e;
                o++;
            }

            ans %= m;
        }

        return ans;
        
    }
};