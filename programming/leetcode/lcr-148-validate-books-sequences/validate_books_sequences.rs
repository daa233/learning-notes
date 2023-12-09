// @problem: LCR 148. 验证图书取出顺序
// @file: validate_books_sequences.rs
// @url: https://leetcode-cn.com/problems/zhan-de-ya-ru-dan-chu-xu-lie-lcof
// @description:
//
// 现在图书馆有一堆图书需要放入书架，并且图书馆的书架是一种特殊的数据结构，只能按照 一定 的顺序 放入 和 拿取 书籍。
// 给定一个表示图书放入顺序的整数序列 putIn，请判断序列 takeOut
// 是否为按照正确的顺序拿取书籍的操作序列。你可以假设放入书架的所有书籍编号都不相同。
// 示例 1：
//
// 输入：putIn = [6,7,8,9,10,11], takeOut = [9,11,10,8,7,6]
// 输出：true
// 解释：我们可以按以下操作放入并拿取书籍：
// push(6), push(7), push(8), push(9), pop() -> 9,
// push(10), push(11),pop() -> 11,pop() -> 10, pop() -> 8, pop() -> 7,
// pop() -> 6
//
// 示例 2：
//
// 输入：putIn = [6,7,8,9,10,11], takeOut = [11,9,8,10,6,7]
// 输出：false
// 解释：6 不能在 7 之前取出。
//
// 提示：
//
// 0 <= putIn.length == takeOut.length <= 1000
// 0 <= putIn[i], takeOut < 1000
// putIn 是 takeOut 的排列。
//
// 注意：本题与主站 946 题相同：https://leetcode-cn.com/problems/validate-stack-
// sequences/
//
// @author: Du Ang
// @date: Dec 09, 2023

impl Solution {
    pub fn validate_book_sequences(put_in: Vec<i32>, take_out: Vec<i32>) -> bool {
        assert!(put_in.len() == take_out.len());
        if put_in.len() == 0 {
            true;
        }

        let mut stack: Vec<i32> = vec![];
        let mut i: usize = 0;
        for num in take_out {
            loop {
                match stack.last() {
                    Some(&value) => {
                        if value == num {
                            // the stack is not empty and the top is num, pop it out and break the loop
                            stack.pop();
                            break;
                        } else {
                            // the stack is not empty but the top is not num, keep pushing
                            if i >= put_in.len() {
                                // exit the loop if no nums to push
                                break;
                            } else {
                                stack.push(put_in[i]);
                            }
                            i += 1;
                        }
                    }
                    None => {
                        // the stack is empty, keep pushing
                        stack.push(put_in[i]);
                        i += 1;
                    }
                }
            }
        }
        return stack.len() == 0;
    }
}
