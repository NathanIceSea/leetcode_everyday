#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Bottom-to-up Max Heap Arrange
void ArrangeBtuMaxHeap(vector<int> &arr, int heap_size, int root)
{
    int cur_index = root;
    while (cur_index < heap_size) {
        int left_index = 2 * cur_index + 1, right_index = 2 * cur_index + 2;
        int biggest_index = cur_index;
        // 注意左右子节点序号不能超过 heap_size；如果都超过说明 cur_index 就在底部，它就是 MaxHeap 良序的
        if (left_index < heap_size && arr[left_index] > arr[biggest_index])
            biggest_index = left_index;
        if (right_index < heap_size && arr[right_index] > arr[biggest_index])
            biggest_index = right_index;
        if (biggest_index != cur_index) {
            swap(arr[cur_index], arr[biggest_index]);
            // 将 cur_index 置为被交换的节点的 index
            cur_index = biggest_index;
        } else {
            // cur_index == biggest_index; 说明 cur_index 及以下都是 MaxHeap，完成
            break;
        }
    }
}

void HeapSort(vector<int> &arr) {
    int size = arr.size();
    // 对于大小为 size 的堆，最后一个有子的根节点的儿子是 size - 1，所以其序号为 (size - 1 - 1) / 2 = size/2 - 1
    for (int i = (size - 2) / 2; i >= 0; i--)
        ArrangeBtuMaxHeap(arr, size, i);
    // 每次拿走堆顶的最大元素与堆末的元素交换，并使堆的逻辑大小 - 1，由于 Root 的左右子仍为良序堆所以可以直接 Arrange 恢复良序
    for (; size > 1; size--) {
        swap(arr[0], arr[size - 1]);
        ArrangeBtuMaxHeap(arr, size - 1, 0);
    }
}

// 返回二分搜索限定区间；如果存在两个相等值返回 [l_target][r_target]，如果是夹逼值返回 [l_smaller][r_bigger]
// 否则如果在 arr 中是单个相等值形如 [l_smaller][r_target] 或 [l_target][r_bigger]，在二分搜索收敛 left == right == target 后返回 [left][left+1]
vector<int> BinarySearchRange(vector<int> const & arr, double target) {
    int len = arr.size();
    int left = 0, right = len - 1;
    while (true) {
        int middle = (left + right) / 2;
        if (left == right) {
            return vector<int>{left, left + 1};
        } else if ((arr[middle] < target && arr[middle + 1] > target) ||
                   (arr[middle] == target && arr[middle + 1] == target))
            return vector<int>{middle, middle + 1};
        // 仅剩下四种情形：< <; < <=; >= >; > >
        else if (arr[middle + 1] <= target) {
            left = middle + 1;
        } else if (arr[middle] >= target) {
            right = middle;
        }
    }
}

// 在原始顺序的 vector 中找到结果元素
vector<int> GetMappedIndexResult(vector<int> const &ori, vector<int> const &nums, vector<int> &result) {
    int len = ori.size();
    // result 中哪一个已经替换过
    int flagged = -1;
    for (int i = 0; i < len; i++) {
        if (flagged != 0 && ori[i] == nums[result[0]]) {
            result[0] = i;
            // 说明 result[1] 已经替换
            if (flagged != -1)
                return result;
            else
                flagged = 0;
        } else if (flagged != 1 && ori[i] == nums[result[1]]) {
            result[1] = i;
            if (flagged != -1)
                return result;
            else
                flagged = 1;
        }
    }
    return result;
}

// 堆排序 + 找到 target/2 位置 + 双指针左右移动（动态规划？）
class Solution {
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        vector<int> ori = vector<int>(nums);
        int len = ori.size();
        HeapSort(nums);
        vector<int> middles = BinarySearchRange(nums, target / 2.0);
        while (true) {
            if (nums[middles[0]] + nums[middles[1]] == target)
                return GetMappedIndexResult(ori, nums, middles);
            // 如果相加大于 target，就通过以 middles[0] 为起点向左遍历来检验 middles[1] 是否为加数之一
            else if (nums[middles[0]] + nums[middles[1]] > target) {
                int l = middles[0] - 1;
                for (int i = l; i >= 0; i--) {
                    if (nums[i] + nums[middles[1]] == target) {
                        middles[0] = i;
                        return GetMappedIndexResult(ori, nums, middles);
                    } else if (nums[i] + nums[middles[1]] < target) {
                        // 说明 middles[1] 不可能是加数之一
                        break;
                    }
                }
                middles[1]++;
                continue;
            }
            // 相加小于 target，同理
            else {
                int r = middles[1] + 1;
                for (int i = r; i < len; i++) {
                    if (nums[middles[0]] + nums[i] == target) {
                        middles[1] = i;
                        return GetMappedIndexResult(ori, nums, middles);
                    } else if (nums[middles[0]] + nums[i] > target) {
                        // 说明 middles[0] 不可能是加数之一
                        break;
                    }
                }
                middles[0]--;
                continue;
            }
        }
    }
};

int main() {
    vector<int> nums{429, 364, 392, 148, 196, 407, 193, 48, 422, 282, 218, 487, 188, 190, 401, 186, 10, 29, 418, 288, 500, 500, 367, 415, 58, 484, 136, 380, 474, 76, 348, 267, 183, 453, 25, 203, 419, 171, 228, 160, 292, 304, 41, 410, 149, 62, 96, 72, 352, 361, 483, 496, 438, 123, 259, 437, 237, 315, 119, 381, 116, 357, 426, 206, 400, 81, 53, 101, 394, 428, 1, 201, 37, 230, 170, 344, 412, 213, 134, 132, 131, 289, 92, 151, 254, 459, 11, 227, 457, 488, 301, 142, 242, 353, 283, 467, 435, 192, 238, 215, 331};
    HeapSort(nums);
    vector<int> search = BinarySearchRange(nums, 500);
    for_each(
        search.cbegin(), search.cend(), [&](int const &each) {
            cout << each << ", ";
        });
    cout << endl;
    cout << nums[search[0]] << ", " << nums[search[1]] << endl;

    Solution s;
    vector<int> test{-10, 7, 19, 15};
    vector<int> result = s.twoSum(test, 9);
    cout << result[0] << ", " << result[1] << endl;
}