#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <stack>
#include <climits>
#include <algorithm>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int val) : val(val), next(nullptr) {}
    ListNode(int val, ListNode *next) : val(val), next(next) {}
};
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int val) : val(val), left(nullptr), right(nullptr) {}
    TreeNode(int val, TreeNode *left, TreeNode *right) : val(val), left(left), right(right) {}
};
class Solution1 { //两数之和
public:
     vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> mp;
        for (int i = 0; i < int(nums.size()); ++i)
        {
            if (mp.count(target-nums[i]))
                return {mp[target-nums[i]], i};
            mp[nums[i]] = i;
        }
        return {};
     }
};
class Solution2 { //无重复字符最长子串
public:
    int lengthOfLongestSubstring(string s) {
        if (s.empty())
            return 0;
        unordered_map<char, int> pos;
        int maxLen = 0;
        int left = 0;
        for (int right = 0; right < int(s.size()); ++right)
        {
            char ch = s[right];
            if (pos.count(ch) && pos[ch] >= left)
                left = pos[ch] + 1;
            maxLen = max(maxLen, right - left + 1);
            pos[ch] = right;
        }
        return maxLen;
    }
};
class Solution3 { //最长回文子串
public:
    string longestPalindrome(string s) {
        if (s.empty())
            return {};
        int n = int(s.size());
        if (n < 1)
            return s;
        int maxLen = 0;
        int start;
        for (int i = 0; i < n; ++i)
        {
            int singleCenter = expand(s, i, i);
            int doubleCenter = expand(s, i, i + 1);
            int len = max(singleCenter, doubleCenter);
            if (len > maxLen)
            {
                maxLen = len;
                start = i - (len - 1) / 2;
            }
        }
        return s.substr(start, maxLen);
    }
private:
    int expand(const string& s, int left, int right) {
        while (left >= 0 && right < int(s.size()) && s[left] == s[right])
        {
            left--;
            right++;
        }
        return right - left - 1;
    }
};
class Solution4 { //有效的括号
public:
    bool isValid(string s) {
        if (s.empty())
            return true;
        unordered_map<char, char> mp = {
            { ')', '(' },
            { ']', '[' },
            { '}', '{' }
        };
        stack<char> sta;
        for (const char& ch : s)
        {
            if (ch == '(' || ch == '[' || ch == '{')
                sta.push(ch);
            else
                if (!sta.empty() && mp[ch] == sta.top())
                    sta.pop();
                else
                    return false;
        }
        return sta.empty();
    }
};
class Solution5 { //两数相加
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int carry = 0;
        ListNode *dummy = new ListNode(-1);
        ListNode *cur = dummy;
        while (l1 != nullptr || l2 != nullptr || carry)
        {
            int val1 = l1 == nullptr ? 0 : l1->val;
            int val2 = l2 == nullptr ? 0 : l2->val;
            int sum = carry + val1 + val2;
            carry = sum / 10;
            cur->next = new ListNode(sum % 10);
            cur = cur->next;
            if (l1 != nullptr)
                l1 = l1->next;
            if (l2 != nullptr)
                l2 = l2->next;
        }
        return dummy->next;
    }
};
class Solution6 { //合并两个有序链表
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode *dummy = new ListNode(-1);
        ListNode *cur = dummy;
        while (list1 != nullptr && list2 != nullptr)
        {
            if (list1->val < list2->val)
            {
                cur->next = list1;
                list1 = list1->next;
            }
            else
            {
                cur->next = list2;
                list2 = list2->next;           
            }
            cur = cur->next;
        }
        if (list1 != nullptr)
            cur->next = list1;
        else
            cur->next = list2;
        return dummy->next;
    }
};
class Solution7 { //环形链表
public:
    bool hasCycle(ListNode *head) {
        ListNode *fast = head;
        ListNode *slow = head;
        while (fast != nullptr && fast->next != nullptr)
        {
            fast = fast->next->next;
            slow = slow->next;
            if (fast == slow)
                return true;
        }
        return false;
    }
};
class Solution8 { //相交链表
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *pA = headA;
        ListNode *pB = headB;
        while (pA != pB)
        {
            pA = pA == nullptr ? headB : pA->next;
            pB = pB == nullptr ? headA : pB->next;
        }
        return pA;
    }
};
class Solution9 { //反转链表
public:
    ListNode* reverseList(ListNode* head) {
        ListNode *cur = head;
        ListNode *revHead = nullptr;
        while (cur != nullptr)
        {
            ListNode *next = cur->next;
            cur->next = revHead;
            revHead = cur;
            cur = next;
        }
        return revHead;
    }
};
class Solution10 { //盛最多水的容器
public:
    int maxArea(vector<int>& height) {
        int n = int(height.size());
        if (n < 2)
            return 0;
        int maxArea = 0;
        int left = 0;
        int right = n - 1;
        while (left < right)
        {
            maxArea = max(maxArea, (right - left) * min(height[left], height[right]));
            if (height[left] < height[right])
                left++;
            else
                right--;
        }
        return maxArea;
    }
};
class Solution11 { //三数之和
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        int n = int(nums.size());
        if (n < 3)
            return res;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < n; ++i)
        {
            if (i > 0 && nums[i] == nums[i - 1])
                continue;
            int left = i + 1;
            int right = n - 1;
            while (left < right)
            {
                int sum = nums[i] + nums[left] + nums[right];
                if (sum < 0)
                    left++;
                else if (sum > 0)
                    right--;
                else
                {
                    res.push_back({nums[i], nums[left], nums[right]});
                    while (left < right && nums[left + 1] == nums[left])
                        left++;
                    left++;
                    while (left < right && nums[right - 1] == nums[right])
                        right--;
                    right--;  
                }
            }
        }
        return res;
    }
};
class Solution12 { //接雨水
public:
    int trap(vector<int>& height) {
        int n = int(height.size());
        if (n < 3)
            return 0;
        int total = 0;
        int left = 0;
        int right = n -1;
        int leftMax = 0;
        int rightMax = 0;
        while (left < right)
        {
            if (height[left] < height[right])
            {
                if (height[left] > leftMax)
                    leftMax = height[left];
                else
                    total += leftMax - height[left];
                left++;
            }
            else
            {
                if (height[right] > rightMax)
                    rightMax = height[right];
                else
                    total += rightMax - height[right];
                right--;
            }
        }
        return total;
    }
};
class Solution13 { //寻找两个正序数组中位数
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = int(nums1.size());
        int n = int(nums2.size());
        if ((m + n) % 2)
        {
            return findTheK(nums1, 0, nums2, 0, (m + n) / 2);
        }
        else
        {
            int midLeft = findTheK(nums1, 0, nums2, 0, (m + n) / 2 - 1);
            int midRight = findTheK(nums1, 0, nums2, 0, (m + n) / 2);
            return (midLeft + midRight) / 2.0;
        }
    }
