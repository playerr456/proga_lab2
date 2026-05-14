#pragma once

#include "Sequence.h"
#include "DynamicArray.h"

template <class T>
class ArraySequence : public Sequence<T> {
protected:
    DynamicArray<T> array;

    Sequence<T>* clone() const override = 0;
    Sequence<T>* instance() override = 0;

    void appendInPlace(T item) override;
    void prependInPlace(T item) override;
    void insertAtInPlace(T item, int index) override;

public:
    ArraySequence();
    ArraySequence(T* items, int count);
    ArraySequence(const DynamicArray<T>& array);
    ArraySequence(const ArraySequence<T>& other);
    ArraySequence(ArraySequence<T>&& other) noexcept; // Конструктор перемещения
    ArraySequence(const DynamicArray<T>& array, int startIndex, int count); 
    // Конструктор подмассива (для оптимизации getSubSequence)

    ~ArraySequence() override;

    T getFirst() const override;
    T getLast() const override;
    T get(int index) const override;
    int getSize() const override;

    Sequence<T>* append(T item) override;
    Sequence<T>* prepend(T item) override;
    Sequence<T>* insertAt(T item, int index) override;

    virtual Sequence<T>* getSubSequence(int startIndex, int endIndex) const override = 0;
    Sequence<T>* concat(const Sequence<T>* other) override;

    Sequence<T>* from(int startIndex, int endIndex) const override;
    Sequence<T>* where(bool (*func)(T)) const override;
    Sequence<T>* map(T (*func)(T)) const override;
    T reduce(T (*func)(T, T), T initial) const override;

    IEnumerator<T>* getEnumerator() const override;
};

template <class T>
class MutableArraySequence : public ArraySequence<T> {
protected:
    Sequence<T>* clone() const override {
        return new MutableArraySequence<T>(*this);
    }

    Sequence<T>* instance() override {
        return this;
    }

public:
    using ArraySequence<T>::ArraySequence;

    Sequence<T>* getSubSequence(int startIndex, int endIndex) const override;
};

template <class T>
class ImmutableArraySequence : public ArraySequence<T> {
protected:
    Sequence<T>* clone() const override {
        return new ImmutableArraySequence<T>(*this);
    }

    Sequence<T>* instance() override {
        return this->clone();
    }

public:
    using ArraySequence<T>::ArraySequence;

    Sequence<T>* getSubSequence(int startIndex, int endIndex) const override;
};

#include "ArraySequence.tpp"
