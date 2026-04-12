#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdexcept>

template <typename T>
class DynamicArray {
private:
    T* data;
    int capacity;
    int size;

    // doubles the capacity
    void resize();

public:
    DynamicArray(); // default constructor
    ~DynamicArray(); // destructor

    void add(T item); // appends item to the end of the array
    T get(int index) const ; // returns the element at index
    T& operator[](int index); // returns a reference to the element at index
    void set(int index, T item); // replaces the element at index with item
    void removeAt(int index); // removes the element at index
    int getSize()const ; // returns the number of elements
    bool isEmpty() const ; // returns true if the array is empty
};

template <typename T>
DynamicArray<T>::DynamicArray() {
    capacity = 4;
    size = 0;
    data = new T[capacity];
}

template <typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] data;
}

template <typename T>
void DynamicArray<T>::resize() {
    capacity *= 2;
    T* newData = new T[capacity];

    for (int i = 0; i < size; i++)
        newData[i] = data[i];

    delete[] data;
    data = newData;
}

template <typename T>
void DynamicArray<T>::add(T item) {
    // resize if full
    if (size == capacity)
        resize();

    data[size] = item;
    
    // update size
    size++;
}

template <typename T>
T DynamicArray<T>::get(int index) const {
    if (index < 0 || index > size - 1)
        throw std::out_of_range("Index out of range");

    return data[index];
}

template <typename T>
T& DynamicArray<T>::operator[](int index) {
    if (index < 0 || index >= size)
        throw std::out_of_range("Index out of range");

    return data[index];
}

template <typename T>
void DynamicArray<T>::set(int index, T item) {
    if (index < 0 || index > size - 1)
        throw std::out_of_range("Index out of range");

    data[index] = item;
}

template <typename T>
void DynamicArray<T>::removeAt(int index) {
    if (index < 0 || index > size - 1)
        throw std::out_of_range("Index out of range");

    // shift left
    for (int i = index; i < size - 1; i++)
        data[i] = data[i + 1];

    // update size
    size--;
}

template <typename T>
int DynamicArray<T>::getSize() const {
    return size;
}

template <typename T>
bool DynamicArray<T>::isEmpty() const {
    return size == 0;
}

#endif