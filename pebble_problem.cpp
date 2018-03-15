// 好久没写C语言代码, 今天学习一个石子问题, 解决CCF的压缩编码的问题
// (1)有N堆石子，现要将石子有序的合并成一堆，规定如下：每次只能移动
// 相邻的2堆石子合并，合并花费为新合成的一堆石子的数量。求将这N堆石
// 子合并成一堆的总花费最小（或最大）。

// 什么是动态规划
// 动态规划常常采取从部分整体最优解的拆分来得到最优解法的递归式，我
// 们可以想到，此处是由2堆石子合并，所以最终最优解肯定是由两个局部
// 最优解的加上整体的和求得。
#include <stdio.h>
#define INIF 999999999
int dp[1001][1001] = {0};
int sum[1001][1001];
int num[1001];
int n;

void runDp();
int main(void) {
    FILE* fp = fopen("num.txt", "r");
    int i = 0;
    fscanf(fp, "%d", &n);
    // 设置一个长度为10001的数组
    // 将数据输入
    fp = fopen("data.txt", "r");

    for (i = 1; i <= n; i++) {
        fscanf(fp, "%d", &num[i]);
        // 数据进去了 printf("数据:%d\n", num[i]);
    }

    runDp();

    return 0;
}
void runDp() {
    int i, j, k, t, len, min;
    // 计算堆与堆之间的距离
    for (i = 1; i <= n; i++) {
        sum[i][i] = num[i];
        for (j = i+1; j <= n; j++) {
            // sum 是i到j-1 合并 所产生的花费 最后加上 合并[j]
            sum[i][j] = sum[i][j-1] + num[j];
        }
    }
    // 首先是长度
    for(j = 2; j <= n; j++) {
        // 从第一个开始算起, 这个长度下, 的最小值
        // 然后是从后往前算,
        // dp的意思好像是合并
        // sum的意思应该就是, 合并这两个堆, 不移动的花费, 只是中间过程
        // 才是我们要想的
        for(i = j-1; i >= 0; i--) {
            min = dp[i][j] = INIF;
            for(k = i; k < j; k++) {
                // k 在这里, 就是更新最小值的
                // 所以, 要把所有的遍历一遍,
                // dp[][]里的值都是最小的, 所以要从后往前
                t = dp[i][k] + dp[k+1][j] + sum[i][j];
                if(t < min) { min = t; }
            }
            dp[i][j] = min;
        }
    }
    printf("%d\n", dp[1][n]);
    return;
}
