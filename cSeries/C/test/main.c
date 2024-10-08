/*****************************************************
 * @File name: C
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/09/26 上午9:07
 * @Commend:
 *******************************************************/

#include "stdio.h"
#include "test.h"

void reverse(int arr[], int n) {
    for (int i = 0; i < n / 2; i++) {
        arr[i] ^= arr[n - i - 1];
        arr[n - i - 1] ^= arr[i];
        arr[i] ^= arr[n - i - 1];
    }
}

int main() {
    int arr[] = {92, 85, 66, 89, 89, 95, 79};
    reverse(arr, sizeof(arr) / sizeof(arr[0]));
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        printf("%d ", arr[i]);
    }
    return 0;
}