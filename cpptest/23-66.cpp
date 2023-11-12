#include "head.hpp"
/*
剑指 Offer 66. 构建乘积数组
给定一个数组 A[0,1,…,n-1]，请构建一个数组 B[0,1,…,n-1]，其中 B[i] 的值是数组 A 中除了下标 i 以外的元素的积, 即 B[i]=A[0]×A[1]×…×A[i-1]×A[i+1]×…×A[n-1]。不能使用除法。

示例:

输入: [1,2,3,4,5]
输出: [120,60,40,30,24]

*/
class Solution
{
public:
    vector<int> productExceptSelf(vector<int> &a)
    {
       int len=a.size();
       vector<int> L(len,0);
       vector<int> R(len,0);
       vector<int> res(len,0);
       L[0]=1;
       R[len-1]=1;
       for(int i=1;i<len;i++){
        L[i]=L[i-1]*a[i-1];
       }
       for(int j=len-2;j>=0;j--){
        R[j]=R[j+1]*a[j+1];
       }
       for(int k=0;k<len;k++){
        res[k]=L[k]*R[k];
       }
       return res;
    }
};

int main()
{
    vector<int> input = {1, 2, 3, 4, 5};
    vector<int> res = Solution().productExceptSelf(input);
    for (auto e : res)
    {
        cout << e << ", ";
    }
}