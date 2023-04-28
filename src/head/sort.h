#include "head.h"

//打印数组元素
template <typename T, unsigned N>
void printArr(T (&arr)[N]) {
    for(int i = 0; i < N; ++i) {
        cout<<arr[i]<<"\t";
        if (i % 10 == 9) cout<<endl;
    }
}

//生成随机数组
template <unsigned N>
void randomIntArr(int (&arr)[N], int rangeL, int rangeR) {
    default_random_engine dre;
    uniform_int_distribution<int> u(rangeL, rangeR);
    for (int i = 0; i < N; ++i) {
        arr[i] = u(dre);
    }
}

//交换数组元素
template <typename T>
void swap_(T &a, T &b) {
    int temp = a;
    a = b;
    b = temp;
}

//冒泡
template <typename T, unsigned N>
void bubleSort(T (&arr)[N]) {
    bool isSwap = true;
    for(int i = N - 1; i > 0 && isSwap; --i) {
        isSwap = false;
        for(int j = 0; j < i; ++j)
            if(arr[j] > arr[j+1]){
                swap_(arr[j], arr[j+1]);
                isSwap = true;
            }
    }
}

//选择
template <typename T, unsigned N>
void selectSort(T (&arr)[N]) {
    int temp_index;
    for(int i = 0; i < N - 1; ++i) {
        temp_index = i;
        for(int j = i; j < N; ++j) 
            if(arr[j] < arr[temp_index]) temp_index = j;
        swap(arr[i], arr[temp_index]);
    }
}

//插入
template <typename T, unsigned N>
void insertSort(T (&arr)[N]) {
    int temp, j;
    for (int i = 1; i < N; ++i) {
        temp = arr[i];
        for(j = i - 1; j >= 0 && arr[j] > temp; j--) 
            arr[j + 1] = arr[j];
        arr[j+1] = temp;
    }
}

template <typename T, unsigned N>
void merge(T (&arr)[N], int left, int mid, int right) {
    int n = right - left + 1;
    T temp_arr[n];
    int i = left, j = mid + 1, index = 0;
    while(i <= mid && j <= right) 
        temp_arr[index++] = (arr[i] <= arr[j]) ? arr[i++] : arr[j++];
    while(i <= mid) temp_arr[index++] = arr[i++];
    while(j <= right) temp_arr[index++] = arr[j++];
    for (int k = 0; k < n; ++k) arr[left + k] = temp_arr[k];
}

//归并
template <typename T, unsigned N>
void merge_sort(T (&arr)[N], int left, int right) {
    if (left >= right) return;
    int mid = (left + right)/2;
    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}
template <typename T, unsigned N>
void mergeSort(T (&arr)[N]) {
    merge_sort(arr, 0, N - 1);
}
template <typename T, unsigned N>
T quick(T (&arr)[N], int left, int right) {
    /*mid_index取随机值
    default_random_engine dre;
    uniform_int_distribution<int> u(left, right);
    swap_(arr[left], arr[u(dre)]);
    */
    int mid_index = left;
    for (int i = left + 1; i <= right; ++i) 
        if (arr[i] < arr[left]) swap_(arr[i], arr[++mid_index]);
    swap_(arr[left], arr[mid_index]);
    return mid_index;
}

//快速
template <typename T, unsigned N>
void quick_sort(T (&arr)[N], int left, int right) {
    if (left >= right) return;
    int mid_index = quick(arr, left, right);
    quick_sort(arr, left, mid_index - 1);
    quick_sort(arr, mid_index + 1, right);
}
template <typename T, unsigned N>
void quickSort(T (&arr)[N]) {
    quick_sort(arr, 0, N - 1);
}
template <typename T, unsigned N>
void shellSort(T (&arr)[N]) {
    int i, j, temp;
    int gap = N;
    do {
        gap = gap / 3 + 1;
        for(i = gap; i < N; i += gap) {
            temp = arr[i];
            for(j = i - gap; j >= 0 && arr[j] > temp; j -= gap) 
                arr[j + 1] = arr[j];
            arr[j+1] = temp;
        }
    } while(gap > 1);
}

//堆
template <typename T, unsigned N>
void max_heapify(T (&arr)[N], int start, int end) {
    int current = start;
    int child = (current<<1)+1;
    while (child <= end) {
        if(child < end && arr[child] < arr[child+1]) ++child;
        if(arr[current] > arr[child]){
            return;
        } else{
            swap_(arr[current], arr[child]);
            current = child;
            child = (current<<1)+1;
        }
    }
}
template <typename T, unsigned N>
void heapSort(T (&arr)[N]) {
    int i;
    for(i = (N>>1)-1; i >= 0; --i) max_heapify(arr, i, N-1);
    for(i = N-1; i > 0; --i) {
        swap_(arr[0], arr[i]);
        max_heapify(arr, 0, i-1);
    }
}

//计数
template <typename T, unsigned N>
void countSort(T (&arr)[N]) {
    int max = arr[0], min = arr[0], i;
    for(i = 1; i < N; ++i) {
        if(max < arr[i]) max = arr[i];
        if(min > arr[i]) min = arr[i];
    }
    int length = max-min+1;
    T count[length];
    fill(count, count + length, 0);
    for(i = 0; i < N; ++i) ++count[arr[i]];
    for(int k = 0, i = 0; k < length; ++k) 
        while(count[k]){
            arr[i++] = k;
            --count[k];
        }
}

//桶
template <typename T, unsigned N>
void bucketSort(T (&arr)[N]) {
    int max = arr[0], min = arr[0], i, j, index;
    for(i = 1; i < N; ++i) {
        if(max < arr[i]) max = arr[i];
        if(min > arr[i]) min = arr[i];
    }
    int gap = (max-min)/N+1;
    int bucket_num = (max-min)/gap+1;
    vector<T> bucket[bucket_num];
    for(i = 0; i < N; ++i) 
        bucket[(arr[i]-min)/gap].push_back(arr[i]);
    for(i = 0; i < bucket_num; ++i) 
        if(bucket[i].size() > 0) 
            sort(bucket[i].begin(), bucket[i].end());
    for(i = 0; i < bucket_num; ++i) 
        for(j = 0; j < bucket[i].size(); ++j) 
            arr[index++] = bucket[i][j];
}

//基数
template <typename T, unsigned N>
void radixSort(T (&arr)[N]) {
    vector<T> base_[10];
    int i, j, arr_index, base_till;
    int n = 1 + (int)log10(*max_element(arr, arr + N));
    for(i = 0; i < n; ++i) {
        for(j = 0; j < N; ++j) 
            base_[(arr[j]/(int)pow(10, i))%10].push_back(arr[j]);
        arr_index = 0;        
        for(j = 0; j < 10; ++j) {
            sort(base_[j].rbegin(), base_[j].rend());
            base_till = base_[j].size() - 1;
            while(base_[j].size() > 0) {
                arr[arr_index++] = base_[j][base_till--];
                base_[j].pop_back();
            }
        }
    }
}