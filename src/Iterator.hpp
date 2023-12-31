#pragma once

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "TwoWayNode.hpp"
#include <sys/types.h>

template <typename T>
class Iterator {
    private:
        TwoWayNode<T>* mCursor{};

    public:
        Iterator(TwoWayNode<T>* begin);
        Iterator(const Iterator& iterator);
        const T& get();
        void operator++();
        void operator--();
        const T& operator*();
        Iterator& operator=(const Iterator& rhs);
        template <typename _T>
        friend bool operator==(const Iterator<_T>& lhs, const Iterator<_T>& rhs);
        template <typename _T>
        friend bool operator!=(const Iterator<_T>& lhs, const Iterator<_T>& rhs);
        template <typename _T>
        friend Iterator<_T> operator-(const Iterator<_T>& lhs, ssize_t rhs);
        template <typename _T>
        friend Iterator<_T> operator+(const Iterator<_T>& lhs, ssize_t rhs);
        void set(const T& element) const;
        ~Iterator();
};

#include "Iterator.inl"

#endif