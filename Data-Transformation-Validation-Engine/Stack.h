#ifndef STACK_H
#define STACK_H

#include <stdexcept>

template <typename T>
class Stack {
private:
    T* elements;
    int top;
    int capacity;
    
    // doubles the capacity
    void resize();

public:
    Stack(); // default constructor
    ~Stack(); // destructor
    Stack(const Stack<T>& other); // copy constructor
    Stack<T>& operator=(const Stack<T>& other); // assignment operator

    void push(T item); // pushes item onto the stack
    T pop(); // removes the top item and returns it
    T peek(); // returns the top item
    bool isEmpty(); // if stack is empty, the record is valid
    int getSize(); // return the number of elements
};

template <typename T>
Stack<T>::Stack() {
    // default capacity
    capacity = 4;
    top = -1;
    elements = new T[capacity];
}

template <typename T>
Stack<T>::~Stack() {
    delete[] elements;
}

template <typename T>
Stack<T>::Stack(const Stack<T>& other) {
    capacity = other.capacity;
    top = other.top;
    elements = new T[capacity];

    for (int i = 0; i <= top; i++)
        elements[i] = other.elements[i];
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other) {
    if (this == &other) return *this;

    delete[] elements;

    capacity = other.capacity;
    top = other.top;
    elements = new T[capacity];
    
    for (int i = 0; i <= top; i++)
        elements[i] = other.elements[i];

    return *this;
}

template <typename T>
void Stack<T>::resize() {
    capacity *= 2;
    T* newElements = new T[capacity];

    for (int i = 0; i < top + 1; i++)
        newElements[i] = elements[i];

    delete[] elements;
    elements = newElements;
}

template <typename T>
void Stack<T>::push(T item) {
    // resize if full
    if (top + 1 == capacity)
        resize();

    elements[++top] = item;
}

template <typename T>
T Stack<T>::pop() {
    if (isEmpty())
        throw std::runtime_error("Stack is empty");

    return elements[top--];
}

template <typename T>
T Stack<T>::peek() {
    if (isEmpty())
        throw std::runtime_error("Stack is empty");

    return elements[top];
}

template <typename T>
bool Stack<T>::isEmpty() {
    return top == -1;
}

template <typename T>
int Stack<T>::getSize() {
    return top + 1;
}

#endif