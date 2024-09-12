// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

// -------------------------<edocsitahw>----------------------------
// ???????: 2024/05/08 ????7:51
// ????????: test
// ??????: utf-8
// ???:
// -------------------------<edocsitahw>----------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int method1(int start, int end) {
    int len = 1;

    int res;
    char str[100];

    while (res < end) {
        len++;

        for (int i = 0; i < len; i++) {
            for (int j = 1; j < 10; j++) {
                res += j * i * 10;
                res += j * (len - i) * 10;
                printf("%d\n", res);
            }

            printf("%d\n", res);
        }
        res = end + 1;
    }
}

int main() {
    method1(1, 1993);

    return 0;
}
