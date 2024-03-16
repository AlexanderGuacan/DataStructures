#pragma once

#ifndef NODE_HPP
#define NODE_HPP

template <typename T>
struct Node {
    Node* previousNode{};
    Node* nextNode{};
    T element{};
    
    Node(const T& initialElement);
    ~Node();
};

#include "Node.inl"

#endif