#pragma once

#ifndef UNIDIRECTIONAL_NODE_HPP
#define UNIDIRECTIONAL_NODE_HPP

template <typename T>
struct UnidirectionalNode {
    UnidirectionalNode* adjacentNode{ nullptr };
    T data{};
    
    UnidirectionalNode(const T& initialData);
    ~UnidirectionalNode();
};

#include "UnidirectionalNode.inl"

#endif