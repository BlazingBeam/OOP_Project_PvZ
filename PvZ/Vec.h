#pragma once
#include <iostream>
using namespace std;

//custom vector class using templates to store any type of data
//its like a python list, using similar naming conventions like push and pop etc.



template <typename T>
class Vec {
private:
    T* data; // Pointer to dynamically allocated array
    int capacity; // Total capacity of the vector
    int count; // Number of elements in the vector

public:
    // Default constructor
    Vec() : data(nullptr), capacity(0), count(0) {}

    Vec(int capacity) : capacity(capacity), count(0) {
        data = new T[capacity];
    }

    // Copy constructor
    Vec(const Vec& other) : capacity(other.capacity), count(other.count) {
        data = new T[capacity];
        for (int i = 0; i < count; ++i) {
            data[i] = other.data[i];
        }
    }

    // Assignment operator
    Vec& operator=(const Vec& other) {
        if (this == &other) {
            return *this;
        }
        clear();
        capacity = other.capacity;
        count = other.count;
        data = new T[capacity];
        for (int i = 0; i < count; ++i) {
            data[i] = other.data[i];
        }
        return *this;
    }
    
    // Destructor
    ~Vec() {
        clear();
    }

    // Push element at the back
    void push(const T& element) {
        if (count >= capacity) {
            resize();
        }
        data[count++] = element;
    }

    // Pop element from the back
    void pop() {
        if (!empty()) {
            --count;
        }
    }

    // Push element at a specific index
    void pushAt(const T& element, int index) {
        if (index > count) {
            cout << "Index out of range at pushAt" << endl;
            cout << "Index: " << index << " Count: " << count << endl;
            exit(1);
        }
        if (count >= capacity) {
            resize();
        }
        for (int i = count; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = element;
        ++count;
    }

    void popAt(unsigned index) {
        if (index >= count) {
            cout << "Index out of range at popAt" << endl;
            cout << "Index: " << index << " Count: " << count << endl;
            exit(1);
        }
        for (unsigned i = index + 1; i < count; ++i) {
            data[i - 1] = data[i];
        }
        --count;
    }
    

    // Overload [] operator for access
    T& operator[](int index) {
        if (index >= count) {
            cout << "Index out of range at []" << endl;
            cout << "Index: " << index << " Count: " << count << endl;
            exit(1);
        }
        return data[index];
    }

    // Get capacity of the vector
    int size() {
        return count;
    }

    // Get number of elements in the vector
    int length() {
        return count;
    }

    // Check if vector is empty
    bool empty() const {
        return count == 0;
    }

    // Clear the vector and deallocate memory
    void clear() {
        delete[] data;
        data = nullptr;
        capacity = count = 0;
    }

    // Resize the vector to accommodate more elements
    void resize(int newCapacity = 0) {
        if (newCapacity == 0) {
            newCapacity = 1;
        }
        newCapacity = capacity + newCapacity;
        T* newData = new T[newCapacity];
        for (int i = 0; i < count; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

    // Print vector elements
    void print() const {
        for (int i = 0; i < count; ++i) {
            cout << data[i] << " ";
        }
        cout << endl;
    }

};
