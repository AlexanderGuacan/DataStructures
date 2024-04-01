#pragma once

#ifndef NODE_HPP
#define NODE_HPP

template <typename T>
class Node {
    public:
    
    Node<T>* previous{};
    Node<T>* next{};
    T element{};

    Node(const T& element);
    void connectPrevious(Node<T>* node);
    void connectNext(Node<T>* node);
    void interconnectPrevious(Node<T>* node);
    void interconnectNext(Node<T>* node);
    ~Node();
};

#include "Node.inl"

#endif