private:
    int findTheK(vector<int>& nums1, int i, vector<int>& nums2, int j, int k) {
        int m = int(nums1.size());
        int n = int(nums2.size());
        if (i + k >= m)
            return nums2[j + k];
        if (j + k >= n)
            return nums1[i + k];
        if (k == 0)
            return min(nums1[i], nums2[j]);
        int mid = k / 2;
        int val1 = i + mid < m ? nums1[i + mid] : INT_MAX;
        int val2 = j + mid < n ? nums2[j + mid] : INT_MAX;
        if (val1 < val2)
            return findTheK(nums1, i + mid + 1, nums2, j, k - mid - 1);
        else
            return findTheK(nums1, i, nums2, j + mid + 1, k - mid - 1);
    }
};
class Solution14 { //搜索旋转排序数组
public:
    int search(vector<int>& nums, int target) {
        if (nums.empty())
            return -1;
        int left = 0;
        int right = int(nums.size()) - 1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (target == nums[mid])
                return mid;
            if (nums[left] <= nums[mid])
            {
                if (target >= nums[left] && target < nums[mid])
                    right = mid - 1;
                else
                    left = mid + 1;
            }
            else
            {
                if (target <= nums[right] && target > nums[mid])
                    left = mid + 1;
                else
                    right = mid - 1;
            }
        }
        return -1;     
    }
};
class Solution15 { //二分查找
public:
    int search(vector<int>& nums, int target) {
        if (nums.empty())
            return -1;
        int left = 0;
        int right = int(nums.size()) - 1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (target < nums[mid])
                right = mid - 1;
            else if (target > nums[mid])
                left = mid + 1;
            else
                return mid;
        }
        return -1;
    }
};
class Solution16 { //中序遍历
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        inorder(root, res);
        return res;
    }
