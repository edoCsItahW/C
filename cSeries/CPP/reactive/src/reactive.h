// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: reactive
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/08/26 上午2:37
 * @Commend:
 *******************************************************/

#ifndef REACTIVE_REACTIVE_H
#define REACTIVE_REACTIVE_H
#pragma once

#include <functional>
#include <utility>
#include <vector>
#include <memory>
#include <map>
#include <optional>
#include <iostream>
#include <any>
#include <tuple>


class Dep;
class Effect;

namespace Global {
    extern std::any ACTIVE_EFFECT;
    extern std::map<std::string, std::pair<std::any
}

class Effect {
    using Fn = std::function<std::any(std::tuple<std::any>)>;
    private:
        Fn _func;

    public:
        std::vector<Dep*> deps;
        size_t idx = 0;
        size_t trackId = 0;

        explicit Effect(Fn  func) : _func(std::move(func)) {}

        std::any operator()(std::tuple<std::any>& args) {
            Global::ACTIVE_EFFECT = std::any(*this);
            trackId ++;
            idx = 0;
            return std::apply(_func, args);
        }
};

template<typename Return, typename... Args>
std::any createEffect(const Return(*func)(Args...)) {
    return std::any(Effect<Return, Args...>(func));
}

struct Dep : public std::map<std::any, size_t> {
      std::function<void()> cleanUp;
      explicit Dep(const std::function<void()>& cleanUp) : cleanUp(cleanUp) {}

      std::optional<size_t> operator[](const std::any& effect) {
          auto it = this->find(effect);
      }

      explicit operator bool() const { return !this->empty(); }
};

template<typename T>
class Ref {
    private:
        T _value;

    public:
        Dep* dep = nullptr;

        explicit Ref(const T& value) : _value(value) {}
        explicit Ref(T&& value) : _value(std::move(value)) {}

        T& operator*() { return _value; }
        Ref& operator=(const T& value) {
            _value = value;
            return *this;
        }
};

template<typename T>
void trackRef(const Ref<T>& ref) {
    if (Global::ACTIVE_EFFECT.has_value())
        track(Global::ACTIVE_EFFECT, ref.dep ? *ref.dep : Dep([&ref] { ref.dep = nullptr; }));
}

template<typename R>
void track(const std::any& effect, const Dep& dep) {
    if (dep.find(effect)->second != effect.an) {
        dep[effect] = effect.trackId;

        Dep<R>* oldDep;

        try {
            oldDep = effect.deps[effect.idx];
        } catch (const std::out_of_range&) { oldDep = nullptr; }
        if (oldDep != &dep) {
            if (oldDep) {
                if (oldDep->get(effect) != effect.trackId) {
                    oldDep->erase(effect);
                    if (oldDep->empty()) oldDep->cleanup();
                }
            }
            effect.deps.push_back(&dep);
        }
        effect.idx++;
    }
}

#endif  // REACTIVE_REACTIVE_H
