#include "Node.hpp"

template <typename T>
inline Node<T>::Node(const T& initialData): data{ initialData } {
}

template <typename T>
inline Node<T>::~Node() {
    if (previousAdjacentNode != nullptr)
        previousAdjacentNode = nullptr;
    
    if (nextAdjacentNode != nullptr)
        nextAdjacentNode = nullptr;
}