#pragma once

#include "Sequence.h"
#include "LinkedList.h"

template <class T>
class ListSequence : public Sequence<T> {
protected:
    LinkedList<T> list;

    Sequence<T>* clone() const override = 0;
    Sequence<T>* instance() override = 0;

    void appendInPlace(T item) override;
    void prependInPlace(T item) override;
    void insertAtInPlace(T item, int index) override;

public:
    ListSequence();
    ListSequence(T* items, int count);
    ListSequence(const LinkedList<T>& list);
    ListSequence(const ListSequence<T>& other);
    ListSequence(ListSequence<T>&& other) noexcept; // Конструктор перемещения
    ListSequence(LinkedList<T>&& list); // Конструктор перемещения для типа LinkedList  
    // Для оптимизации getSubSequence (чтобы не было лишнего копипаста)

    ~ListSequence() override;

    T getFirst() const override;
    T getLast() const override;
    T get(int index) const override;
    int getSize() const override;

    virtual Sequence<T>* append(T item) override;
    virtual Sequence<T>* prepend(T item) override;
    virtual Sequence<T>* insertAt(T item, int index) override;

    virtual Sequence<T>* concat(const Sequence<T>* other) override;
    virtual Sequence<T>* getSubSequence(int startIndex, int endIndex) const override = 0;

    Sequence<T>* from(int startIndex, int endIndex) const override;
    Sequence<T>* map(T (*func)(T)) const override;
    T reduce(T (*func)(T, T), T initial) const override;

    IEnumerator<T>* getEnumerator() const override;
};


template <class T>
class MutableListSequence : public ListSequence<T> {
protected:
    Sequence<T>* clone() const override {
        return new MutableListSequence<T>(*this);
    }

    Sequence<T>* instance() override {
        return this;
    }

public:
    using ListSequence<T>::ListSequence;

    Sequence<T>* getSubSequence(int startIndex, int endIndex) const override;
};

template <class T>
class ImmutableListSequence : public ListSequence<T> {
protected:
    Sequence<T>* clone() const override {
        return new ImmutableListSequence<T>(*this);
    }

    Sequence<T>* instance() override {
        return this->clone();
    }

public:
    using ListSequence<T>::ListSequence;

    Sequence<T>* getSubSequence(int startIndex, int endIndex) const override;
};

#include "ListSequence.tpp"
