#pragma once

#ifndef LIST_HPP
#define LIST_HPP

#include <functional>

template <typename T>
class List {
    protected:
    
    int length{};

    bool isOutOfBounded(int index);
    virtual void copy(const List& list) = 0;

    public:

    int getLength() const;
    bool isEmpty() const;
    virtual void clear() = 0;
    virtual void addAtBegin(const T& element) = 0;
    virtual void addAtEnd(const T& element) = 0;
    virtual void addToIndex(const T& element, int index) = 0;
    virtual T removeFirst() = 0;
    virtual T removeLast() = 0;
    virtual T removeAtIndex(int index) = 0;
    virtual void forEach(std::function<void(const T& element)> callback) const = 0;
    virtual List* map(std::function<T(const T& element)> process) const = 0;
    virtual List* filter(std::function<bool(const T& element)> isFilteredMatch) const = 0;
    virtual T& operator[](int index) = 0;
    virtual const T& operator[](int index) const = 0;
    virtual List& operator=(const List& rightHandSideOperator) = 0;
    virtual ~List() = default;
};

#include "List.inl"

#endif