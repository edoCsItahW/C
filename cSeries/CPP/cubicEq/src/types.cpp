// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/**
 * @file types.cpp
 * @author edocsitahw
 * @version 1.1
 * @date 2024/11/07 下午4:48
 * @brief
 * @copyright CC BY-NC-SA 2024. All rights reserved.
 * */
#include "types.h"
#include "mathUtils.h"

bool LATEX_OUTPUT = false;

Fraction::Fraction(int numerator, int denominator)
    : _numerator(numerator)
    , _denominator(denominator) {
    reduce();
}

void Fraction::reduce() {
    int divisor = gcd(_numerator, _denominator);
    _numerator /= divisor;
    _denominator /= divisor;
}

Fraction Fraction::fromDecimal(double decimal) {
    int denominator = 1;
    while (decimal != static_cast<int>(decimal)) {
        decimal *= 10;
        denominator *= 10;
    }
    int numerator = static_cast<int>(decimal);
    int divisor   = gcd(numerator, denominator);
    return {numerator / divisor, denominator / divisor};
}

double Fraction::value() const { return static_cast<double>(_numerator) / _denominator; }

Fraction Fraction::operator+(const Fraction& other) const { return {_numerator * other._denominator + _denominator * other._numerator, _denominator * other._denominator}; }

Fraction Fraction::operator+(const Number& other) const {
    if (std::holds_alternative<int>(other))
        return {_numerator + (std::get<int>(other) * _denominator), _denominator};
    else if (std::holds_alternative<float>(other))
        return fromDecimal(std::get<float>(other)) + *this;
    else if (std::holds_alternative<double>(other))
        return fromDecimal(std::get<double>(other)) + *this;
    else
        throw TypeError("Unsupported type for Number.");
}

Fraction Fraction::operator-(const Fraction& other) const { return {_numerator * other._denominator - _denominator * other._numerator, _denominator * other._denominator}; }

Fraction Fraction::operator-(const Number& other) const {
    if (std::holds_alternative<int>(other))
        return {_numerator - (std::get<int>(other) * _denominator), _denominator};
    else if (std::holds_alternative<float>(other))
        return fromDecimal(std::get<float>(other)) - *this;
    else if (std::holds_alternative<double>(other))
        return fromDecimal(std::get<double>(other)) - *this;
    else
        throw TypeError("Unsupported type for Number.");
}

Fraction Fraction::operator*(const Fraction& other) const { return {_numerator * other._numerator, _denominator * other._denominator}; }

Fraction Fraction::operator*(const Number& other) const {
    if (std::holds_alternative<int>(other))
        return {_numerator * std::get<int>(other), _denominator};
    else if (std::holds_alternative<float>(other))
        return fromDecimal(std::get<float>(other)) * *this;
    else if (std::holds_alternative<double>(other))
        return fromDecimal(std::get<double>(other)) * *this;
    else
        throw TypeError("Unsupported type for Number.");
}

Fraction Fraction::operator/(const Fraction& other) const { return {_numerator * other._denominator, _denominator * other._numerator}; }

Fraction Fraction::operator/(const Number& other) const {
    if (std::holds_alternative<int>(other))
        return {_numerator, _denominator * std::get<int>(other)};
    else if (std::holds_alternative<float>(other))
        return fromDecimal(std::get<float>(other)) / *this;
    else if (std::holds_alternative<double>(other))
        return fromDecimal(std::get<double>(other)) / *this;
    else
        throw TypeError("Unsupported type for Number.");
}

Fraction Fraction::operator-() const { return {-_numerator, _denominator}; }

bool Fraction::operator>(const Fraction& other) const { return value() > other.value(); }

bool Fraction::operator>(const Number& other) const {
    if (std::holds_alternative<int>(other))
        return value() > static_cast<double>(std::get<int>(other));
    else if (std::holds_alternative<float>(other))
        return value() > std::get<float>(other);
    else if (std::holds_alternative<double>(other))
        return value() > std::get<double>(other);
    else
        throw TypeError("Unsupported type for Number.");
}

bool Fraction::operator<(const Fraction& other) const { return value() < other.value(); }

bool Fraction::operator<(const Number& other) const {
    if (std::holds_alternative<int>(other))
        return value() < static_cast<double>(std::get<int>(other));
    else if (std::holds_alternative<float>(other))
        return value() < std::get<float>(other);
    else if (std::holds_alternative<double>(other))
        return value() < std::get<double>(other);
    else
        throw TypeError("Unsupported type for Number.");
}

std::string Fraction::toString() const {
    return LATEX_OUTPUT ? "\\frac{" + std::to_string(_numerator) + "}{" + std::to_string(_denominator) + "}" : std::to_string(_numerator) + "/" + std::to_string(_denominator);
}

std::ostream& operator<<(std::ostream& os, const Fraction& fraction) {
    os << fraction.toString();
    return os;
}

Exponential::Exponential(Number base, Number exponent) {
    if (std::holds_alternative<int>(base))
        _base = std::get<int>(base);
    else if (std::holds_alternative<float>(base))
        _base = Fraction::fromDecimal(std::get<float>(base));
    else if (std::holds_alternative<double>(base))
        _base = Fraction::fromDecimal(std::get<double>(base));
    else
        throw TypeError("Unsupported type for base.");

    if (std::holds_alternative<int>(exponent))
        _exponent = std::get<int>(exponent);
    else if (std::holds_alternative<float>(exponent))
        _exponent = Fraction::fromDecimal(std::get<float>(exponent));
    else if (std::holds_alternative<double>(exponent))
        _exponent = Fraction::fromDecimal(std::get<double>(exponent));
    else
        throw TypeError("Unsupported type for exponent.");
}

std::string Exponential::toString() const {
    std::string baseStr;
    if (std::holds_alternative<int>(_base))
        if
    return LATEX_OUTPUT ? }
