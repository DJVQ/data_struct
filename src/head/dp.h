#include "head.h"

int count_ = 0;
//青蛙问题_递归
int count_ways_r(int n) {
    cout<<"count: "<<++count_<<endl;
    if(n == 1)
        return 1;
    if(n == 2)
        return 2;
    return count_ways_r(n - 1) + count_ways_r(n - 2);
} 

//青蛙问题_递归优化
int count_ways_u_l(int first, int second, int n) {
    if(n >= 3) 
        return count_ways_u_l(second, first + second, n - 1);
    else if (n == 2) 
        return second;
    return first;
} 

//青蛙问题_循环
int count_ways_u(int n) {
    if (n<= 1) {
        return 1;
    }
    if (n == 2) {
        return 2;
    }
    int a = 1, b = 2, temp = 0;
    for (int i = 3; i <= n; i++) {
        temp = a + b;
        a = b;
        b = temp;
    }
    return temp;
} 