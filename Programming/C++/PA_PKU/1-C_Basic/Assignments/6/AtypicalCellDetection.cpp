/**
 * C程序中的数组 数组应用练习 编程题 #5：异常细胞检测
 *
 * @file: AtypicalCellDetection.cpp
 * @description: 我们拍摄的一张CT照片用一个二维数组来存储，假设数组中的每个点代表一个细胞。每个细
                胞的颜色用0到255之间（包括0和255）的一个整数表示。我们定义一个细胞是异常细胞，如
                果这个细胞的颜色值比它上下左右4个细胞的颜色值都小50以上（包括50）。数组边缘上的
                细胞我们不检测。现在我们的任务是，给定一个存储CT照片的二维数组，写程序统计照片中
                异常细胞的数目。
 * @input: 第一行包含一个整数N（100>=N>2）.下面有 N 行，每行有 N 个0~255之间的整数，整数之间用空格隔开
 * @output: 输出只有一行，包含一个整数，为异常细胞的数目。
 * 样例输入
    4
    70 70 70 70
    70 10 70 70
    70 70 20 70
    70 70 70 70
 * 样例输出
    2
 *
 * @author: Du Ang
 * @date: Apr. 7th, 2017
 */

 #include <iostream>

 using namespace std;

 int main(int argc, char *argv[])
 {
     int n;      // 数组为n行n列
     const int N = 100;  // 二维数组的最大维数N*N
     int a[N][N] = {0};  // 定义二维数组，并初始化为全0
     int counts = 0; // 统计异常细胞的个数
     cin >> n;
     for (int i = 0; i < n; i++) {
         for (int j = 0; j < n; j++) {
             cin >> a[i][j];     // 输入数组元素
         }
     }

     // 检查异常细胞
     for (int i = 1; i < n-1; i++) {
         for (int j = 1; j < n-1; j++) {
             if (a[i][j] <= a[i-1][j] - 50 && a[i][j] <= a[i][j-1] - 50
                 && a[i][j] <= a[i+1][j] - 50 && a[i][j] <= a[i][j+1] - 50) {
                 counts++;
             }
         }
     }
     cout << counts << endl;

     return 0;
 }
