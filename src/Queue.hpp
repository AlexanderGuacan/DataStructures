#pragma once

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "OneWayNode.hpp"
#include <sys/types.h>
#include <initializer_list>

template <typename T>
class Queue {
    private:
        OneWayNode<T>* mHead{};
        OneWayNode<T>* mTail{};
        ssize_t mLength{};

        void copy(const Queue& elements);

    public:
        Queue() = default;
        Queue(std::initializer_list<T> elements);
        Queue(const Queue& elements);
        void add(const T& element);
        void clear();
        bool isEmpty() const;
        ssize_t length() const;
        Queue& operator=(const Queue& rhs);
        template <typename _T>
        friend bool operator==(const Queue& lhs, const Queue& rhs);
        template <typename _T>
        friend bool operator!=(const Queue& lhs, const Queue& rhs);
        T pull();
        const T& top() const;
        ~Queue();
};

#include "Queue.inl"

#endif