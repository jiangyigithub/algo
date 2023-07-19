/*
剑指 Offer 21. 调整数组顺序使奇数位于偶数前面
输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有奇数在数组的前半部分，所有偶数在数组的后半部分。

 

示例：

输入：nums = [1,2,3,4]
输出：[1,3,2,4] 
注：[3,1,2,4] 也是正确的答案之一。
 

提示：

0 <= nums.length <= 50000
0 <= nums[i] <= 10000
*/

#include "head.hpp"
#include "PrintUtil.hpp"

// ===== Solution Code =====
class Solution {
public:
    vector<int> exchange(vector<int>& nums) {
        int i = 0, j = nums.size() - 1;
        while (i < j)
        {
            if(i < j && (nums[i] & 1) == 1) i++;
            if(i < j && (nums[j] & 1) == 0) j--;
            swap(nums[i], nums[j]);
        }
        return nums;
    }
};

int main() {
    // ======= Test Case =======
    vector<int> nums = { 1, 2, 4,7,9, 5, 6, 3 };
    // ====== Driver Code ======
    Solution* slt = new Solution();
    vector<int> res = slt->exchange(nums);
    PrintUtil::printVector(res);
    
    return 0;
}
