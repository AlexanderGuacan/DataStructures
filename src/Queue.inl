#include "Queue.hpp"

template <typename T>
inline void Queue<T>::copy(const Queue& elements) {
    mHead = new OneWayNode{ elements.mHead->getElement() };
    mTail = mHead;

    const OneWayNode<T>* iterator{ elements.mHead->getNextNode() };

    while (iterator != nullptr) {
        mTail->setNextNode(new OneWayNode{ iterator->getElement() });
        mTail = mTail->getNextNode();
        iterator = iterator->getNextNode();
    }

    mLength = elements.mLength;
}

template <typename T>
inline Queue<T>::Queue(std::initializer_list<T> elements) {
    for (const auto& element : elements)
        add(element);
}

template <typename T>
inline Queue<T>::Queue(const Queue& elements) {
    clone(elements);
}

template <typename T>
inline void Queue<T>::add(const T& element) {
    OneWayNode<T>* next{ new OneWayNode{ element } };

    if (isEmpty())
        mHead = next;
    else
        mTail->setNextNode(next);

    mTail = next;

    ++mLength;
}

template <typename T>
inline void Queue<T>::clear() {
    while (!isEmpty())
        pull();
}

template <typename T>
inline bool Queue<T>::isEmpty() const {
    return mLength <= 0;
}

template <typename T>
inline ssize_t Queue<T>::length() const {
    return mLength;
}

template <typename T>
inline Queue<T>& Queue<T>::operator=(const Queue& rhs) {
    if (this == &rhs)
        return *this;

    clear();
    clone(rhs);

    return *this;
}

template <typename T>
inline bool operator==(const Queue<T>& lhs, const Queue<T>& rhs) {
    if (lhs.mLength != rhs.mLength)
        return false;

    OneWayNode<T>* iteratorLeft{ lhs.mHead };
    OneWayNode<T>* iteratorRight{ rhs.mHead };

    while (iteratorLeft != nullptr) {
        if (iteratorLeft->getElement() != iteratorRight->getElement())
            return false;

        iteratorLeft = iteratorLeft->getNextNode();
        iteratorRight = iteratorRight->getNextNode();
    }

    return true;
}

template <typename T>
inline bool operator!=(const Queue<T>& lhs, const Queue<T>& rhs) {
    return !(lhs == rhs);
}

template <typename T>
inline T Queue<T>::pull() {
    if (isEmpty())
        throw "Empty queue exception";

    T topElement{ mHead->getElement() };

    OneWayNode<T>* topNode{ mHead };
    mHead = mHead->getNextNode();

    if (mHead == nullptr)
        mTail = nullptr;

    delete topNode;
    topNode = nullptr;

    --mLength;

    return topElement;
}

template <typename T>
inline const T& Queue<T>::top() const {
    return mHead->getElement();
}

template <typename T>
inline Queue<T>::~Queue() {
    clear();
}