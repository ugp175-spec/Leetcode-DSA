class Solution {
public:
    int countDaysTogether(string arriveAlice, string leaveAlice, string arriveBob, string leaveBob) {

        vector <int> days = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        auto convert = [&](string date)
        {
            int month = stoi(date.substr(0,2));
            int day = stoi(date.substr(3,2));

            for(int i = 0;i < month-1;i++)
            {
                day += days[i];
            }

            return day;
        };

        int a = convert(arriveAlice);
        int b = convert(arriveBob);
        int c = convert(leaveAlice);
        int d = convert(leaveBob);

        int s = max(a,b);
        int e = min(c,d);

        return max(0,e-s+1);


        
    }
};