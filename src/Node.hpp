#pragma once

#ifndef NODE_HPP
#define NODE_HPP

template <typename T>
struct Node {
    Node* previousNode{};
    Node* nextNode{};
    T data{};
    
    Node(const T& initialData);
    ~Node();
};

#include "Node.inl"

#endif