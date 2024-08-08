#include <iostream>
#include <vector>
#include <string>
#include <functional>

using namespace std;

class Solution
{

public:
    vector<vector<int>> permute(vector<int> &nums)
    {
        int n = nums.size();
        vector<vector<int>> ans;
        vector<int> path(n), on_path(n);
        function<void(int)> dfs = [&](int i)
        {   
            // If the depth equals the size of the vector, we have a complete permutation
            if (i == n)
            {
                ans.emplace_back(path);
                return;
            }
            for (int j = 0; j < n; ++j)
            {
                if (!on_path[j])
                {
                    path[i] = nums[j];
                    on_path[j] = true;
                    dfs(i + 1); // Recur to fill the next position
                    on_path[j] = false; // 恢复现场
                }
            }
        };

        dfs(0); // Start the DFS with the first position

        return ans;
    }
};

void printResult(const vector<vector<int>> &result)
{
    for (const auto &vec : result)
    {
        for (int num : vec)
        {
            cout << num << " ";
        }
        cout << endl;
    }
}

int main()
{
    Solution sol;
    vector<int> nums1 = {1, 2, 3};
    vector<int> nums2 = {0, 1};
    vector<int> nums3 = {1};

    cout << "Permutations of {1, 2, 3}:" << endl;
    vector<vector<int>> result1 = sol.permute(nums1);
    printResult(result1);

    // cout << "Permutations of {0, 1}:" << endl;
    // vector<vector<int>> result2 = sol.permute(nums2);
    // printResult(result2);

    // cout << "Permutations of {1}:" << endl;
    // vector<vector<int>> result3 = sol.permute(nums3);
    // printResult(result3);

    return 0;
}
