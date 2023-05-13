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


//找到与对应负数同时存在的最大正整数
int findMaxK(vector<int>& nums) {
    unordered_set<int> set_;
    int max = -1;
    for (int i = 0; i < nums.size(); ++i) {
        if (!set_.count(-nums[i])) {
            set_.insert(nums[i]);
        }
        else {
            if (abs(nums[i]) > max) {
                max = abs(nums[i]);
            }
        }
    }
    return max;
}

//寻找两个正序数组的中位数
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int s1 = nums1.size(), s2 = nums2.size();
    int s = s1 + s2, index = 0, pre_val = -1, cur_val = -1;
    for (int i = 0, j = 0; i < s1 || j < s2;) {
        pre_val = cur_val;
        if (i == s1) {
            for (int k = j; k < s2; ++index) {
                if (index == s / 2 + 1) break;
                pre_val = cur_val;
                cur_val = nums2[k++];
            }
            break;
        }else if (j == s2) {
            for (int l = i; l < s1; ++index) {
                if (index == s / 2 + 1) break;
                pre_val = cur_val;
                cur_val = nums1[l++];
            }
            break;
        }
        if (nums1[i] < nums2[j]) {
            cur_val = nums1[i++];
            ++index;
        } else {
            cur_val = nums2[j++];
            ++index;
        }
        if (index == s / 2 + 1) break;
    }
    return s % 2 == 0 ? (pre_val + cur_val) / 2.0 : cur_val;
}