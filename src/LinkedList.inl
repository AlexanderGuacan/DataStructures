#include "LinkedList.hpp"

template <typename T>
inline LinkedList<T>::LinkedList(std::initializer_list<T> elements) {
    for (const auto& element : elements)
        add(element);
}

template <typename T>
inline LinkedList<T>::LinkedList(const LinkedList& elements) {
    add(elements);
}

template <typename T>
inline void LinkedList<T>::add(const T& element) {
    TwoWayNode<T>* last{ new TwoWayNode{ element } };

    if (isEmpty()) {
        mStart = new TwoWayNode<T>{ element };
        mFinish = new TwoWayNode<T>{ element };
        mStart->setNextNode(last);
        last->setPreviousNode(mStart);
        mHead = last;
    } else {
        last->setPreviousNode(mTail);
        mTail->setNextNode(last);
    }

    mFinish->setPreviousNode(last);
    last->setNextNode(mFinish);
    mTail = last;

    ++mLength;
}

template <typename T>
inline void LinkedList<T>::add(const LinkedList& elements) {
    TwoWayNode<T>* iterator{ elements.mHead };

    while (iterator != mFinish) {
        add(iterator->getElement());
        iterator = iterator->getNextNode();
    }
}

template <typename T>
inline Iterator<T> LinkedList<T>::begin() const {
    return Iterator{ mHead };
}

template <typename T>
inline void LinkedList<T>::clear() {
    TwoWayNode<T>* iterator{ mStart };

    while (iterator != nullptr) {
        TwoWayNode<T>* node{ iterator };
        iterator = iterator->getNextNode();
        delete node;
    }

    mStart = nullptr;
    mHead = nullptr;
    mTail = nullptr;
    mFinish = nullptr;
}

template <typename T>
inline bool LinkedList<T>::contain(const T& element) const {
    TwoWayNode<T>* iterator{ mHead };

    while (iterator != mFinish) {
        if (iterator->getElement() == element)
            return true;

        iterator = iterator->getNextNode();
    }

    return false;
}

template <typename T>
inline Iterator<T> LinkedList<T>::end() const {    
    return Iterator<T>{ mFinish };
}

template <typename T>
inline const T& LinkedList<T>::get(ssize_t index) const {
    if (index >= mLength)
        throw "Index out of bounds exception";

    TwoWayNode<T>* iterator{ mHead };
    ssize_t position{};

    while (position < index) {
        iterator = iterator->getNextNode();
        ++position;
    }

    return iterator->getElement();
}

template <typename T>
inline ssize_t LinkedList<T>::indexOf(const T& element) const {
    ssize_t index{};

    TwoWayNode<T>* iterator{ mHead };

    while (iterator != mFinish) {
        if (element == iterator->getElement())
            return index;

        iterator = iterator->getNextNode();
        ++index;
    }

    return -1;
}

template <typename T>
inline bool LinkedList<T>::isEmpty() const {
    return mLength == 0;
}

template <typename T>
inline Iterator<T> LinkedList<T>::iterator() const {
    return begin();
}

template <typename T>
inline ssize_t LinkedList<T>::lastIndexOf(const T& element) const {
    ssize_t index{ mLength - 1 };

    TwoWayNode<T>* iterator{ mTail };

    while (iterator != mStart) {
        if (element == iterator->getElement())
            return index;

        iterator = iterator->getPreviousNode();
        --index;
    }

    return -1;
}

template <typename T>
inline ssize_t LinkedList<T>::length() const {
    return mLength;
}

template <typename T>
inline const T& LinkedList<T>::operator[](ssize_t index) const {
    return get(index);
}

template <typename T>
inline LinkedList<T>& LinkedList<T>::operator=(const LinkedList& rhs) {
    if (this == &rhs)
        return *this;

    clear();
    add(rhs);

    return *this;
}

template <typename T>
inline LinkedList<T> operator+(const LinkedList<T>& lhs, const LinkedList<T>& rhs) {
    LinkedList combination{ lhs };
    combination.add(rhs);

    return combination;
}

