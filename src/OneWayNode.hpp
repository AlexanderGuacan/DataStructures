#pragma once

#ifndef NODE_HPP
#define NODE_HPP

template <typename T>
class OneWayNode {
    private:
        T mElement{};
        OneWayNode* mNext{};
    
    public:
        OneWayNode(const T& element, OneWayNode* nextNode = nullptr);
        const T& getElement() const;
        OneWayNode* const& getNextNode() const;
        void setElement(const T& element);
        void setNextNode(OneWayNode* node);
        ~OneWayNode();
};

#include "OneWayNode.inl"

#endif