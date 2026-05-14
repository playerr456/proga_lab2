#include <stdexcept>
#include <utility>


template <class T>
ArraySequence<T>::ArraySequence() : array(0) {}

template <class T>
ArraySequence<T>::ArraySequence(T* items, int count) :
    array(items, count) {}

template <class T>
ArraySequence<T>::ArraySequence(const DynamicArray<T>& array) :
    array(array) {}

template <class T>
ArraySequence<T>::ArraySequence(const ArraySequence<T>& other) :
    array(other.array) {}

template <class T>
ArraySequence<T>::ArraySequence(ArraySequence<T>&& other) noexcept :
    array(std::move(other.array)) {}

template <class T>
ArraySequence<T>::ArraySequence(const DynamicArray<T>& array, int startIndex, int count) :
    array(array, startIndex, count) {}

template <class T>
ArraySequence<T>::~ArraySequence() = default;


template <class T>
T ArraySequence<T>::getFirst() const {

    if (!array.getSize())
        throw std::out_of_range("sequence is empty");

    return array.get(0);
}

template <class T>
T ArraySequence<T>::getLast() const {

    if (!array.getSize())
        throw std::out_of_range("sequence is empty");

    return array.get(array.getSize() - 1);
}

template <class T>
T ArraySequence<T>::get(int index) const {
    return array.get(index);
}

template <class T>
int ArraySequence<T>::getSize() const {
    return array.getSize();
}


template <class T>
void ArraySequence<T>::appendInPlace(T item) {

    int oldSize = array.getSize(); 
    array.resize(oldSize + 1);
    array.set(item, oldSize);
}

template <class T>
void ArraySequence<T>::prependInPlace(T item) {
    
    int oldSize = array.getSize();
    array.resize(oldSize + 1);

    for (int i = oldSize; i > 0; -- i)
        array[i] = std::move(array[i - 1]);

    array.set(item, 0);
}

template <class T>
void ArraySequence<T>::insertAtInPlace(T item, int index) {
    int oldSize = array.getSize();

    if (index < 0 or index >= oldSize)
        throw std::out_of_range("index is out of range");

    array.resize(oldSize + 1);

    for (int i = oldSize; i > index; -- i)
        array[i] = std::move(array[i - 1]);

    array.set(item, index);
}

template <class T>
Sequence<T>* ArraySequence<T>::append(T item) {

    ArraySequence<T>* result = static_cast<ArraySequence<T>*>(this->instance());
    result->appendInPlace(item);
    return result;
}

template <class T>
Sequence<T>* ArraySequence<T>::prepend(T item) {

    ArraySequence<T>* result = static_cast<ArraySequence<T>*>(this->instance());
    result->prependInPlace(item);
    return result;
}

template <class T>
Sequence<T>* ArraySequence<T>::insertAt(T item, int index) {

    ArraySequence<T>* result = static_cast<ArraySequence<T>*>(this->instance());
    result->insertAtInPlace(item, index);
    return result;
}

template <class T>
Sequence<T>* ArraySequence<T>::concat(const Sequence<T>* other) {

    if (other == nullptr)
        throw std::invalid_argument("other sequence is null");

    ArraySequence<T>* result = static_cast<ArraySequence<T>*>(this->clone());

    IEnumerator<T>* enumerator = other->getEnumerator();
    while (enumerator->moveNext()) {
        result->appendInPlace(enumerator->getCurrent());
    }

    delete enumerator;
    return result;
}

template <class T>
Sequence<T>* MutableArraySequence<T>::getSubSequence(int startIndex, int endIndex) const {

    int count = endIndex - startIndex;
    return new MutableArraySequence<T>(this->array, startIndex, count);
}

template <class T>
Sequence<T>* ImmutableArraySequence<T>::getSubSequence(int startIndex, int endIndex) const {

    int count = endIndex - startIndex;
    return new ImmutableArraySequence<T>(this->array, startIndex, count);
}


template <class T>
IEnumerator<T>* ArraySequence<T>::getEnumerator() const {
    return array.getEnumerator();
}


template <class T>
Sequence<T>* ArraySequence<T>::from(int startIndex, int endIndex) const {
    return this->getSubSequence(startIndex, endIndex);
}

template <class T>
Sequence<T>* ArraySequence<T>::map(T (*func)(T)) const {

    ArraySequence<T>* result = static_cast<ArraySequence<T>*>(this->clone());

    for (int i = 0; i < getSize(); ++ i) 
        result->array.set(func(get(i)), i);
    
    return result;
}

template <class T>
T ArraySequence<T>::reduce(T (*func)(T, T), T initial) const {

    T result = initial;
    
    for (int i = 0; i < getSize(); ++ i) 
        result = func(result, get(i));
    
    return result;
}
