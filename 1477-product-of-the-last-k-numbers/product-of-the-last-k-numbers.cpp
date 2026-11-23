class ProductOfNumbers {
    vector<int> pre;
public:
    ProductOfNumbers() {
        pre.push_back(1);
    }

    void add(int num) {
        if (num == 0) {
            pre.clear();
            pre.push_back(1);
        } else {
            pre.push_back(pre.back() * num);
        }
    }

    int getProduct(int k) {
        int n = pre.size();
        if (k >= n) return 0;          
        return pre[n - 1] / pre[n - 1 - k];
    }
};