/**
 * \file StackADT.cpp
 * \author Emily Horsman <horsmane@mcmaster.ca>
 */
#include "Exceptions.h"
#include "CardADT.h"
#include "StackADT.h"


template <class T>
Stack<T>::Stack() : m_capacity(0) {}


template <class T>
Stack<T>::Stack(int capacity) :
    m_s(),
    m_capacity(capacity)
{
    if (capacity <= 0) {
        throw invalid_capacity();
    }
}


template <class T>
bool Stack<T>::isEmpty() const {
    return m_s.size() == 0;
}


template <class T>
bool Stack<T>::isFull() const {
    return m_s.size() == m_capacity;
}


template <class T>
int Stack<T>::capacity() const {
    return m_capacity;
}


template <class T>
void Stack<T>::push(const T v) {
    if (isFull()) {
        throw full();
    }

    m_s.push_back(v);
}


template <class T>
T Stack<T>::peek() const {
    if (isEmpty()) {
        throw empty();
    }

    return m_s.back();
}


template <class T>
void Stack<T>::pop() {
    if (isEmpty()) {
        throw empty();
    }

    m_s.pop_back();
}


template <class T>
std::vector<T> Stack<T>::seq() const {
    return std::vector<T>(m_s.cbegin(), m_s.cend());
}


template class Stack<int>;
template class Stack<CardT>;
