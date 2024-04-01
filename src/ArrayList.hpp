#pragma once

#ifndef ARRAY_LIST_HPP
#define ARRAY_LIST_HPP

#include "List.hpp"
#include <initializer_list>

template <typename T>
class ArrayList : public List<T> {
    private:
    int defaultCapacity{};
    int capacity{};
    int increase{};
    T* array{};

    void copy(const List<T>& list) override;
    bool isFull();
    bool hasUnusedIncrease();
    void increaseArrayCapacity();
    void decreaseArrayCapacity();
    void resizeArray();

    public:

    ArrayList(int capacity, int increase = 10);
    ArrayList(std::initializer_list<T> list);
    ArrayList(const ArrayList<T>& list);
    int getCapacity() const;
    void setIncrease(int newIncrease);
    void clear() override;
    void addAtBegin(const T& element) override;
    void addAtEnd(const T& element) override;
    void addToIndex(const T& element, int index) override;
    T removeFirst() override;
    T removeLast() override;
    T removeAtIndex(int index) override;
    void forEach(std::function<void(const T& element)> callback) const override;
    ArrayList<T>* map(std::function<T(const T& element)> process) const override;
    ArrayList<T>* filter(std::function<bool(const T& element)> isFilteredMatch) const override;
    T* begin() const;
    T* end() const;
    T& operator[](int index) override;
    const T& operator[](int index) const override;
    ArrayList<T>& operator=(const List<T>& rightHandSideOperator) override;
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