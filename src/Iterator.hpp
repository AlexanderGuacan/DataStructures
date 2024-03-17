#pragma once

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "Node.hpp"

template <typename T>
class Iterator {
    private:

    Node<T>* cursor{};

    void scrollCursorForward(int positions);
    void scrollCursorBackward(int positions);

    public:

    Iterator(Node<T>* begin);
    T& currentElement();
    T& operator*();
    Iterator& operator++();
    Iterator& operator--();
    Iterator operator++(int);
    Iterator operator--(int);
    Iterator& operator+=(int positions);
    Iterator& operator-=(int positions);
    template <typename _T>
    friend bool operator==(const Iterator<_T>& leftHandSideOperator, const Iterator<_T>& rightHandSideOperator);
    template <typename _T>
    friend bool operator!=(const Iterator<_T>& leftHandSideOperator, const Iterator<_T>& rightHandSideOperator);
    template <typename _T>
    friend Iterator<_T> operator+(Iterator<_T> iterator, int positions);
    template <typename _T>
    friend Iterator<_T> operator-(Iterator<_T> iterator, int positions);
    ~Iterator();
};

#include "Iterator.inl"

#endif