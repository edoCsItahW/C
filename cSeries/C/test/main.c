/**
 * @file main.c
 * @author edocsitahw
 * @version 1.1
 * @date 2024/09/26 上午9:07
 * @brief
 * @copyright CC
 **/

#include "stdio.h"
#include "test.h"

#define MAX_LEN 32

bool repeat(int num) {
    int count = 0, bitVec = 0, arr[MAX_LEN];
    while (num &= (num - 1)) count++;
    for (int i = 0; i < count; i++) if (bitVec & (1 << arr[i])) return true; else bitVec |= (1 << arr[i]);
    return false;
}

int main() {
    int num = 1, count = 0, res;
    while (res = (num++ * 11))
        if (!repeat(res) && res > 99) {
            count++;
            printf("%d\n", res);
        }
    return 0;
}