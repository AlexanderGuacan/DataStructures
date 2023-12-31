#include "TwoWayNode.hpp"

template <typename T>
inline TwoWayNode<T>::TwoWayNode(const T& element, TwoWayNode* previousNode, TwoWayNode* nextNode): mElement{ element }, mPrevious{ previousNode }, mNext{ nextNode } {
}

template <typename T>
inline const T& TwoWayNode<T>::getElement() const {
    return mElement;
}

template <typename T>
inline TwoWayNode<T>* const& TwoWayNode<T>::getNextNode() const {
    return mNext;
}

template <typename T>
inline TwoWayNode<T>* const& TwoWayNode<T>::getPreviousNode() const {
    return mPrevious;
}

template <typename T>
inline void TwoWayNode<T>::setElement(const T& element) {
    mElement = element;
}

template <typename T>
inline void TwoWayNode<T>::setNextNode(TwoWayNode* node) {
    mNext = node;
}

template <typename T>
inline void TwoWayNode<T>::setPreviousNode(TwoWayNode* node) {
    mPrevious = node;
}

template <typename T>
inline TwoWayNode<T>::~TwoWayNode() {
    mNext = nullptr;
    mPrevious = nullptr;
}