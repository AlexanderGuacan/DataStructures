#include "Node.hpp"

template <typename T>
inline Node<T>::Node(const T& initialData): data{ initialData } {
}

template <typename T>
inline Node<T>::~Node() {
    if (previousNode != nullptr)
        previousNode = nullptr;
    
    if (nextNode != nullptr)
        nextNode = nullptr;
}