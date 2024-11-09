// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/**
 * @file types.h
 * @author edocsitahw
 * @version 1.1
 * @date 2024/11/07 下午4:48
 * @brief 定义三次方程程式化计算器的数值类型
 * @copyright CC BY-NC-SA 2024. All rights reserved.
 * */
#ifndef C_TYPES_H
#define C_TYPES_H
#pragma once

#include <variant>
#include <string>
#include <ostream>

using Number = std::variant<int, float, double>;


extern bool LATEX_OUTPUT;


class Fraction {
private:
    // 分子
    int _numerator;
    // 分母
    int _denominator;

public:
    Fraction(int numerator, int denominator);
    static Fraction fromDecimal(double decimal);
    [[nodiscard]] std::string toString() const;
    [[nodiscard]] double value() const;
    void reduce();
    Fraction operator+(const Fraction& other) const;
    Fraction operator+(const Number& other) const;
    Fraction operator-(const Fraction& other) const;
    Fraction operator-(const Number& other) const;
    Fraction operator*(const Fraction& other) const;
    Fraction operator*(const Number& other) const;
    Fraction operator/(const Fraction& other) const;
    Fraction operator/(const Number& other) const;
    Fraction operator-() const;
    bool operator>(const Fraction& other) const;
    bool operator>(const Number& other) const;
    bool operator<(const Fraction& other) const;
    bool operator<(const Number& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Fraction& fraction);
};

/** @typedef IntExp
 * @todo 待支持指数
 * */
using IntExp = std::variant<int, Fraction>;

class Exponential {
    // 底数
    IntExp _base;
    // 指数
    IntExp _exponent;

public:
    Exponential(Number base, Number exponent);
    [[nodiscard]] std::string toString() const;
};

#include "types.hpp"

#endif  // C_TYPES_H
