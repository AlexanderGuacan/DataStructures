#include "LinkedList.hpp"

template <typename T>
void LinkedList<T>::copy(const List<T>& list) {
    const LinkedList<T>* linkedList{ dynamic_cast<const LinkedList<T>*>(&list) };
    for (const T& element : *linkedList)
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
inline LinkedList<T>::LinkedList(std::initializer_list<T> list) {
    for (const T& element : list)
        addAtEnd(element);
}

template<typename T>
inline LinkedList<T>::LinkedList(const LinkedList<T>& list) {
    copy(list);
}


template<typename T>
inline void LinkedList<T>::clear() {
    while (!List<T>::isEmpty())
        removeLast();
}

template<typename T>
inline void LinkedList<T>::addAtBegin(const T& element) {
    Node<T>* newNode{ new Node<T>{ element } };

    if (List<T>::isEmpty()) {
        initializeLimits(element);
        bottomLimit->interconnectPrevious(newNode);
        tail = newNode;
    } else {
        head->interconnectPrevious(newNode);
    }

    topLimit->interconnectNext(newNode);
    head = newNode;
    ++List<T>::length;
}

template<typename T>
inline void LinkedList<T>::addAtEnd(const T& element) {
    Node<T>* newNode{ new Node<T>{ element } };

    if (List<T>::isEmpty()) {
        initializeLimits(element);
        topLimit->interconnectNext(newNode);
        head = newNode;
    } else {
        tail->interconnectNext(newNode);
    }

    bottomLimit->interconnectPrevious(newNode);
    tail = newNode;
    ++List<T>::length;
}

template<typename T>
inline void LinkedList<T>::addToIndex(const T& element, int index) {
    if (List<T>::isOutOfBounded(index))
        throw "Index out of bounded exception";

    if (index == 0)
        return addAtBegin(element);

    if (index == List<T>::length - 1)
        return addAtEnd(element);

    Node<T>* nextToNewNode{ getNode(index) };
    Node<T>* previousToNewNode{ nextToNewNode->previous };
    Node<T>* newNode{ new Node<T>{ element } };

    newNode->interconnectNext(nextToNewNode);
    newNode->interconnectPrevious(previousToNewNode);

    ++List<T>::length;
}

template<typename T>
inline T LinkedList<T>::removeFirst() {
    if (List<T>::isEmpty())
        throw "Empty list exception";

    Node<T>* nodeRemoved{ head };

    head = head->next;
    topLimit->interconnectNext(head);
    --List<T>::length;

    T elementRemoved{ nodeRemoved->element };

    delete nodeRemoved;
    nodeRemoved = nullptr;

    if (List<T>::isEmpty())
        tail = nullptr;

    return elementRemoved;
}

template<typename T>
inline T LinkedList<T>::removeLast() {
    if (List<T>::isEmpty())
        throw "Empty list exception";

    Node<T>* nodeRemoved{ tail };

    tail = tail->previous;
    bottomLimit->interconnectPrevious(tail);
    --List<T>::length;

    T elementRemoved{ nodeRemoved->element };

    delete nodeRemoved;
    nodeRemoved = nullptr;

    if (List<T>::isEmpty())
        head = nullptr;

    return elementRemoved;
}

template<typename T>
inline T LinkedList<T>::removeAtIndex(int index) {
    if (List<T>::isOutOfBounded(index))
        throw "Index out of bounded exception";

    if (index == 0)
        return removeFirst();

    if (index == List<T>::length - 1)
        return removeLast();

    Node<T>* nodeRemoved{ getNode(index) };
    Node<T>* previousToNodeRemoved{ nodeRemoved->previous };
    Node<T>* nextToNodeRemoved{ nodeRemoved->next };

    previousToNodeRemoved->interconnectNext(nextToNodeRemoved);
    --List<T>::length;

    T elementRemoved{ nodeRemoved->element };

    delete nodeRemoved;
    nodeRemoved = nullptr;

    return elementRemoved;
}

template<typename T>
inline void LinkedList<T>::forEach(std::function<void(const T& element)> callback) const {
    for (const T& element : *this)
        callback(element);
}

template<typename T>
inline LinkedList<T>* LinkedList<T>::map(std::function<T(const T& element)> process) const {
    LinkedList<T>* mappedList{ new LinkedList<T>{} };

    for (const T& element : *this)
        mappedList->addAtEnd(process(element));

    return mappedList;
}

template<typename T>
inline LinkedList<T>* LinkedList<T>::filter(std::function<bool(const T& element)> isFilteredMatch) const {
    LinkedList<T>* filteredList{ new LinkedList<T>{} };

    for (const T& element : *this) {
        if (isFilteredMatch(element))
            filteredList->addAtEnd(element);
    }

    return filteredList;
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
inline LinkedList<T>& LinkedList<T>::operator=(const List<T>& rightHandSideOperator) {
    const LinkedList<T>* castedOperator{ dynamic_cast<const LinkedList<T>*>(&rightHandSideOperator) };

    if (castedOperator == this)
        return *this;

    clear();
    copy(*castedOperator);

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
inline LinkedList<T> operator+(const LinkedList<T>& leftHandSideOperator, const LinkedList<T>& rightHandSideOperator) {
    LinkedList<T> result{ leftHandSideOperator };
    result.copy(rightHandSideOperator);
    return result;
}

template<typename T>
inline LinkedList<T>::~LinkedList() {
    clear();
}