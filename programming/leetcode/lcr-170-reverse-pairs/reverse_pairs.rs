// @problem: LCR 170. 交易逆序对的总数
// @file: reverse_pairs.rs
// @url: https://leetcode-cn.com/problems/shu-zu-zhong-de-ni-xu-dui-lcof
// @description:
//
// 在股票交易中，如果前一天的股价高于后一天的股价，则可以认为存在一个「交易逆序对」。请设计一个程序，输入一段时间内的股票交易记录
// record，返回其中存在的「交易逆序对」总数。
// 示例 1:
//
// 输入：record = [9, 7, 5, 4, 6]
// 输出：8
// 解释：交易中的逆序对为 (9, 7), (9, 5), (9, 4), (9, 6), (7, 5), (7, 4), (7, 6),
// (5, 4)。
//
// 限制：
// 0 <= record.length <= 50000
//
// @author: Du Ang
// @date: Dec 18, 2023

struct Solution {}

// 归并排序
impl Solution {
    // 合并 [left, mid] 和 [mid + 1, right] 区间，并返回逆序对数目
    fn merge(nums: &mut Vec<i32>, left: usize, mid: usize, right: usize) -> i32 {
        let mut tmp_nums: Vec<i32> = vec![0; right - left + 1]; // 存放排序后的临时结果
        let mut i: usize = left;
        let mut j: usize = mid + 1;
        let mut reorder: i32 = 0;
        let mut count: usize = 0;

        while i <= mid && j <= right {
            if nums[i] > nums[j] {
                tmp_nums[count] = nums[j];
                // 从 [i, mid] 区间的每个数都和 j 索引的数构成了逆序对
                reorder += (mid - i + 1) as i32;
                j += 1;
            } else {
                tmp_nums[count] = nums[i];
                i += 1;
            }
            count += 1;
        }

        // 某个区间已经遍历完毕，将另一个区间剩余的所有数字拷贝到临时结果里
        while i <= mid {
            tmp_nums[count] = nums[i];
            count += 1;
            i += 1;
        }
        while j <= right {
            tmp_nums[count] = nums[j];
            count += 1;
            j += 1;
        }

        // 将最终结果拷贝到合并后的 nums 的 [left, right] 区间
        for index in left..right + 1 {
            nums[index] = tmp_nums[index - left];
        }

        return reorder;
    }

    // 对 [left, right] 区间执行归并排序，并返回逆序对数目
    fn merge_sort(nums: &mut Vec<i32>, left: usize, right: usize) -> i32 {
        if left >= right {
            return 0;
        }
        // 将 [left, right] 区间分为 [left, mid] 和 [mid + 1, right]
        let mid = (left + right) / 2;
        let res_left = Solution::merge_sort(nums, left, mid);
        let res_right = Solution::merge_sort(nums, mid + 1, right);
        let res_merge = Solution::merge(nums, left, mid, right);
        return res_left + res_right + res_merge;
    }

    pub fn reverse_pairs(record: Vec<i32>) -> i32 {
        let mut ordered_record: Vec<i32> = record.clone();
        if record.len() == 0 {
            return 0;
        } else {
            return Solution::merge_sort(&mut ordered_record, 0, record.len() - 1);
        }
    }
}

fn main() {
    let record = vec![9, 7, 5, 4, 6];
    let res = Solution::reverse_pairs(record);
    assert_eq!(res, 8);
}