private:
    void inorder(TreeNode* root, vector<int>& res) {
        if (root == nullptr)
            return;
        inorder(root->left, res);
        res.push_back(root->val);
        inorder(root->right, res);
    }
};
class Solution17 { //层序遍历
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if (root == nullptr)
            return res;
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty())
        {
            int n = int(q.size());
            vector<int> cur;
            for (int i = 0; i < n; ++i)
            {
                TreeNode *node = q.front();
                q.pop();
                cur.push_back(node->val);
                if (node->left != nullptr)
                    q.push(node->left);
                if (node->right != nullptr)
                    q.push(node->right);
            }
            res.push_back(cur);
        }
        return res;
    }
};
class Solution18 { //最大深度
public: 
    int maxDepth(TreeNode* root) {
        if (root == nullptr)
            return 0;
        int left = maxDepth(root->left);
        int right = maxDepth(root->right);
        return max(left, right) + 1;
    }
};
class Solution19 { //最大路径和
public:
    int maxPathSum(TreeNode* root) {
        int maxPathSum = INT_MIN;
        maxSubPathSum(root, maxPathSum);
        return maxPathSum;
    }
private:
    int maxSubPathSum(TreeNode* root, int& maxPathSum) {
        if (root == 0)
            return 0;
        int left = max(0, maxSubPathSum(root->left, maxPathSum));
        int right = max(0, maxSubPathSum(root->right, maxPathSum));
        maxPathSum = max(maxPathSum, left + right + root->val);
        return max(left, right) + root->val;
    }
};
class Solution20 {  //柱状图最大矩形
public:
    int largestRectangleArea(vector<int>& heights) {
        if (heights.empty())
            return 0;
        int n = int(heights.size());
        stack<int> sta;
        int maxArea = 0;
        for (int i = 0; i <= n; ++i)
        {
            int cur = i == n ? 0 : heights[i];
            while (!sta.empty() && cur < heights[sta.top()])
            {
                int topIdx = sta.top();
                sta.pop();
                int height = heights[topIdx];
                int left = sta.empty() ? -1 : sta.top();
                int width = (i - 1)  - (left + 1) + 1;
                maxArea = max(maxArea, width * height);
            }
            sta.push(i);
        }
        return maxArea;
    }
};
class MinStack21 { //最小栈
public:
    MinStack21() 
    {
    }
    void push(int val) 
    {
        if (staMin.empty() || val <= sta.top())
            staMin.push(val);
        sta.push(val); 
    }
    void pop() 
    {
        if (staMin.top() == sta.top())
            staMin.pop();
        sta.pop();
    }
    int top() 
    {
        return sta.top();
    }
    int getMin()
    {   
        return staMin.top();
    }
private:
    stack<int> sta;
    stack<int> staMin;
};
class Solution22 { //最大子数组和
public:
    int maxSubArray(vector<int>& nums) {
        if (nums.empty())
            throw invalid_argument("nums is empty");
        int maxSub = nums[0];
        int maxCur = nums[0];
        for (int i = 1; i < int(nums.size()); ++i)
        {
            int cur = nums[i];
            maxCur = max(cur, maxCur + cur);
            maxSub = max(maxSub, maxCur);
        }
        return maxSub;
    }
};
class Solution23 { //爬楼梯
public:
    int climbStairs(int n) {
        if (n == 0)
            return 0;
        if (n == 1)
            return 1;
        if (n == 2)
            return 2;
        int a = 1;
        int b = 2;
        int total = 0;
        for (int i = 3; i <= n; ++i)
        {
            total = a + b;
            a = b;
            b = total;
        }
        return total;
    }
};
class Solution24 { //买卖股票最佳时机
public:
    int maxProfit(vector<int>& prices) {
        int n = int(prices.size());
        if (n < 2)
            return 0;
        int maxProfit = 0;
        int low = prices[0];
        for (int i = 1; i < n; ++i) 
        {   
            int cur = prices[i];
            maxProfit = max(maxProfit, cur - low);
            low = min(low, cur);
        }
        return maxProfit;
    }
};
class Solution25 { //合并区间
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> res;
        if (intervals.empty())
            return res;
        sort(intervals.begin(), intervals.end());
        res.push_back(intervals[0]);
        for (int i = 1; i < int(intervals.size()); ++i) 
        {
            auto& last = res.back();
            auto cur = intervals[i];
            if (last.back() < cur.front())
                res.push_back(cur);
            else
                last.back() = max(last.back(), cur.back());
        }
        return res;
    }
};
class Solution26 { //螺旋矩阵
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> res;
        if (matrix.empty())
            return res;
        int top = 0;
        int bottom = matrix.size() - 1;
        int left = 0;
        int right = matrix[0].size() - 1;
        while (true)
        {
            for (int i = left; i <= right; ++i)
                res.push_back(matrix[top][i]);
            if (++top > bottom)
                break;
            for (int i = top; i <= bottom; ++i)
                 res.push_back(matrix[i][right]);
            if (--right < left)
                break;
            for (int i = right; i >= left; --i)
                 res.push_back(matrix[bottom][i]); 
            if (--bottom < top)
                break;
            for (int i = bottom; i >= top; --i)
                 res.push_back(matrix[i][left]);
            if (++left > right)
                break;   
        }
        return res;
    }   
};
class Solution27 { // 全排列
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        if (nums.empty())
            return res;
        vector<int> path;
        vector<bool> visited(int(nums.size()), false);
        trackback(nums, visited, path, res);
        return res;
    }
