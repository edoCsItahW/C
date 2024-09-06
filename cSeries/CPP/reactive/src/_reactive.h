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

#ifndef DOCSPAWNER_REACTIVE_H
#define DOCSPAWNER_REACTIVE_H
#pragma once

#include <any>
#include <functional>
#include <iostream>
#include <map>
#include <optional>
#include <unordered_map>
#include <vector>

template<typename R>
class Dep;
template<typename R, typename... Args>
class Effect;

namespace Global {
    template<typename R, typename... Args>
    extern Effect<R, Args...> ACTIVE_EFFECT;
}

template<typename R, typename... Args>
class Effect {
        using Fn = std::function<R(Args...)>;

    private:
        Fn _func;

    public:
        std::vector<Dep<R>*> deps{};
        size_t idx     = 0;
        size_t trackId = 0;

        explicit Effect(const Fn& func) : _func(func) {}

        R operator()() {
            try {
                Global::ACTIVE_EFFECT<R, Args...> = *this;
                trackId++;
                idx = 0;
                return _func();
            } catch (const std::exception& e) { std::cerr << "Exception in Effect: " << e.what() << std::endl; }
        }

        explicit operator bool() const noexcept {
            return _func != nullptr;
        }
};

template<typename R>
class Dep : public std::map<Effect<R>*, size_t> {
    public:
        std::function<void()> cleanup;
        explicit Dep(const std::function<void()>& cleanup)
            : cleanup(cleanup) {}

        std::optional<size_t> get(const Effect<R>& effect) {
            if (auto it = this->find(effect); it != this->end()) return it->second;
            return std::nullopt;
        }

        explicit operator bool() const noexcept {
            return !this->empty();
        }
};

template<typename T>
class Ref {
    private:
        T _val;
        Dep<std::any>* _dep = nullptr;

    public:

        explicit Ref(T val)
            : _val(std::move(val)) {}

        T value() const noexcept {
            trackRef(*this);
            return _val;
        }

        Dep<std::any>* dep() {
            return dep;
        }

        void dep(Dep<std::any>* dep) {
            this->dep = dep;
        }

        void dep(Dep<std::any>& dep) {
            this->dep = &dep;
        }

        void value(T val) {
            _val = std::move(val);
            triggerRef(*this);
        }

        Ref& operator=(T val) {
            _val = std::move(val);
            triggerRef(*this);
            return *this;
        }
};

template<typename R>
void track(const Effect<R>& effect, const Dep<R>& dep) {
    if (dep.get(effect) != effect.trackId) {
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

template<typename R>
void trigger(const Dep<R>& dep) {
    for (auto&& [effect, trackId] : dep)
        if (trackId == effect->trackId) *effect();
}

template<typename T>
void trackRef(const Ref<T>& ref) {
    if (Global::ACTIVE_EFFECT) track(any_cast<Effect<std::any>>(Global::ACTIVE_EFFECT), ref.dep ? *ref.dep : Dep<std::any>([&ref] { ref.dep(nullptr); }));
}

template<typename T>
void triggerRef(const Ref<T>& ref) {
    if (ref) trigger(ref.dep());
}

#endif  // DOCSPAWNER_REACTIVE_H
