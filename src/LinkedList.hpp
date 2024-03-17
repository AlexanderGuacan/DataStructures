#pragma once

#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include "Node.hpp"
#include "Iterator.hpp"
#include <initializer_list>
#include <functional>

template <typename T>
class LinkedList {
    private:

    int length{};
    Node<T>* topLimit{};
    Node<T>* head{};
    Node<T>* tail{};
    Node<T>* bottomLimit{};

    void copy(const LinkedList& list);
    void initializeLimits(const T& element);
    Node<T>* getNode(int index);
    bool isOutOfBounded(int index);

    public:

    LinkedList() = default;
    LinkedList(std::initializer_list<T> list);
    LinkedList(const LinkedList& list);
    int getLength() const;
    bool isEmpty() const;
    void clear();
    void addAtBegin(const T& element);
    void addAtEnd(const T& element);
    void addIn(const T& element, int index);
    T removeFirst();
    T removeLast();
    T removeFrom(int index);
    void forEach(std::function<void(T& element)> modify);
    LinkedList map(std::function<T(const T& element)> process) const;
    LinkedList filter(std::function<bool(const T& element)> isFilteredMatch) const;
    Iterator<T> begin() const;
    Iterator<T> end() const;
    T& operator[](int index);
    LinkedList& operator=(const LinkedList& rightHandSideOperator);
    template <typename _T>
    friend bool operator==(const LinkedList<_T>& leftHandSideOperator, const LinkedList<_T>& rightHandSideOperator);
    template <typename _T>
    friend bool operator!=(const LinkedList<_T>& leftHandSideOperator, const LinkedList<_T>& rightHandSideOperator);
    ~LinkedList();
};

#include "LinkedList.inl"

#endif