private:
    void trackback(vector<int>& nums, vector<bool>& visited, vector<int>& path, vector<vector<int>>& res) {
        if (path.size() == nums.size())
        {
            res.push_back(path);
            return;
        }
        for (int i = 0; i < int(nums.size()); ++i) 
        {
            if (visited[i])
                continue;
            visited[i] = true;
            path.push_back(nums[i]);
            trackback(nums, visited, path, res);
            path.pop_back();
            visited[i] = false;
        }
    }
};
class Solution28 { //子集
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        if (nums.empty())
            return res;
        vector<int> path;
        trackback(nums, 0, path, res);
        return res;
    }
private:
    void trackback(vector<int>& nums, int start, vector<int>& path, vector<vector<int>>& res) {
        res.push_back(path);
        for (int i = start; i < int(nums.size()); ++i) 
        {
            path.push_back(nums[i]);
            trackback(nums, i + 1, path, res);
            path.pop_back();
        }
    }
};
class Solution29 { //岛屿数量 
public:
    int numIslands(vector<vector<char>>& grid) {
        int count = 0;
        for (int row = 0; row < int(grid.size()); ++row)
        {
            for (int col = 0; col < int(grid[0].size()); ++col)
            {
                if (grid[row][col] != '0')
                {
                    gridDfs(grid, row, col);
                    count++;
                }
            }
        }
        return count;
    }
private:
    void gridDfs(vector<vector<char>>& grid, int row, int col) {
        if (row < 0 || row >= int(grid.size()) || col < 0 || col >= int(grid[0].size()))
            return;
        if (grid[row][col] == '0')
            return;
        grid[row][col] = '0';
        gridDfs(grid, row - 1, col);
        gridDfs(grid, row + 1, col);
        gridDfs(grid, row, col - 1);
        gridDfs(grid, row, col + 1);
    }
};
class Solution30 { //课程表
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        vector<int> inDegree(numCourses, 0);
        for (const auto& edge : prerequisites) 
        {
            int cur = edge[0];
            int pre = edge[1];
            graph[pre].push_back(cur);
            inDegree[cur]++;
        }
        queue<int> q;
        for (int i = 0; i < numCourses; ++i)
        {
            if (!inDegree[i])
                q.push(i);
        }
        int count = 0;
        while (!q.empty())
        {
            int cur = q.front();
            q.pop();
            count++;
            for (int next : graph[cur])
            {
                inDegree[next]--;
                if (!inDegree[next])
                    q.push(next);
            }
        }
       return count == numCourses; 
    }
};
int main(int argc, char *argv[])
{
    return 0;
}