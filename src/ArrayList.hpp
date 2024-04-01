#pragma once

#ifndef ARRAY_LIST_HPP
#define ARRAY_LIST_HPP

#include <initializer_list>
#include <functional>

template <typename T>
class ArrayList {
    private:
    int defaultCapacity{};
    int capacity{};
    int increase{};
    int length{};
    T* array{};

    void copy(const ArrayList& list);
    bool isOutOfBounded(int index);
    bool isFull();
    bool hasUnusedIncrease();
    void increaseArrayCapacity();
    void decreaseArrayCapacity();
    void resizeArray();

    public:

    ArrayList(int capacity, int increase = 10);
    ArrayList(std::initializer_list<T> list);
    ArrayList(const ArrayList& list);
    int getLength() const;
    int getCapacity() const;
    void setIncrease(int newIncrease);
    bool isEmpty() const;
    void clear();
    void addAtBegin(const T& element);
    void addAtEnd(const T& element);
    void addToIndex(const T& element, int index);
    T removeFirst();
    T removeLast();
    T removeAtIndex(int index);
    void forEach(std::function<void(const T& element)> callback) const;
    ArrayList map(std::function<T(const T& element)> process) const;
    ArrayList filter(std::function<bool(const T& element)> isFilteredMatch) const;
    T* begin() const;
    T* end() const;
    T& operator[](int index);
    ArrayList& operator=(const ArrayList& rightHandSideOperator);
    template <typename _T>
    friend bool operator==(const ArrayList<_T>& leftHandSideOperator, const ArrayList<_T>& rightHandSideOperator);
    template <typename _T>
    friend bool operator!=(const ArrayList<_T>& leftHandSideOperator, const ArrayList<_T>& rightHandSideOperator);
    template <typename _T>
    friend ArrayList<_T> operator+(const ArrayList<_T>& leftHandSideOperator, const ArrayList<_T>& rightHandSideOperator);
    ~ArrayList();
};

#include "ArrayList.inl"

#endif