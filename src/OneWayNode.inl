#include "OneWayNode.hpp"

template <typename T>
inline OneWayNode<T>::OneWayNode(const T& element, OneWayNode* nextNode): mElement{ element }, mNext{ nextNode } {
}

template <typename T>
inline const T& OneWayNode<T>::getElement() const {
    return mElement;
}

template <typename T>
inline OneWayNode<T>* const& OneWayNode<T>::getNextNode() const {
    return mNext;
}

template <typename T>
inline void OneWayNode<T>::setElement(const T& element) {
    mElement = element;
}

template <typename T>
inline void OneWayNode<T>::setNextNode(OneWayNode* node) {
    mNext = node;
}

template <typename T>
inline OneWayNode<T>::~OneWayNode() {
    mNext = nullptr;
}