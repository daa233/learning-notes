// @problem: LCR 184. 设计自助结算系统
// @file: checkout.rs
// @url: https://leetcode-cn.com/problems/dui-lie-de-zui-da-zhi-lcof
// @description:
//
// 请设计一个自助结账系统，该系统需要通过一个队列来模拟顾客通过购物车的结算过程，需要实现的功能有：
//
// get_max()：获取结算商品中的最高价格，如果队列为空，则返回 -1
// add(value)：将价格为 value 的商品加入待结算商品队列的尾部
// remove()：移除第一个待结算的商品价格，如果队列为空，则返回 -1
//
// 注意，为保证该系统运转高效性，以上函数的均摊时间复杂度均为 O(1)
// 示例 1：
//
// 输入:
// ["Checkout","add","add","get_max","remove","get_max"]
// [[],[4],[7],[],[],[]]
//
// 输出: [null,null,null,7,4,7]
//
// 示例 2：
//
// 输入:
// ["Checkout","remove","get_max"]
// [[],[],[]]
//
// 输出: [null,-1,-1]
//
// 提示：
//
// 1 <= get_max, add, remove 的总操作数 <= 10000
// 1 <= value <= 10^5
//
// @author: Du Ang
// @date: Dec 10, 2023

struct Checkout1 {
    data: Vec<i32>,
    deque: Vec<i32>,
}

/**
 * 采用 Vec 模拟单调双端队列实现
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl Checkout1 {
    fn new() -> Self {
        Checkout {
            data: vec![],
            deque: vec![],
        }
    }

    // 获取结算商品中的最高价格，如果队列为空，则返回 -1
    fn get_max(&self) -> i32 {
        if self.deque.len() == 0 {
            return -1;
        }
        return self.deque[0];
    }

    // 将价格为 `value` 的商品加入待结算商品队列的尾部
    fn add(&mut self, value: i32) {
        self.data.push(value);
        // 移除 deque 尾部比 value 大的元素
        while let Some(&last_value) = self.deque.last() {
            if value > last_value {
                self.deque.pop();
                continue;
            } else {
                break;
            }
        }
        // 将 value 添加到 deque 尾部
        self.deque.push(value);
    }

    // 移除第一个待结算的商品价格，如果队列为空，则返回 -1
    fn remove(&mut self) -> i32 {
        if self.data.len() == 0 {
            return -1;
        }
        let value = self.data.remove(0);
        if value == self.deque[0] {
            self.deque.remove(0);
        }
        return value;
    }
}

use std::collections::VecDeque;

struct Checkout {
    data: VecDeque<i32>,
    deque: VecDeque<i32>,
}

/**
 * 采用 VecDeque 单调双端队列实现
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl Checkout {
    fn new() -> Self {
        Checkout {
            data: VecDeque::new(),
            deque: VecDeque::new(),
        }
    }

    // 获取结算商品中的最高价格，如果队列为空，则返回 -1
    fn get_max(&self) -> i32 {
        match self.deque.front() {
            Some(&value) => value,
            None => -1,
        }
    }

    // 将价格为 `value` 的商品加入待结算商品队列的尾部
    fn add(&mut self, value: i32) {
        self.data.push_back(value);
        // 移除 deque 尾部比 value 大的元素
        while let Some(&last_value) = self.deque.back() {
            if value > last_value {
                self.deque.pop_back();
                continue;
            } else {
                break;
            }
        }
        // 将 value 添加到 deque 尾部
        self.deque.push_back(value);
    }

    // 移除第一个待结算的商品价格，如果队列为空，则返回 -1
    fn remove(&mut self) -> i32 {
        match self.data.pop_front() {
            Some(value) => {
                if value == *self.deque.front().unwrap() {
                    self.deque.pop_front();
                }
                value
            }
            None => -1,
        }
    }
}


/**
 * Your Checkout object will be instantiated and called as such:
 * let obj = Checkout::new();
 * let ret_1: i32 = obj.get_max();
 * obj.add(value);
 * let ret_3: i32 = obj.remove();
 */

