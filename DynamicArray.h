#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

template <typename T>
class DynamicArray {
private:
    T *data;        // the array
    int count;      // how many items are stored
    int capacity;   // how many items the array can hold

    // Makes the array twice as big when it is full
    void grow() {
        capacity = capacity * 2;
        T *newData = new T[capacity];

        for (int i = 0; i < count; i++) {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
    }

public:
    // Constructor: starts with space for 10 items
    DynamicArray() {
        capacity = 10;
        count = 0;
        data = new T[capacity];
    }

    // Copy constructor: makes a separate copy of the array.
    // Used when sorting a copy so the original order stays the same.
    DynamicArray(const DynamicArray &other) {
        capacity = other.capacity;
        count = other.count;
        data = new T[capacity];

        for (int i = 0; i < count; i++) {
            data[i] = other.data[i];
        }
    }

    // Assignment: same idea as the copy constructor
    DynamicArray& operator=(const DynamicArray &other) {
        if (this != &other) {
            delete[] data;
            capacity = other.capacity;
            count = other.count;
            data = new T[capacity];

            for (int i = 0; i < count; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    // Destructor: frees the memory
    ~DynamicArray() {
        delete[] data;
    }

    int size() const {
        return count;
    }

    bool empty() const {
        return count == 0;
    }

    // arr[i] gives the item at a position (0 is the first)
    T& operator[](int index) {
        return data[index];
    }

    const T& operator[](int index) const {
        return data[index];
    }
    
    void clear() {
        count = 0;
    }  
    // Add an item at the end
    void push_back(const T &value) {
        if (count == capacity) {
            grow();
        }
        data[count] = value;
        count++;
    }

    // Put an item at a position and move the others to the right
    void insertAt(int index, const T &value) {
        if (count == capacity) {
            grow();
        }

        for (int i = count; i > index; i--) {
            data[i] = data[i - 1];
        }

        data[index] = value;
        count++;
    }

    // Remove the item at a position and move the others to the left
    void removeAt(int index) {
        for (int i = index; i < count - 1; i++) {
            data[i] = data[i + 1];
        }
        count--;
    }
};


#endif
