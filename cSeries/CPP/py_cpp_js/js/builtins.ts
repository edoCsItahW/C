/*
 * Copyright (c) 2024. All rights reserved.
 * This source code is licensed under the CC BY-NC-SA
 * (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
 * This software is protected by copyright law. Reproduction, distribution, or use for commercial
 * purposes is prohibited without the author's permission. If you have any questions or require
 * permission, please contact the author: 2207150234@st.sziit.edu.cn
 */
// @ts-ignore
import builtins from "../build/Release/bridging.node";


export namespace Builtins {
    /*
    * @brief 该类包装了Python的内置对象object,并提供了一些常用的方法.
    * */
    export class PyObject {
        // @ts-ignore
        #instance: Proxy;

        /*
        * @brief 构造函数,传入参数作为Python的内置对象object的参数.
        * @param args Python的内置对象object的参数.
        * @note Python的内置对象object作为所有类的基类,所有不应接受任何参数.
        * */
        constructor(...args: any[]) {
            // @ts-ignore
            this.#instance = new Proxy(new builtins.PyObject(...args), {
                get: (t: builtins.PyObject, k: string) => { return t.get(k) },
                set: (t: builtins.PyObject, k: string, v: any) => { return t.set(k, v) }
            })
        }
        get __doc__(): string { return this.#instance.__doc__; }
        get __dir__(): () => string[] { return this.#instance.__dir__; }
        get __str__(): () => string { return this.#instance.__str__; }
        get __repr__(): () => string { return this.#instance.__repr__; }
        get __hash__(): () => number { return this.#instance.__hash__; }
        get __getattribute__(): () => (name: string) => any { return this.#instance.__getattribute__; }
    }
    export function pyImport(name: string) {
        return builtins.pyImport(name);
    }
}
