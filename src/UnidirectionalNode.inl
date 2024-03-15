#include "UnidirectionalNode.hpp"

template <typename T>
inline UnidirectionalNode<T>::UnidirectionalNode(const T& initialData): data{ initialData } {
}

template <typename T>
inline UnidirectionalNode<T>::~UnidirectionalNode() {
    if (!adjacentNode)
        return;
    
    adjacentNode = nullptr;
}