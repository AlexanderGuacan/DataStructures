#pragma once

#ifndef TWO_WAY_NODE_HPP
#define TWO_WAY_NODE_HPP

template <typename T>
class TwoWayNode {
    private:
        T mElement{};
        TwoWayNode* mPrevious{};
        TwoWayNode* mNext{};

    public:
        TwoWayNode(const T& element, TwoWayNode* previous = nullptr, TwoWayNode* next = nullptr);
        const T& getElement() const;
        TwoWayNode* const& getNextNode() const;
        TwoWayNode* const& getPreviousNode() const;
        void setElement(const T& element);
        void setNextNode(TwoWayNode* node);
        void setPreviousNode(TwoWayNode* node);
        ~TwoWayNode();
};

#include "TwoWayNode.inl"

#endif