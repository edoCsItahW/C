// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: test
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/08/15 上午10:01
 * @Commend: Implementation of OrderList and LinkList
 *******************************************************/

#ifndef TEST_LIST_H
#define TEST_LIST_H
#pragma once

#include <format>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <windows.h>

#define MAX_SIZE 1000

namespace List {
    template<class T>
    class List {
        public:
            [[maybe_unused]] virtual T getElem(int idx)               = 0;
            [[maybe_unused]] virtual int locateElem(T elem)           = 0;
            [[maybe_unused]] virtual bool insertElem(T elem, int idx) = 0;
            [[maybe_unused]] virtual bool removeElem(int idx)         = 0;
    };

    template<typename T>
    class OrderList : public List<T> {
            using R = std::conditional_t<std::is_fundamental_v<T>, T, T&>;

        private:
            T* arr;
            int _size;

        public:
            OrderList();
            explicit OrderList(int size);
            OrderList(int size, T elem);
            ~OrderList();
            [[nodiscard]] int size() const;
            R getElem(int idx) override;
            R operator[](int idx);
            int locateElem(T elem) override;
            bool insertElem(T elem, int idx) override;
            bool removeElem(int idx) override;
    };

    template<typename T>
    OrderList<T>::OrderList()
        : arr(nullptr)
        , _size(0) {}

    template<typename T>
    OrderList<T>::OrderList(int size)
        : arr(new T[size])
        , _size(0) {}

    template<typename T>
    OrderList<T>::OrderList(int size, T elem)
        : OrderList(size) {
        for (int i = 0; i < size; i++) arr[i] = std::is_fundamental_v<T> ? elem : std::move(elem);
    }

    template<typename T>
    OrderList<T>::~OrderList() {
        delete[] arr;
    }

    template<typename T>
    int OrderList<T>::size() const {
        return _size;
    }

    template<typename T>
    OrderList<T>::R OrderList<T>::getElem(int idx) {
        if (idx < 0 || idx >= _size) throw std::out_of_range(std::format("Index {} out of range {}!", idx, _size));
        return arr[idx];
    }

    template<typename T>
    OrderList<T>::R OrderList<T>::operator[](int idx) {
        return getElem(idx);
    }

    template<typename T>
    int OrderList<T>::locateElem(T elem) {
        for (int i = 0; i < _size; i++)
            if (arr[i] == elem) return i;
        return 0;
    }

    template<typename T>
    bool OrderList<T>::insertElem(T elem, int idx) {
        if (idx < 0 || idx > _size) throw std::out_of_range(std::format("Unable to insert, index {} exceeds {}!", idx, _size));
        if (_size >= MAX_SIZE) throw std::range_error("Unable to insert, list is full!");
        for (int i = _size - 1; i >= idx; i--) arr[i + 1] = arr[i];
        arr[idx] = std::is_fundamental_v<T> ? elem : std::move(elem);
        ++_size;
        return true;
    }

    template<typename T>
    bool OrderList<T>::removeElem(int idx) {
        if (idx < 0 || idx >= _size) throw std::out_of_range(std::format("Unable to remove, index {} out of range {}!", idx, _size));
        for (int i = idx; i < _size - 1; i++) arr[i] = arr[i + 1];
        --_size;
        return true;
    }

    template<typename T>
    class LinkList : public List<T> {
            using R = std::conditional_t<std::is_fundamental_v<T>, T, T&>;

        private:
            using Node = struct node {
                    T data{};
                    std::unique_ptr<node> next;
            };

            std::unique_ptr<Node> head;
            int _size;

        public:
            LinkList();
            ~LinkList();
            [[nodiscard]] int size() const;
            R getElem(int idx) override;
            R operator[](int idx);
            int locateElem(T elem) override;
            bool insertElem(T elem, int idx) override;
            bool removeElem(int idx) override;
    };

    template<typename T>
    LinkList<T>::LinkList()
        : head(nullptr)
        , _size(0) {
        head       = std::make_unique<Node>();
        head->next = nullptr;
    }

    template<typename T>
    LinkList<T>::~LinkList() {
        while (head) head = std::move(head->next);
    }

    template<typename T>
    int LinkList<T>::size() const {
        return _size;
    }

    template<typename T>
    LinkList<T>::R LinkList<T>::getElem(int idx) {
        if (idx < 0 || idx >= _size) throw std::out_of_range(std::format("Index {} out of range {}!", idx, _size));
        auto curr = head.get();
        for (int i = 0; i < idx; i++) curr = curr->next.get();
        return curr->data;
    }

    template<typename T>
    LinkList<T>::R LinkList<T>::operator[](int idx) {
        return getElem(idx);
    }

    template<typename T>
    int LinkList<T>::locateElem(T elem) {
        auto curr = head.get();
        int idx   = 0;
        while (curr && curr->data != elem) {
            curr = curr->next.get();
            idx++;
        }
        return curr ? idx : -1;
    }

    template<typename T>
    bool LinkList<T>::insertElem(T elem, int idx) {
        if (idx < 0 || idx > _size) throw std::out_of_range(std::format("Unable to insert, index {} exceeds {}!", idx, _size));
        auto newNode  = std::make_unique<Node>();
        newNode->data = std::is_fundamental_v<T> ? elem : std::move(elem);

        if (idx == 0) {
            newNode->next = std::move(head);
            head          = std::move(newNode);
        } else {
            auto curr = head.get();
            for (int i = 0; i < idx - 1; i++) curr = curr->next.get();
            newNode->next = std::move(curr->next);
            curr->next    = std::move(newNode);
        }

        ++_size;
        return true;
    }

    template<typename T>
    bool LinkList<T>::removeElem(int idx) {
        if (idx < 0 || idx >= _size) throw std::out_of_range(std::format("Unable to remove, index {} out of range {}!", idx, _size));

        if (idx == 0)
            head = std::move(head->next);
        else {
            auto curr = head.get();
            for (int i = 0; i < idx - 1; i++) curr = curr->next.get();
            curr->next = std::move(curr->next->next);
        }
        --_size;
        return true;
    }
}  // namespace List

#endif  // TEST_LIST_H
