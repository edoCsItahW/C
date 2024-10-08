/*****************************************************
 * @File name: C
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/09/26 上午9:06
 * @Commend:
 *******************************************************/

#ifndef C_TEST_H
#define C_TEST_H
#pragma once


/** @brief 交换两个整数的值
 *
 * @param a 第一个整数
 * @param b 第二个整数
 * */
void swap(int* a, int* b);

/** @brief 快速排序
 *
 * @details 快速排序的分割
 *
 * @param arr 待排序数组
 * @param left 左边界
 * @param right 右边界
 * @return 分割点的位置
 * */
int partition(int arr[], int left, int right);

/** @brief 快速排序
 *
 * @example
 *      int arr[] = {5, 2, 8, 3, 9, 1}; \n
 *      int n = sizeof(arr) / sizeof(arr[0]); \n
 *      quickSort(arr, 0, n - 1);
 *
 * @param arr 待排序数组
 * @param left 左边界
 * @param right 右边界
 * */
void quickSort(int arr[], int left, int right);

/** @brief 冒泡排序
 *
 * @example
 *      int arr[] = {5, 2, 8, 3, 9, 1}; \n
 *      int n = sizeof(arr) / sizeof(arr[0]); \n
 *      bubbleSort(arr, n);
 *
 * @details
 *      1. 冒泡排序是一种非常容易理解的排序 \n
 *      2. 时间复杂度: O(N^2) (最坏情况) \n
 *      3. 空间复杂度: O(1) (不使用额外空间) \n
 *      4. 稳定性: 稳定
 *
 * @param arr 待排序数组
 * @param n 数组长度
 * */
void bubbleSort(int arr[], int n);

/** @brief 希尔排序
 *
 * @example
 *      int arr[] = {5, 2, 8, 3, 9, 1}; \n
 *      int n = sizeof(arr) / sizeof(arr[0]); \n
 *      shellSort(arr, n);
 *
 * @details
 *      1. 希尔排序是对直接插入排序的优化  \n
 *      2. 当gap > 1时都是预排序,目的是让数组更接近于有序.当gap == 1时,数组已经接近有序的了,这样就会很快,这样整体而言,可以达到优化的效果.我们实现后可以进行性能测试的对比  \n
 *      3. 希尔排序的时间复杂度不好计算,因为gap的取值方法很多,一般来说为O(n^1.3)   \n
 *      4. 稳定性: 不稳定
 *
 * @note
 *      1. 最开始gap为10(gap) / 2 = 5,那么有5组,对每一组中的2个进行插排   \n
 *      2. 然后5(上一个等式结果) / 2 = 2,那么有2组,对每组中的5个进行插排   \n
 *      3. 最后2(上一个等式结果) / 2 = 1,那么有1组,对每组中的10个进行插排(此时数组已经大致有序了,符合插排的越有序越快的特点)   \n
 *
 * @param arr 待排序数组
 * @param n 数组长度
 * */
void shellSort(int arr[], int n);

/** @brief 选择排序
 *
 * @example
 *      int arr[] = {5, 2, 8, 3, 9, 1}; \n
 *      int n = sizeof(arr) / sizeof(arr[0]); \n
 *      selectionSort(arr, n);
 *
 * @details
 *      1. 元素集合越接近有序,直接插入排序算法的时间效率越高 \n
 *      2. 时间复杂度: O(N^2) (最坏情况) \n
 *      3. 空间复杂度: O(1),它是一种稳定的排序算法 \n
 *      4. 稳定性: 稳定
 *
 * @param arr 待排序数组
 * @param n 数组长度
 * */
void insertSort(int arr[], int n);

/** @brief 选择排序
 *
 * @example
 *      int arr[] = {5, 2, 8, 3, 9, 1}; \n
 *      int n = sizeof(arr) / sizeof(arr[0]); \n
 *      selectionSort(arr, n);
 *
 * @details
 *      1. 直接选择排序思考非常好理解,但是效率不是很好.实际中很少使用
 *      2. 时间复杂度: O(N^2)
 *      3. 空间复杂度: O(1)
 *      4. 稳定性: 不稳定
 *
 * @param arr 待排序数组
 * @param n 数组长度
 * */
void selectSort(int arr[], int n);

/** @brief 堆排序
 *
 * @param arr 待排序数组
 * @param n 数组长度
 * */
void heapify(int arr[], int n, int i);

/** @brief 堆排序
 *
 * @example
 *      int arr[] = {5, 2, 8, 3, 9, 1}; \n
 *      int n = sizeof(arr) / sizeof(arr[0]); \n
 *      heapSort(arr, n);
 *
 * @param arr 待排序数组
 * @param n 数组长度
 */
void heapSort(int arr[], int n);

/** @brief 归并排序
 *
 * @param arr 待排序数组
 * @param left 左边界
 * @param mid 中间位置
 * @param right 右边界
 */
void merge(int arr[], int left, int mid, int right);

/** @brief 归并排序
 *
 * @example
 *      int arr[] = {5, 2, 8, 3, 9, 1}; \n
 *      int n = sizeof(arr) / sizeof(arr[0]); \n
 *      mergeSort(arr, 0, n - 1);
 *
 * @param arr 待排序数组
 * @param left 左边界
 * @param right 右边界
 * */
void mergeSort(int arr[], int left, int right);

/** @brief 快速幂算法
 *
 * @details
 *      快速幂算法是指利用递归的方法求解幂运算.在如模乘法逆元有运用.
 *      时间复杂度: O(logN)
 *      空间复杂度: O(logN)
 *
 * @note 该函数为递归版本
 *
 * @param x 底数
 * @param n 指数
 * @return x^n
 */
long long binPowR(int x, int n);

/** @brief 快速幂算法
 *
 * @details
 *      快速幂算法是指利用递归的方法求解幂运算.
 *      时间复杂度: O(logN)
 *      空间复杂度: O(1)
 *
 * @note 该函数为迭代版本
 *
 * @param x 底数
 * @param n 指数
 * @return x^n
 */
long long binPowI(int x, int n);

#endif  // C_TEST_H
