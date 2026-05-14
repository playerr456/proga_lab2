#pragma once

#include "IEnumerable.h"

template <class T>
class Sequence : public IEnumerable<T> {
protected:
    virtual Sequence<T>* instance() = 0;
    virtual Sequence<T>* clone() const = 0;

    virtual void appendInPlace(T item) = 0;
    virtual void prependInPlace(T item) = 0;
    virtual void insertAtInPlace(T item, int index) = 0; // лучше использовать ссылки

public:
    virtual ~Sequence() = default;

    virtual T getFirst() const = 0;
    virtual T getLast() const = 0;
    virtual T get(int index) const = 0;
    virtual int getSize() const = 0;

    virtual Sequence<T>* append(T item) = 0;
    virtual Sequence<T>* prepend(T item) = 0;
    virtual Sequence<T>* insertAt(T item, int index) = 0; // лучше использовать ссылки

    virtual Sequence<T>* getSubSequence(int startIndex, int endIndex) const = 0;
    virtual Sequence<T>* concat(const Sequence<T>* other) = 0;

    virtual Sequence<T>* from(int startIndex, int endIndex) const = 0;
    virtual Sequence<T>* where(bool (*func)(T)) const = 0;
    virtual Sequence<T>* map(T (*func)(T)) const = 0;
    virtual T reduce(T (*func)(T, T), T initial) const = 0;

    IEnumerator<T>* getEnumerator() const override = 0;
};
