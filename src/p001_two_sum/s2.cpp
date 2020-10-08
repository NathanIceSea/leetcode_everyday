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

// 堆排序 + 找到 target/2 位置 + 双指针左右移动动态规划
class Solution {
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
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
    vector<int> nums{429, 364, 392, 148, 196, 407, 193, 48, 422, 282, 218, 487, 188, 190, 401, 186, 10, 29, 418, 288, 500, 367, 415, 58, 484, 136, 380, 474, 76, 348, 267, 183, 453, 25, 203, 419, 171, 228, 160, 292, 304, 41, 410, 149, 62, 96, 72, 352, 361, 483, 496, 438, 123, 259, 437, 237, 315, 119, 381, 116, 357, 426, 206, 400, 81, 53, 101, 394, 428, 1, 201, 37, 230, 170, 344, 412, 213, 134, 132, 131, 289, 92, 151, 254, 459, 11, 227, 457, 488, 301, 142, 242, 353, 283, 467, 435, 192, 238, 215, 331};
    HeapSort(nums);
    for_each(
        nums.cbegin(), nums.cend(), [&](int const & each) {
            cout << each << ", ";
        });
    cout << endl;
}