// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: docSpawner
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/08/25 下午4:42
 * @Commend:
 *******************************************************/

#include "src/reactive.h"

int main() {
    auto ref = Ref<int>(1);
    auto inputEffect = Effect<void>(([&ref] {
        ref = 2;
    }));
    auto renderEffect = Effect<void>([&ref] {
        std::cout << "ref changed to: " << *ref << std::endl;
    });
    inputEffect();
    renderEffect();

    ref = 3;
}
