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

    public:

    Queue(std::initializer_list<T> list);
    Queue(const Queue& queue);
    int getLength();
    const T& getHead() const;
    void enqueue(const T& element);
    T dequeue();
    bool isEmpty() const;
    ~Queue();
};

#include "Queue.inl"

#endif