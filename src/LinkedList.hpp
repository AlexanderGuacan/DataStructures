#pragma once

#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include "Node.hpp"
#include "Iterator.hpp"
#include "List.hpp"
#include <initializer_list>

template <typename T>
class LinkedList : public List<T> {
    private:

    Node<T>* topLimit{};
    Node<T>* head{};
    Node<T>* tail{};
    Node<T>* bottomLimit{};

    void copy(const List<T>& list) override;
    void initializeLimits(const T& element);
    Node<T>* getNode(int index) const;

    public:

    LinkedList() = default;
    LinkedList(std::initializer_list<T> list);
    LinkedList(const LinkedList<T>& list);
    void clear() override;
    void addAtBegin(const T& element) override;
    void addAtEnd(const T& element) override;
    void addToIndex(const T& element, int index) override;
    T removeFirst() override;
    T removeLast() override;
    T removeAtIndex(int index) override;
    void forEach(std::function<void(const T& element)> callback) const override;
    LinkedList<T>* map(std::function<T(const T& element)> process) const override;
    LinkedList<T>* filter(std::function<bool(const T& element)> isFilteredMatch) const override;
    Iterator<T> begin() const;
    Iterator<T> end() const;
    T& operator[](int index) override;
    const T& operator[](int index) const override;
    LinkedList<T>& operator=(const List<T>& rightHandSideOperator) override;
    template <typename _T>
    friend bool operator==(const LinkedList<_T>& leftHandSideOperator, const LinkedList<_T>& rightHandSideOperator);
    template <typename _T>
    friend bool operator!=(const LinkedList<_T>& leftHandSideOperator, const LinkedList<_T>& rightHandSideOperator);
    template <typename _T>
    friend LinkedList<_T> operator+(const LinkedList<_T>& leftHandSideOperator, const LinkedList<_T>& rightHandSideOperator);
    ~LinkedList();
};

#include "LinkedList.inl"

#endif