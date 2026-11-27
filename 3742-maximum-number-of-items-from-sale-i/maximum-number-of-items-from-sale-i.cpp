class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {

        const int MAXF = 1500;
        vector<int> freq(MAXF + 1, 0);
        int mn = INT_MAX;
        for (auto& it : items) {
            freq[it[0]]++;
            mn = min(mn, it[1]);
        }

        // cntF[x] = number of items whose factor is a multiple of x
        vector<int> cntF(MAXF + 1, 0);
        for (int x = 1; x <= MAXF; x++)
            for (int m = x; m <= MAXF; m += x)
                cntF[x] += freq[m];

        // 0/1 knapsack: f[w] = max copies using at most w on first purchases
        vector<int> f(budget + 1, 0);
        for (auto& it : items) {
            int price = it[1], gain = cntF[it[0]];
            for (int w = budget; w >= price; w--)
                f[w] = max(f[w], f[w - price] + gain);
        }

        int ans = 0;
        for (int w = 0; w <= budget; w++)
            ans = max(ans, f[w] + (budget - w) / mn);
        return ans;
        
    }
};