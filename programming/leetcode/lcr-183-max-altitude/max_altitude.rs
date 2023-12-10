// @problem: LCR 183. 望远镜中最高的海拔
// @file: max_altitude.rs
// @url: https://leetcode-cn.com/problems/hua-dong-chuang-kou-de-zui-da-zhi-lcof
// @description:
//
// 科技馆内有一台虚拟观景望远镜，它可以用来观测特定纬度地区的地形情况。该纬度的海拔数据记于数组 heights ，其中 heights[i]
// 表示对应位置的海拔高度。请找出并返回望远镜视野范围 limit 内，可以观测到的最高海拔值。
// 示例 1：
//
// 输入：heights = [14,2,27,-5,28,13,39], limit = 3
// 输出：[27,27,28,28,39]
// 解释：
//   滑动窗口的位置                最大值
// ---------------               -----
// [14 2 27] -5 28 13 39          27
// 14 [2 27 -5] 28 13 39          27
// 14 2 [27 -5 28] 13 39          28
// 14 2 27 [-5 28 13] 39          28
// 14 2 27 -5 [28 13 39]          39
// 提示：
// 你可以假设输入总是有效的，在输入数组不为空的情况下：
//
// 1 <= limit <= heights.length
// -10000 <= heights[i] <= 10000
//
// 注意：本题与主站 239 题相同：https://leetcode-cn.com/problems/sliding-window-
// maximum/
//
// @author: Du Ang
// @date: Dec 10, 2023

// 暴力法
impl Solution1 {
    fn find_max_in_window(window: Vec<i32>) -> i32 {
        let mut max_value = window[0];
        for i in 1..window.len() {
            if window[i] > max_value {
                max_value = window[i];
            }
        }
        return max_value;
    }

    pub fn max_altitude(heights: Vec<i32>, limit: i32) -> Vec<i32> {
        if heights.len() == 0 || limit == 0 {
            return vec![];
        }
        let mut window: Vec<i32> = vec![];
        for height in heigts {
            window.push(height);
            if len(window) < limit {
                continue;
            } else {
                max_value = self.find_max_in_window(window);
                result.push(max_value);
                if len(window) >= limit {
                    window = window.drain(1..);
                }
            }
        }
        return result;
    }
}

// 优先队列（大根堆）
struct MaxPQ {
    size: usize,
    data: Vec<(i32, usize)>,
}

impl MaxPQ {
    fn new() -> MaxPQ {
        MaxPQ { size: 0, data: vec![(0, 0)] }
    }

    // 比较方法
    fn less(&self, i: usize, j: usize) -> bool {
        self.data[i].0 < self.data[j].0
    }

    // 交换方法
    fn exch(&mut self, i: usize, j: usize) {
        let temp = self.data[i];
        self.data[i] = self.data[j];
        self.data[j] = temp;
    }

    // 上浮方法
    fn swim(&mut self, k: usize) {
        let mut ik = k;
        while ik > 1 && self.less(ik / 2, ik) {
            self.exch(ik / 2, ik);
            ik = ik / 2;
        }
    }

    // 下沉方法
    fn sink(&mut self, k: usize) {
        let mut ik = k;
        while ik * 2 <= self.size {
            // 令 j 为 k 的两个孩子中较大的一个
            let mut j = ik * 2;
            if j < self.size && self.less(j, j + 1) {
                j += 1;
            }
            if !self.less(ik, j) {
                break;
            }
            self.exch(j, ik);
            ik = j;
        }
    }

    // 获取队列大小
    pub fn size(&self) -> usize {
        self.size
    }

    // 获取最大值
    pub fn get_max(&self) -> (i32, usize) {
        if self.size() == 0 {
            panic!("The priority queue is empty");
        }
        return self.data[1];
    }

    // 添加元素
    pub fn insert(&mut self, value: (i32, usize)) {
        self.data.push(value);
        self.size += 1;
        self.swim(self.size);
    }

    // 删除最大值
    pub fn del_max(&mut self) -> (i32, usize) {
        self.exch(1, self.size);
        let value = self.data.remove(self.size);
        self.size -= 1;
        self.sink(1);
        value
    }
}

// 使用自定义的优先队列（大根堆）
impl Solution2 {
    pub fn max_altitude(heights: Vec<i32>, limit: i32) -> Vec<i32> {
        if heights.len() == 0 || limit == 0 {
            return vec![];
        }

        let mut pq = MaxPQ::new();
        for i in 0..limit as usize {
            pq.insert((heights[i], i));
        }

        let mut result = vec![];
        result.push(pq.get_max().0);

        for i in limit as usize..heights.len() {
            pq.insert((heights[i], i));
            loop {
                let max_idx = pq.get_max().1;
                // NOTE: Be careful of usize overflow
                if max_idx + (limit as usize) <= i {
                    pq.del_max();
                } else {
                    break;
                }
            }
            result.push(pq.get_max().0);
        }
        result
    }
}

use std::collections::BinaryHeap;

// 使用官方库的优先队列（二叉堆）
impl Solution3 {
    pub fn max_altitude(heights: Vec<i32>, limit: i32) -> Vec<i32> {
        if heights.len() == 0 || limit == 0 {
            return vec![];
        }

        let mut pq = BinaryHeap::new();
        for i in 0..limit as usize {
            pq.push((heights[i], i));
        }

        let mut result = vec![];
        result.push(pq.peek().unwrap().0);

        for i in limit as usize..heights.len() {
            pq.push((heights[i], i));
            loop {
                let max_idx = pq.peek().unwrap().1;
                if max_idx + (limit as usize) <= i {
                    pq.pop().unwrap();
                } else {
                    break;
                }
            }
            result.push(pq.peek().unwrap().0);
        }
        return result;
    }
}

// 单调队列
impl Solution {
    pub fn max_altitude(heights: Vec<i32>, limit: i32) -> Vec<i32> {
        if heights.len() == 0 || limit == 0 {
            return vec![];
        }

        let mut deque = vec![];
        let mut result = vec![];
        // 未形成窗口时
        for i in 0..limit as usize {
            while deque.len() > 0 && heights[i] > deque[deque.len() - 1] {
                deque.remove(deque.len() - 1);
            }
            deque.push(heights[i]);
        }
        result.push(deque[0]);
        // 形成窗口后
        for i in limit as usize..heights.len() {
            // 将 heights[i-limit] 从 deque 中移除
            if deque[0] == heights[i - (limit as usize)] {
                deque.remove(0);
            }
            while deque.len() > 0 && heights[i] > deque[deque.len() - 1] {
                deque.remove(deque.len() - 1);
            }
            deque.push(heights[i]);
            result.push(deque[0]);
        }
        return result;
    }
}
