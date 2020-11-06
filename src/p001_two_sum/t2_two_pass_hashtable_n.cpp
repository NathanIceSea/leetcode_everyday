// 由于只考虑两个值相加等于 target，没必要像 s2 一样用二分搜索等奇技淫巧
// 使用哈希表来存储值到 index 的对应关系，遍历数组中每个元素在哈希表中搜索互补值，以空间换时间思想得到 O(N) 复杂度；哈希表可能碰撞，但单次查询时间复杂度基本为 O(1)

// 注意数组中单个值出现多次的情况；由于题目条件给定必定有且仅有一个结果，所以如果互补值为自身可以在第二次遍历中把两个 index 返回
// 两次遍历版本，第一次遍历构建哈希表，第二次遍历查找互补值

#include <vector>
#include <map>

using namespace std;
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        map<int, int> val_index_map;
        int len = nums.size();
        for (int i = 0; i < len; i++) {
            val_index_map.insert(pair<int, int>(nums[i], i));
        }
        for (int i = 0; i < len; i++) {
            int complement = target - nums[i];
            auto ind_iter = val_index_map.find(complement);
            if (ind_iter != val_index_map.cend()) {
                int comp_index = ind_iter->second;
                if (i != comp_index)
                    return vector<int>{i, comp_index};
                // if (i == comp_index) 存在下一个 i 使得 i ！= comp_index
            }
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