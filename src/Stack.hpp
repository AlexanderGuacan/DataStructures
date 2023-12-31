#pragma once

#ifndef STACK_HPP
#define STACK_HPP

#include "OneWayNode.hpp"
#include <sys/types.h>
#include <initializer_list>

template <typename T>
class Stack {
    private:
        OneWayNode<T>* mHead{};
        ssize_t mLength{};

        void copy(const Stack& elements);

    public:
        Stack() = default;
        Stack(std::initializer_list<T> elements);
        Stack(const Stack& elements);
        void clear();
        bool isEmpty() const;
        ssize_t length() const;
        Stack& operator=(const Stack& rhs);
        template <typename _T>
        friend bool operator==(const Stack& lhs, const Stack& rhs);
        template <typename _T>
        friend bool operator!=(const Stack& lhs, const Stack& rhs);
        const T& peek() const;
        T pop();
        void push(const T& element);
        ~Stack();
};

#include "Stack.inl"

#endif