#pragma once

#ifndef NODE_HPP
#define NODE_HPP

template <typename T>
struct Node {
    Node* previousNode{};
    Node* nextNode{};
    T element{};
    
    Node(const T& element);
    void interconnectWith(Node<T>* next);
    ~Node();
};

#include "Node.inl"

#endif