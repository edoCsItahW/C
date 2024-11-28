#  Copyright (c) 2024. All rights reserved.
#  This source code is licensed under the CC BY-NC-SA
#  (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
#  This software is protected by copyright law. Reproduction, distribution, or use for commercial
#  purposes is prohibited without the author's permission. If you have any questions or require
#  permission, please contact the author: 2207150234@st.sziit.edu.cn

from math import floor
from ast import parse


def gcd(a, b):
    return gcd(b, a % b) if b else a


def d2f(dec):
    den = 1  # 分母
    while dec != floor(dec):
        dec *= 10
        den *= 10
    num = floor(dec)  # 分子

    # 计算系数,如将11/5变为1又6/5
    coef, num = num // den, num % den

    return num / (div := gcd(num, den)), den / div, coef


print(d2f(0.2))

from warnings import warn

# warn(1)

from ast import NodeVisitor, AST


class MyVisitor(NodeVisitor):
    def visit_Add(self, node: AST):
        return


with open(__file__, 'r', encoding='utf-8') as file:
    ast = parse(file.read())
    visitor = MyVisitor()
    visitor.visit(ast)
