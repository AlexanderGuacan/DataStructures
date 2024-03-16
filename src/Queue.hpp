#pragma once

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "Node.hpp"
#include "Iterator.hpp"
#include <initializer_list>

template <typename T>
class Queue {
    private:

    int length{};
    Node<T>* head{};
    Node<T>* tail{};

    void copy(const Queue& queue);

    public:

    Queue(std::initializer_list<T> list);
    Queue(const Queue& queue);
    int getLength();
    const T& getHead() const;
    void enqueue(const T& element);
    T dequeue();
    bool isEmpty() const;
    void clear();
    Queue& operator=(const Queue& rightHandSideOperator);
    template <typename _T>
    friend bool operator==(const Queue<_T>& leftHandSideOperator, const Queue<_T>& rightHandSideOperator);
    template <typename _T>
    friend bool operator!=(const Queue<_T>& leftHandSideOperator, const Queue<_T>& rightHandSideOperator);
    ~Queue();
};

#include "Queue.inl"

#endif