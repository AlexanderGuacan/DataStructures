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

    void copy(const Stack& stack);

    public:

    Stack(std::initializer_list<T> list);
    Stack(const Stack& stack);
    int getLength() const;
    const T& getTop() const;
    void push(const T& element);
    T pop();
    bool isEmpty() const;
    void clear();
    Stack& operator=(const Stack& rightHandSideOperator);
    ~Stack();
};

#include "Stack.inl"

#endif