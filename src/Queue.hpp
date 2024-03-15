#pragma once

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "UnidirectionalNode.hpp"
#include "UnidirectionalIterator.hpp"
#include <initializer_list>

template <typename T>
class Queue {
    private:

    int length{};
    UnidirectionalNode<T>* front{};
    UnidirectionalNode<T>* back{};

    public:

    Queue(std::initializer_list<T> list);
    Queue(const Queue& queue);
    int getLength();
    const T& getFront() const;
    void enqueue(const T& element);
    T dequeue();
    bool isEmpty() const;
    ~Queue();
};

#include "Queue.inl"

#endif