class Solution {
public:
    int minChanges(string s) {

        int ans = 0;
        int i = 0;

        while(i  < s.length()-1)
        {
            if(s[i] != s[i+1])
            {
                ans++;
            }
            i += 2;
        }
        
        return ans;
        
    }
};