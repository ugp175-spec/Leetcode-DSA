class Solution {
public:
    bool checkString(string s) {
        
        int id = 0;
        int n = s.length();
        int a = 0;

        for(int i = 0;i < n;i++)
        {
            if(s[i] == 'b')
            {
                id = i;
                a = 1;
                break;
            
            }
        }

        if(a==0)return true;
        
        for(int i = id+1;i < n;i++)
        {
            if(s[i] == 'a')
            {
                return false;
            }
        }

        return true;
    }
};