#include "head.hpp"
#include "PrintUtil.hpp"

class Solution {
public:
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        quickSort(arr, 0, arr.size() - 1);
        vector<int> res;
        res.assign(arr.begin(), arr.begin() + k);
        return res;
    }
private:
    void quickSort(vector<int>& arr, int l, int r) {
        // 子数组长度为 1 时终止递归
        if (l >= r) return;
        // 哨兵划分操作（以 arr[l] 作为基准数）
        int i = l, j = r;
        while (i < j) {
            // Move j towards left until arr[j] < arr[l]
            while (i < j && arr[j] >= arr[l]) j--;
            // Move i towards right until arr[i] > arr[l]
            while (i < j && arr[i] <= arr[l]) i++;
            // Swap elements at indices i and j to maintain the partitioning
            swap(arr[i], arr[j]);
        }
        // Place the pivot element in its correct sorted position
        swap(arr[i], arr[l]);
        // 递归左（右）子数组执行哨兵划分
        quickSort(arr, l, i - 1);
        quickSort(arr, i + 1, r);
    }
};

int main() {
    // ======= Test Case =======
    vector<int> arr = { 3, 2, 1 };
    int k = 2;
    // ====== Driver Code ======
    Solution* slt = new Solution();
    vector<int> res = slt->getLeastNumbers(arr, k);
    PrintUtil::printVector(res);
    
    return 0;
}