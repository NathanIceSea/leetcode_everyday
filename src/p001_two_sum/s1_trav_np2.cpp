#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> result;
        int len = nums.size();
        for (int i = 0; i < len - 1; i++) {
            for (int j = i + 1; j < len; j++) {
                if (nums[i] + nums[j] == target) {
                    result.push_back(i);
                    result.push_back(j);
                    goto out_loop;
                }
            }
        }
        out_loop:
        return result;
    }
};

int main() {
    vector<int> nums{ 2, 7, 11, 15 };
    int target = 9;
    Solution s;
    vector<int> result = s.twoSum(nums, target);
    cout << result[0] << ", " << result[1] << endl;
}