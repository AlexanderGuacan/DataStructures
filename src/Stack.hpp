#pragma once

#ifndef STACK_HPP
#define STACK_HPP

#include "Node.hpp"
#include <initializer_list>

template <typename T>
class Stack {
    private:

    int length{};
    Node<T>* top{};
    Node<T>* bottom{};

    void copy(const Stack<T>& stack);

    public:

    Stack() = default;
    Stack(std::initializer_list<T> list);
    Stack(const Stack<T>& stack);
    int getLength() const;
    const T& getTop() const;
    void push(const T& element);
    T pop();
    bool isEmpty() const;
    void clear();
    Stack<T>& operator=(const Stack<T>& rightHandSideOperator);
    template <typename _T>
    friend bool operator==(const Stack<_T>& leftHandSideOperator, const Stack<_T>& rightHandSideOperator);
    template <typename _T>
    friend bool operator!=(const Stack<_T>& leftHandSideOperator, const Stack<_T>& rightHandSideOperator);
    ~Stack();
};

#include "Stack.inl"

#endif