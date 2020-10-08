#include <vector>
#include <iostream>
using namespace std;

// 不知何故比普通的慢很多
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> result;
        for (vector<int>::const_iterator ori = nums.cbegin(), end = nums.cend(); ori != end - 1; ori++) {
            for (vector<int>::const_iterator cur = ori + 1; cur != nums.cend(); cur++) {
                if (*ori + *cur == target) {
                    result.push_back(ori - nums.cbegin());
                    result.push_back(cur - nums.cbegin());
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