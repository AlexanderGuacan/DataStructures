#include "LinkedList.hpp"

template <typename T>
void LinkedList<T>::copy(const LinkedList<T>& list) {
    for (const T& element : list)
        addAtEnd(element);
}

template<typename T>
inline void LinkedList<T>::initializeLimits(const T& element) {
    topLimit = new Node{ element };
    bottomLimit = new Node{ element };
}

template<typename T>
inline Node<T>* LinkedList<T>::getNode(int index) {
    Node<T>* iterator{ head };

    for (int i{}; i < index; ++i)
        iterator = iterator->next;

    return iterator;
}

template<typename T>
inline bool LinkedList<T>::isOutOfBounded(int index) {
    return index < 0 || index >= length;
}

template<typename T>
inline LinkedList<T>::LinkedList(std::initializer_list<T> list) {
    for (const T& element : list)
        addAtEnd(element);
}

template<typename T>
inline LinkedList<T>::LinkedList(const LinkedList& list) {
    copy(list);
}

template<typename T>
inline int LinkedList<T>::getLength() const {
    return length;
}

template<typename T>
inline bool LinkedList<T>::isEmpty() const {
    return !length;
}

template<typename T>
inline void LinkedList<T>::clear() {
    while (!isEmpty())
        removeLast();
}

template<typename T>
inline void LinkedList<T>::addAtBegin(const T& element) {
    Node<T>* newNode{ new Node{ element } };

    if (isEmpty()) {
        initializeLimits(element);
        bottomLimit->interconnectPrevious(newNode);
        tail = newNode;
    } else {
        head->interconnectPrevious(newNode);
    }

    topLimit->interconnectNext(newNode);
    head = newNode;
    ++length;
}

template<typename T>
inline void LinkedList<T>::addAtEnd(const T& element) {
    Node<T>* newNode{ new Node{ element } };

    if (isEmpty()) {
        initializeLimits(element);
        topLimit->interconnectNext(newNode);
        head = newNode;
    } else {
        tail->interconnectNext(newNode);
    }

    bottomLimit->interconnectPrevious(newNode);
    tail = newNode;
    ++length;
}

template<typename T>
inline void LinkedList<T>::addIn(const T& element, int index) {
    if (isOutOfBounded(index))
        throw "Index out of bounded exception";

    if (index == 0)
        return addAtBegin(element);

    if (index == length - 1)
        return addAtEnd(element);

    Node<T>* nextToNewNode{ getNode(index) };
    Node<T>* previousToNewNode{ nextToNewNode->previous };
    Node<T>* newNode{ new Node{ element } };

    newNode->interconnectNext(nextToNewNode);
    newNode->interconnectPrevious(previousToNewNode);

    ++length;
}

template<typename T>
inline T LinkedList<T>::removeFirst() {
    if (isEmpty())
        throw "Empty list exception";

    T elementRemoved{ head->element };
    Node<T>* nodeRemoved{ head };

    head = head->next;
    topLimit->interconnectNext(head);
    --length;

    delete nodeRemoved;
    nodeRemoved = nullptr;

    if (isEmpty())
        tail = nullptr;

    return elementRemoved;
}

template<typename T>
inline T LinkedList<T>::removeLast() {
    if (isEmpty())
        throw "Empty list exception";

    T elementRemoved{ tail->element };
    Node<T>* nodeRemoved{ tail };

    tail = tail->previous;
    bottomLimit->interconnectPrevious(tail);
    --length;

    delete nodeRemoved;
    nodeRemoved = nullptr;

    if (isEmpty())
        head = nullptr;

    return elementRemoved;
}

template<typename T>
inline T LinkedList<T>::removeFrom(int index) {
    if (isOutOfBounded(index))
        throw "Index out of bounded exception";

    if (index == 0)
        return removeFirst();

    if (index == length - 1)
        return removeLast();

    Node<T>* nodeRemoved{ getNode(index) };
    Node<T>* previousToNodeRemoved{ nodeRemoved->previous };
    Node<T>* nextToNodeRemoved{ nodeRemoved->next };

    previousToNodeRemoved->interconnectNext(nextToNodeRemoved);
    --length;

    T elementRemoved{ nodeRemoved->element };

    delete nodeRemoved;
    nodeRemoved = nullptr;

    return elementRemoved;
}

template<typename T>
inline void LinkedList<T>::forEach(std::function<void(T& element)> modify) {
    for (T& element : *this)
        modify(element);
}

template<typename T>
inline LinkedList<T> LinkedList<T>::map(std::function<T(const T& element)> process) const {
    LinkedList<T> mappedList{};

    for (const T& element : *this)
        mappedList.addAtEnd(process(element));

    return mappedList;
}

template<typename T>
inline LinkedList<T> LinkedList<T>::filter(std::function<bool(const T& element)> isFilteredMatch) const {
    LinkedList<T> filterList{};

    for (const T& element : *this) {
        if (isFilteredMatch(element))
            filterList.addAtEnd(element);
    }

    return filterList;
}

template<typename T>
inline Iterator<T> LinkedList<T>::begin() const {
    return Iterator<T>{ head };
}

template<typename T>
inline Iterator<T> LinkedList<T>::end() const {
    return Iterator<T>{ tail->next };
}

template<typename T>
inline T& LinkedList<T>::operator[](int index) {
    Node<T>* nodeSelected{ getNode(index) };
    return nodeSelected->element;
}

template<typename T>
inline LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rightHandSideOperator) {
    if (this == &rightHandSideOperator)
        return *this;

    clear();
    copy(rightHandSideOperator);

    return *this;
}

template<typename T>
inline bool operator==(const LinkedList<T>& leftHandSideOperator, const LinkedList<T>& rightHandSideOperator) {
    if (&leftHandSideOperator == &rightHandSideOperator)
        return true;

    if (leftHandSideOperator.length != rightHandSideOperator.length)
        return false;

    for (Iterator<T> i{ leftHandSideOperator.begin() }, j{ rightHandSideOperator.begin() }; i != leftHandSideOperator.end(); ++i, ++j) {
        if (i.currentElement() != j.currentElement())
            return false;
    }

    return true;
}

template<typename T>
inline bool operator!=(const LinkedList<T>& leftHandSideOperator, const LinkedList<T>& rightHandSideOperator) {
    return !(leftHandSideOperator == rightHandSideOperator);
}

template<typename T>
inline LinkedList<T>::~LinkedList() {
    clear();
}