#pragma once
#include "IEnumerator.h"

template <class T>
class DynamicArray {
private:
    class DynamicArrayEnumerator : public IEnumerator<T> {
    private:
        const DynamicArray<T>& array;
        int currentIndex;
    public:
        explicit DynamicArrayEnumerator(const DynamicArray<T>& array);
        bool moveNext() override;
        T getCurrent() const override;
        void reset() override;
    };

    T* data;
    int size;
    int capacity;

public:
    DynamicArray(int size);
    DynamicArray(T* items, int count);
    DynamicArray(const DynamicArray<T>& other);
    ~DynamicArray();

    T get(int index) const;
    void set(T value, int index);
    int getSize() const;
    void resize(int newSize);

    T& operator[](int index);
    const T& operator[](int index) const;

    IEnumerator<T>* getEnumerator() const;
};

#include "DynamicArray.tpp"
