#pragma once

#ifndef ARRAY_LIST_HPP
#define ARRAY_LIST_HPP

#include <sys/types.h>
#include <initializer_list>

template <typename T>
class ArrayList {
    private:
        ssize_t mCapacity{};
        ssize_t mLength{};
        T* mArray{};

        void resize(ssize_t capacity);

    public:
        ArrayList(ssize_t capacity = 10);
        ArrayList(std::initializer_list<T> elements);
        ArrayList(const ArrayList& elements);
        void add(const T& element);
        void add(const ArrayList& elements);
        T* begin() const;
        ssize_t capacity() const;
        void clear();
        bool contain(const T& element) const;
        T* end() const;
        const T& get(ssize_t index) const;
        ssize_t indexOf(const T& element) const;
        bool isEmpty() const;
        ssize_t lastIndexOf(const T& element) const;
        ssize_t length() const;
        T& operator[](ssize_t index);
        const T& operator[](ssize_t index) const;
        ArrayList& operator=(const ArrayList& rhs);
        template <typename _T>
        friend ArrayList<_T> operator+(const ArrayList<_T>& lhs, const ArrayList<_T>& rhs);
        ArrayList& operator+=(const ArrayList& rhs);
        template <typename _T>
        friend bool operator==(const ArrayList<_T>& lhs, const ArrayList<_T>& rhs);
        template <typename _T>
        friend bool operator!=(const ArrayList<_T>& lhs, const ArrayList<_T>& rhs);
        const T& peek() const;
        T pop();
        T pull();
        void push(const T& element);
        T remove(ssize_t index);
        void set(ssize_t index, const T& element);
        const T& top() const;
        ~ArrayList();
};

#include "ArrayList.inl"

#endif