#include <stdexcept>
#include <utility>


template <class T>
ListSequence<T>::ListSequence() : list() {}

template <class T>
ListSequence<T>::ListSequence(T* items, int count) :
    list(items, count) {}

template <class T>
ListSequence<T>::ListSequence(const LinkedList<T>& list) :
    list(list) {}

template <class T>
ListSequence<T>::ListSequence(const ListSequence<T>& other) : 
    list(other.list) {}

template <class T>
ListSequence<T>::ListSequence(ListSequence<T>&& other) noexcept :
    list(std::move(other.list)) {}

template <class T>
ListSequence<T>::ListSequence(LinkedList<T>&& list) :
    list(std::move(list)) {}
    // std::move меняет тип объекта на T&&, 
    // что позволяет использовать конструктор перемещения LinkedList<T>

template <class T>
ListSequence<T>::~ListSequence() = default;

template <class T>
T ListSequence<T>::getFirst() const {
    return list.getFirst();
}

template <class T>
T ListSequence<T>::getLast() const {
    return list.getLast();
}

template <class T>
T ListSequence<T>::get(int index) const {
    return list.get(index);
}

template <class T>
int ListSequence<T>::getSize() const { 
    return list.getSize();
}


template <class T>
void ListSequence<T>::appendInPlace(T item) {
    list.append(item);
}

template <class T>
void ListSequence<T>::prependInPlace(T item) {
    list.prepend(item);
}

template <class T>
void ListSequence<T>::insertAtInPlace(T item, int index) { 
    list.insertAt(item, index); 
}

template <class T>
Sequence<T>* ListSequence<T>::append(T item) {

    ListSequence<T>* result = static_cast<ListSequence<T>*>(this->instance());
    result->appendInPlace(item);
    return result;
}

template <class T>
Sequence<T>* ListSequence<T>::prepend(T item) {

    ListSequence<T>* result = static_cast<ListSequence<T>*>(this->instance());
    result->prependInPlace(item);
    return result;
}

template <class T>
Sequence<T>* ListSequence<T>::insertAt(T item, int index) {

    ListSequence<T>* result = static_cast<ListSequence<T>*>(this->instance());
    result->insertAtInPlace(item, index);
    return result;
}

template <class T>
Sequence<T>* ListSequence<T>::concat(const Sequence<T>* other) {

    if (other == nullptr) 
        throw std::invalid_argument("other sequence is null");

    ListSequence<T>* result = static_cast<ListSequence<T>*>(this->clone());

    IEnumerator<T>* enumerator = other->getEnumerator();
    while (enumerator->moveNext()) {
        result->appendInPlace(enumerator->getCurrent());
    }

    delete enumerator;
    return result;
}

template <class T>
Sequence<T>* MutableListSequence<T>::getSubSequence(int startIndex, int endIndex) const {

    LinkedList<T>* subList = this->list.getSubList(startIndex, endIndex);
    Sequence<T>* result = new MutableListSequence<T>(std::move(*subList));
    delete subList;
    return result;
}

template <class T>
Sequence<T>* ImmutableListSequence<T>::getSubSequence(int startIndex, int endIndex) const {

    LinkedList<T>* subList = this->list.getSubList(startIndex, endIndex);
    Sequence<T>* result = new ImmutableListSequence<T>(std::move(*subList));
    delete subList;
    return result;
}
// можно объединить в 1 функции (без копипаста)

template <class T>
IEnumerator<T>* ListSequence<T>::getEnumerator() const {
    return list.getEnumerator();
}
