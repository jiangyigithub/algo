#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 结构体用于存储测试用例的输入和期望输出
struct TestCase
{
    vector<int> heights;
    int expected;

    TestCase(vector<int> h, int exp) : heights(h), expected(exp) {}
};

class Solution
{
public:
    /*
    water[i] = min(
        # 左边最高的柱子
        max(height[0..i]),
        # 右边最高的柱子
        max(height[i..end])
    ) - height[i]
    */

    /// 暴力解法
    int trap0(vector<int> &height)
    {
        // 计算总的接雨水量
        int sum = 0;
        if (height.empty())
            return 0;

        int n = height.size();
        vector<int> water(n, 0); // 初始化 water 数组的大小为 n，并全部赋值为 0

        for (int i = 1; i < n - 1; ++i)
        {
            int leftmax = 0;
            int rightmax = 0;

            // 找到左边最高的柱子
            for (int k = i; k >= 0; k--)
            {
                leftmax = max(leftmax, height[k]);
            }

            // 找到右边最高的柱子
            for (int k = i; k < n; k++)
            { // 从 i+1 开始，因为 i 本身不应该包括在内
                rightmax = max(rightmax, height[k]);
            }

            // 计算当前柱子可以接的雨水量
            water[i] = max(0, min(leftmax, rightmax) - height[i]);
        }
        for (auto elem : water)
        {
            sum += elem;
        }
        return sum;
    }

    /// 暴力解法
    int trap(vector<int> &height)
    {
        // 计算总的接雨水量
        int sum = 0;
        if (height.empty())
            return 0;

        int n = height.size();
        vector<int> water(n, 0); // 初始化 water 数组的大小为 n，并全部赋值为 0

        for (int i = 1; i < n - 1; ++i)
        {
            int leftmax = 0;
            int rightmax = 0;

            // 找到左边最高的柱子
            for (int k = i; k >= 0; k--)
            {
                leftmax = max(leftmax, height[k]);
            }

            // 找到右边最高的柱子
            for (int k = i; k < n; k++)
            { // 从 i+1 开始，因为 i 本身不应该包括在内
                rightmax = max(rightmax, height[k]);
            }

            // 计算当前柱子可以接的雨水量
            water[i] = max(0, min(leftmax, rightmax) - height[i]);
            sum += water[i];
        }
        return sum;
    }

    /// @brief 带memory的
    /// @param height
    /// @return
    int trapWithMemory(vector<int> &height)
    {
        if (height.size() == 0)
        {
            return 0;
        }
        int n = height.size();
        int res = 0;
        // 数组充当备忘录
        vector<int> l_max(n);
        vector<int> r_max(n);
        // 初始化 base case
        l_max[0] = height[0];
        r_max[n - 1] = height[n - 1];
        // 从左向右计算 l_max
        for (int i = 1; i < n; i++)
            l_max[i] = max(height[i], l_max[i - 1]);
        // 从右向左计算 r_max
        for (int i = n - 2; i >= 0; i--)
            r_max[i] = max(height[i], r_max[i + 1]);
        // 计算答案
        for (int i = 1; i < n - 1; i++)
            res += min(l_max[i], r_max[i]) - height[i];
        return res;
    }

    int trapWithDP(vector<int> &height)
    {
        if (height.empty())
            return 0;

        int n = height.size();
        vector<int> left_max(n, 0);
        vector<int> right_max(n, 0);

        // 填充 left_max 数组
        left_max[0] = height[0];
        for (int i = 1; i < n; ++i)
        {
            left_max[i] = max(left_max[i - 1], height[i]);
        }

        // 填充 right_max 数组
        right_max[n - 1] = height[n - 1];
        for (int i = n - 2; i >= 0; --i)
        {
            right_max[i] = max(right_max[i + 1], height[i]);
        }

        // 计算总水量
        int sum = 0;
        for (int i = 0; i < n; ++i)
        {
            sum += min(left_max[i], right_max[i]) - height[i];
        }
        return sum;
    }

