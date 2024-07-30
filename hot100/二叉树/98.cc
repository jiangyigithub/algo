#include <iostream>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <climits> // 包含 LONG_MAX 和 LONG_MIN 的定义
#include <algorithm> // 包含 std::min 和 std::max 的定义

// 定义二叉树节点结构体
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    // 辅助递归函数，返回值是一个 pair，包含当前子树的最小值和最大值
    std::pair<long, long> dfs(TreeNode* node) {
        // 基本情况：空节点返回一个特殊的最小值和最大值
        if (node == nullptr) {
            return {LONG_MAX, LONG_MIN}; // 空节点的最小值为 LONG_MAX，最大值为 LONG_MIN
        }

        // 递归处理左子树和右子树，获取它们的最小值和最大值
        auto [l_min, l_max] = dfs(node->left);
        auto [r_min, r_max] = dfs(node->right);
        
        long x = node->val; // 当前节点的值

        // 检查当前节点是否满足二叉搜索树的性质：
        // 左子树的最大值应小于当前节点值，右子树的最小值应大于当前节点值
        if (x <= l_max || x >= r_min) {
            // 如果不满足，返回一个特殊的值表示这不是一个二叉搜索树
            return {LONG_MIN, LONG_MAX}; // 用特殊值表示这个子树不是 BST
        }

        // 返回当前子树的最小值和最大值
        // 当前子树的最小值是左子树的最小值和当前节点值中的最小者
        // 当前子树的最大值是右子树的最大值和当前节点值中的最大者
        return {std::min(l_min, x), std::max(r_max, x)};
    }

public:
    // 主函数，判断二叉树是否是有效的二叉搜索树
    bool isValidBST(TreeNode* root) {
        // 调用辅助递归函数，检查根节点的子树是否是二叉搜索树
        // 如果返回的最大值是 LONG_MAX，表示整个树不是二叉搜索树
        return dfs(root).second != LONG_MAX;
    }
};

struct TestCase
{
    TreeNode *root;
    bool expected;
    std::string description;

    TestCase(TreeNode *r, bool e, std::string d) : root(r), expected(e), description(d) {}
};

void runTestCase(const TestCase &testCase)
{
    Solution solution;
    bool result = solution.isValidBST(testCase.root);
    std::cout << "Description: " << testCase.description << "\n";
    std::cout << "Expected: " << (testCase.expected ? "true" : "false") << "\n";
    std::cout << "Actual: " << (result ? "true" : "false") << "\n";
    std::cout << "Test " << (result == testCase.expected ? "Passed" : "Failed") << "\n\n";
}

int main()
{
    std::vector<TestCase> testCases;

    // Test case 1
    TreeNode *root1 = new TreeNode(2);
    root1->left = new TreeNode(1);
    root1->right = new TreeNode(3);
    testCases.push_back(TestCase(root1, true, "Example 1: [2,1,3]"));

    // Test case 2
    TreeNode *root2 = new TreeNode(5);
    root2->left = new TreeNode(1);
    root2->right = new TreeNode(4);
    root2->right->left = new TreeNode(3);
    root2->right->right = new TreeNode(6);
    testCases.push_back(TestCase(root2, false, "Example 2: [5,1,4,null,null,3,6]"));

    // Run all test cases
    for (const auto &testCase : testCases)
    {
        runTestCase(testCase);
    }

    // Clean up
    for (const auto &testCase : testCases)
    {
        // We should ideally delete all nodes to avoid memory leaks
        // Here we'll just delete the root nodes for simplicity
        delete testCase.root;
    }

    return 0;
}
