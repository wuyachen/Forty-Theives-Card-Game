/**
 * \file StackADT.h
 * \author Emily Horsman <horsmane@mcmaster.ca>
 * \brief Provides an abstract data type (ADT) for a first-in-last-out data
 *   structure with an optional bound/capacity.
 */
#ifndef STACK_ADT_H
#define STACK_ADT_H

#include <vector>


/**
 * \brief ADT for a first-in-last-out data structure with an optionally bounded
 *   capacity.
 */
template <class T>
class Stack {
    private:
        std::vector<T> m_s;
        int m_capacity;

    public:
        /**
         * \brief Default constructor for Stack. This Stack cannot take any
         * items.
         *
         * \details This is a language-specific implementation detail and is
         * deliberately not in the specification. It should not be used.
         */
        Stack();

        /**
         * \brief Constructs a new Stack instance with a bounded capacity.
         * \param capacity The maximum number of items which can be in this
         *   stack.
         * \throws invalid_capacity if the capacity is not a natural number
         *   greater than 0.
         */
        Stack(int capacity);

        /**
         * \brief Returns true if the stack has no items in it.
         */
        bool isEmpty() const;

        /**
         * \brief Returns true if the stack cannot accept any more items.
         */
        bool isFull() const;

        /**
         * \brief Returns the capacity of this stack.
         */
        int capacity() const;

        /**
         * \brief Adds an item to the stack.
         * \param v The item to add to the top of the stack.
         * \throws full if the stack cannot accept any more items.
         */
        void push(const T v);

        /**
         * \brief Returns the item on the top of the stack.
         * \throws empty if the stack does not contain any items.
         */
        T peek() const;

        /**
         * \brief Removes the element at the top of the stack.
         * \throws empty if the stack does not contain any items.
         */
        void pop();

        /**
         * \brief Returns a sequence of the members of this stack.
         * \details The first item was the first item inserted. The last item
         *   is the first item that would be popped off. This getter is
         *   intended for a View module to translate state into view.
         * \returns A copy of the sequence.
         */
        std::vector<T> seq() const;
};

#endif
