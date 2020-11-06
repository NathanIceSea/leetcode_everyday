// 哈希表一次遍历的版本，每次向哈希表加入新值前先检查哈希表中是否有元素与当前值构成互补，有就直接输出
// 由于互补是相互的，当前元素如果与后面的元素互补将被后面的元素加入时检出，所以算法正确性可以保证

// 12ms, 10.5MB

#include <vector>
#include <map>

using namespace std;
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        map<int, int> val_index_map;
        int len = nums.size();
        for (int i = 0; i < len; i++) {
            int complement = target - nums[i];
            auto ind_iter = val_index_map.find(complement);
            if (ind_iter != val_index_map.cend()) {
                int comp_index = ind_iter->second;
                return vector<int>{i, comp_index};
            }
            else val_index_map.insert(pair<int, int>(nums[i], i));
        }
        return vector<int>{-1};
    }
};

#include <iostream>

int main() {
    vector<int> nums{ 3, 3, 3, 3 };
    int target = 6;
    Solution s;
    vector<int> result = s.twoSum(nums, target);
    std::cout << result[0] << ", " << result[1] << std::endl;
}