    int trap3(vector<int> &height)
    {
        if (height.size() <= 2)
            return 0;

        int l = 0;
        int r = height.size() - 1;
        int cap = 0;                   // 待返回的水量 (water capacity)
        int leftCeil = height.front(); // 左侧上限 c(l)
        int rightCeil = height.back(); // 右侧上限 c(r)

        while (l <= r)
        {
            if (leftCeil < rightCeil)
            {
                cap += leftCeil - height[l]; // 增加水量
                l++;                         // l 右移
                if (l < height.size())
                    leftCeil = max(leftCeil, height[l]); // 更新 c(l)
            }
            else
            {
                cap += rightCeil - height[r]; // 增加水量
                r--;                          // r 左移
                if (r >= 0)
                    rightCeil = max(rightCeil, height[r]); // 更新 c(r)
            }
        }

        return cap;
    }

    // 计算能接的雨水总量
    int trap2(vector<int> &height)
    {
        int n = height.size();
        if (n == 0)
            return 0;

        int left = 0, right = n - 1;
        int left_max = 0, right_max = 0;
        int water = 0;

        while (left <= right)
        {
            if (height[left] <= height[right])
            {
                // 如果左边柱子较低或相等，处理左边柱子
                if (height[left] >= left_max)
                {
                    left_max = height[left];
                }
                else
                {
                    water += left_max - height[left];
                }
                left++;
            }
            else
            {
                // 如果右边柱子较低，处理右边柱子
                if (height[right] >= right_max)
                {
                    right_max = height[right];
                }
                else
                {
                    water += right_max - height[right];
                }
                right--;
            }
        }

        return water;
    }

    // 运行单个测试用例并输出结果
    void runTest(const TestCase &testCase)
    {
        vector<int> heights = testCase.heights;
        int expected = testCase.expected;

        int result = trap(heights);

        // 输出测试用例的输入数组
        cout << "Input: [";
        for (size_t i = 0; i < heights.size(); ++i)
        {
            cout << heights[i];
            if (i < heights.size() - 1)
            {
                cout << ", ";
            }
        }
        cout << "]" << endl;

        // 输出预期结果和实际结果
        cout << "Expected: " << expected << endl;
        cout << "Actual: " << result << endl;

        // 判断测试是否通过
        if (result == expected)
        {
            cout << "Test Passed!" << endl;
        }
        else
        {
            cout << "Test Failed!" << endl;
        }

        cout << "----------------------" << endl;
    }

    // 可视化函数，用于输出柱状图表示的柱子高度
    void visualize(vector<int> &heights)
    {
        int maxHeight = *max_element(heights.begin(), heights.end());

        for (int h = maxHeight; h > 0; --h)
        {
            for (int i = 0; i < heights.size(); ++i)
            {
                if (heights[i] >= h)
                {
                    cout << "|";
                }
                else
                {
                    cout << " ";
                }
                cout << " ";
            }
            cout << endl;
        }

        for (int i = 0; i < heights.size(); ++i)
        {
            cout << "==";
        }
        cout << endl;

        for (int i = 0; i < heights.size(); ++i)
        {
            cout << heights[i] << " ";
        }
        cout << endl;
    }
};

int main()
{
    Solution solution;

    // 测试用例
    vector<TestCase> testCases = {
        // 正常情况
        {{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}, 6},
        {{4, 2, 0, 3, 2, 5}, 9},
        {{3, 1, 2, 4, 0, 1, 3, 2, 1, 2, 1}, 12},

        // 边界情况：没有柱子或只有一个柱子
        {{}, 0},
        {{1}, 0},
        {{5}, 0},

        // 全部递减的情况
        {{5, 4, 3, 2, 1}, 0},

        // 全部递增的情况
        {{1, 2, 3, 4, 5}, 0},

        // 部分递减、递增混合的情况
        {{3, 1, 2, 0, 4, 1}, 6},

        // 大量连续相等的柱子
        {{2, 2, 2, 2, 2, 2, 2, 2}, 0},

        // 大量相等且有不同高度的柱子
        {{3, 3, 1, 2, 2, 1, 3, 3}, 6}};

    // 遍历每个测试用例，运行并输出结果
    for (auto &testCase : testCases)
    {
        // solution.visualize(testCase.heights);  // 可视化柱子高度
        solution.runTest(testCase); // 运行测试用例
    }

    return 0;
}
