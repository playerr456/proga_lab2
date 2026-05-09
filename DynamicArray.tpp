#include <stdexcept>


template <class T>
DynamicArray<T>::DynamicArray(int size) {

    if (size < 0) 
        throw std::invalid_argument("size must be non-negative");

    this->size = size;
    this->capacity = size;
    data = capacity ? new T[capacity]{} : nullptr; 
}

template <class T>
DynamicArray<T>::DynamicArray(T* items, int count) {

    if (count < 0) 
        throw std::invalid_argument("count must be non-negative");

    if (count > 0 and items == nullptr) 
        throw std::invalid_argument("items must be not null when count is positive");

    size = count;
    capacity = count;
    data = capacity ? new T[capacity] : nullptr; 

    for (int i = 0; i < count; ++ i) 
        data[i] = items[i];
}

template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& other) {

    this->size = other.size;
    this->capacity = other.capacity;
    this->data = this->capacity ? new T[this->capacity] : nullptr;

    for (int i = 0; i < other.size; ++ i) 
        this->data[i] = other.data[i];
}

template <class T>
DynamicArray<T>::~DynamicArray() {
    delete[] data;
}


template <class T>
T DynamicArray<T>::get(int index) const {

    if (index < 0 or index >= size)
        throw std::out_of_range("index is out of range");

    return data[index];
}

template <class T>
void DynamicArray<T>::set(T value, int index) {

    if (index < 0 or index >= size)
        throw std::out_of_range("index is out of range");

    data[index] = value; 
}

template <class T>
int DynamicArray<T>::getSize() const {
    return size;
}

template <class T>
void DynamicArray<T>::resize(int newSize) {

    if (newSize < 0)
        throw std::invalid_argument("size must be non-negative");

    if (newSize <= capacity) {
        if (newSize > size) {
            for (int i = size; i < newSize; ++ i) 
                data[i] = T{};
        }
        size = newSize;
        return;
    }

    int newCapacity = capacity == 0 ? 1 : capacity;
    while (newCapacity < newSize) {
        newCapacity *= 2;
    }

    T* newData = new T[newCapacity]{};

    for (int i = 0; i < size; ++ i)
        newData[i] = data[i]; 

    delete[] data;
    data = newData;
    size = newSize;
    capacity = newCapacity;
}


template <class T>
T& DynamicArray<T>::operator[](int index) {

    if (index < 0 or index >= size)
        throw std::out_of_range("index is out of range");

    return data[index];
}

template <class T>
const T& DynamicArray<T>::operator[](int index) const {

    if (index < 0 or index >= size)
        throw std::out_of_range("index is out of range");

    return data[index];
}


template <class T>
DynamicArray<T>::DynamicArrayEnumerator::DynamicArrayEnumerator(const DynamicArray<T>& array) :
    array(array), currentIndex(-1) {}

template <class T>
bool DynamicArray<T>::DynamicArrayEnumerator::moveNext() {

    if (currentIndex + 1 < array.getSize()) {
        ++ currentIndex;
        return true;
    }

    currentIndex = array.getSize();
    return false;
}

template <class T>
T DynamicArray<T>::DynamicArrayEnumerator::getCurrent() const {

    if (currentIndex < 0 or currentIndex >= array.getSize())
        throw std::out_of_range("enumerator is not on a valid element");

    return array.get(currentIndex);
}

template <class T>
void DynamicArray<T>::DynamicArrayEnumerator::reset() {
    currentIndex = -1;
}

template <class T>
IEnumerator<T>* DynamicArray<T>::getEnumerator() const {
    return new DynamicArrayEnumerator(*this);
}