template <typename T>
inline LinkedList<T>& LinkedList<T>::operator+=(const LinkedList& rhs) {
    add(rhs);
    return *this;
}

template <typename T>
inline bool operator==(const LinkedList<T>& lhs, const LinkedList<T>& rhs) {
    if (lhs.mLength != rhs.mLength)
        return false;

    if (&lhs == &rhs)
        return true;

    TwoWayNode<T>* iteratorLeft{ lhs.mHead };
    TwoWayNode<T>* iteratorRight{ rhs.mHead };

    while (iteratorLeft != lhs.mFinish) {
        if (iteratorLeft->getElement() != iteratorRight->getElement())
            return false;

        iteratorLeft = iteratorLeft->getNextNode();
        iteratorRight = iteratorRight->getNextNode();
    }

    return true;
}

template <typename T>
inline bool operator!=(const LinkedList<T>& lhs, const LinkedList<T>& rhs) {
    return !(lhs == rhs);
}

template <typename T>
inline const T& LinkedList<T>::peek() const {
    return mTail->getElement();
}

template <typename T>
inline T LinkedList<T>::pop() {
    if (isEmpty())
        throw "Empty list exception";

    T lastElement{ mTail->getElement() };
    TwoWayNode<T>* lastNode{ mTail };

    mTail = mTail->getPreviousNode();
    mTail->setNextNode(mFinish);
    mFinish->setPreviousNode(mTail);

    delete lastNode;
    --mLength;

    if (isEmpty()) {
        delete mStart;
        delete mFinish;
        mStart = nullptr;
        mHead = nullptr;
        mTail = nullptr;
        mFinish = nullptr;
    }

    return lastElement;
}

template <typename T>
inline T LinkedList<T>::pull() {
    if (isEmpty())
        throw "Empty list exception";

    T firstElement{ mHead->getElement() };
    TwoWayNode<T>* firstNode{ mHead };

    mHead = mHead->getNextNode();
    mHead->setPreviousNode(mStart);
    mStart->setNextNode(mHead);

    delete firstNode;
    --mLength;

    if (isEmpty()) {
        delete mStart;
        delete mFinish;
        mStart = nullptr;
        mHead = nullptr;
        mTail = nullptr;
        mFinish = nullptr;
    }

    return firstElement;
}

template <typename T>
inline void LinkedList<T>::push(const T& element) {
    TwoWayNode<T>* first{ new TwoWayNode{ element } };

    if (isEmpty()) {
        mStart = new TwoWayNode<T>{ element };
        mFinish = new TwoWayNode<T>{ element };
        mFinish->setPreviousNode(first);
        first->setNextNode(mFinish);
        mTail = first;
    } else {
        first->setNextNode(mHead);
        mHead->setPreviousNode(first);
    }

    mStart->setNextNode(first);
    first->setPreviousNode(mStart);
    mHead = first;

    ++mLength;
}

template <typename T>
inline T LinkedList<T>::remove(ssize_t index) {
    if (index >= mLength)
        throw "Index out of bounds exception";

    if (index == 0)
        return pull();

    if (index == mLength - 1)
        return pop();

    TwoWayNode<T>* iterator{ mHead };
    ssize_t position{};

    while (position < index) {
        iterator = iterator->getNextNode();
        ++position;
    }

    T element{ iterator->getElement() };

    iterator->getPreviousNode()->setNextNode(iterator->getNextNode());
    iterator->getNextNode()->setPreviousNode(iterator->getPreviousNode());

    delete iterator;
    --mLength;

    return element;
}

template <typename T>
inline void LinkedList<T>::set(ssize_t index, const T& element) {
    if (index >= mLength)
        throw "Index out of bounds exception";

    TwoWayNode<T>* iterator{ mHead };
    ssize_t position{};

    while (position < index) {
        iterator = iterator->getNextNode();
        ++position;
    }

    iterator->setElement(element);
}

template <typename T>
inline const T& LinkedList<T>::top() const {
    return mHead->getElement();
}

template <typename T>
inline LinkedList<T>::~LinkedList() {
    clear();
}