/**
 * @file: ChickensAndRabbits.cpp
 * @description: 鸡兔同笼问题，已知笼中脚总数，鸡兔总数至少几何？至多几何？
 * @solution: 全部是鸡的时候总数最多，全部是兔子时（也可能也有一只鸡）总数最少。
 *
 * @author: Du Ang
 * @date: Apr. 3rd, 2017
 */

 #include <iostream>
 #include <cstdlib>     // 为了使用atoi函数
 using namespace std;

void help();

// 用法示例   Usage: ./ChickenAndRabbit [case1] [case2] ...
void help()
{
    cout << "Usage: ./ChickenAndRabbit [case1] [case2] ...\n"
      << " All cases should be odds." << endl;
}

 int main(int argc, char *argv[])
 {
     int foots = 0; // 笼中脚的总数目
     int minSum = 0;    // 笼中动物总数目最小的可能值
     int maxSum = 0;    // 笼中动物总数目最大的可能值

     // 从命令参数或者输入获得笼中脚的总数目foots
     if (argc <= 1) {
         cout << "Error arguments!" << endl;
         help();
     } else {
         for (int i = 1; i < argc; i++) {
             foots = atoi(argv[i]); // 将输入参数由char转为int
             // 首先判断脚的数目是否为偶数
             if (foots % 2 != 0) {  // 脚的数目为奇数
                 cout << "0 0" << endl;   // 直接输出 0 0
             } else {   // 脚的数目为偶数
                 // 鸡兔总数最少时为全是兔子或一只鸡剩下的全是兔子
                 if (foots % 4 == 0) {
                     minSum = foots / 4;    // 全是兔子
                 } else {
                     minSum = foots / 4 + 1;    // 只有一只鸡，剩下的全是兔子
                 }
                 maxSum = foots / 2;    // 鸡兔总数最多时全是鸡
                 cout << minSum << " "<< maxSum << endl;
             }
         }
     }

     return 0;
 }
