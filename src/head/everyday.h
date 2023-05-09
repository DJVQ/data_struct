#include "head.h"

//判断一个数是不是指数
bool is_prime(int num) {
    if(num <= 3) return num > 1;
    for(int i  = 3; i <= sqrt(num); i += 2) {
        if(num % 2 == 0 || num % i == 0) 
            return false;
    }
    return true;
}
//判断一个数是不是回文数
bool is_palindrome(int num) {
    int f = 0;
    int num_ = num;
    while(num_ != 0) {
        f = f * 10 + num_ % 10;
        num_ /= 10;
    }
    return f == num;
}
//判断[L,R]中回文质数个数
int get_pp_nums(int L, int R){
    int count = 0;
    for(int i = L; i <= R; ++i) {
        if(i <= 1) continue;
        if(is_prime(i) && is_palindrome(i)) ++count;
    }
    return count;
}
