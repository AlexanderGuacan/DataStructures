#pragma once

#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include "Iterator.hpp"
#include <sys/types.h>
#include <initializer_list>

template <typename T>
class LinkedList {
    private:
        ssize_t mLength{};
        TwoWayNode<T>* mStart{};
        TwoWayNode<T>* mHead{};
        TwoWayNode<T>* mTail{};
        TwoWayNode<T>* mFinish{};

    public:
        LinkedList() = default;
        LinkedList(std::initializer_list<T> elements);
        LinkedList(const LinkedList& elements);
        void add(const T& element);
        void add(const LinkedList& elements);
        Iterator<T> begin() const;
        void clear();
        bool contain(const T& element) const;
        Iterator<T> end() const;
        const T& get(ssize_t index) const;
        ssize_t indexOf(const T& element) const;
        bool isEmpty() const;
        Iterator<T> iterator() const;
        ssize_t lastIndexOf(const T& element) const;
        ssize_t length() const;
        const T& operator[](ssize_t index) const;
        LinkedList& operator=(const LinkedList& rhs);
        template <typename _T>
        friend LinkedList<_T> operator+(const LinkedList<_T>& lhs, const LinkedList<_T>& rhs);
        LinkedList& operator+=(const LinkedList& rhs);
        template <typename _T>
        friend bool operator==(const LinkedList<_T>& lhs, const LinkedList<_T>& rhs);
        template <typename _T>
        friend bool operator!=(const LinkedList<_T>& lhs, const LinkedList<_T>& rhs);
        const T& peek() const;
        T pop();
        T pull();
        void push(const T& element);
        T remove(ssize_t index);
        void set(ssize_t index, const T& element);
        const T& top() const;
        ~LinkedList();
};

#include "LinkedList.inl"

#endif