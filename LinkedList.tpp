#include <stdexcept>
#include <utility>


template <class T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), size(0) {}

template <class T>
LinkedList<T>::LinkedList(T* items, int count) {

    if (count < 0) 
        throw std::invalid_argument("count must be non-negative");

    if (count > 0 and items == nullptr) 
        throw std::invalid_argument("items must be not null when count is positive");

    head = nullptr;
    tail = nullptr;
    size = 0;

    for (int i = 0; i < count; ++ i) 
        this->append(items[i]);
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) {
    
    head = nullptr;
    tail = nullptr;
    size = 0;

    Node* current = other.head;

    while (current) {
        this->append(current->value);
        current = current->next;
    }
}

template <class T>
LinkedList<T>::LinkedList(LinkedList<T>&& other) noexcept :
    head(other.head), tail(other.tail), size(other.size) {
    
    other.head = nullptr;
    other.tail = nullptr;
    other.size = 0;
}

template <class T>
LinkedList<T>::~LinkedList() {
    Node* current = head;

    while (current) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }

    head = nullptr;
    tail = nullptr;
    size = 0;
}


template <class T>
T LinkedList<T>::getFirst() const {

    if (!size)
        throw std::out_of_range("list is empty");

    return head->value; 
}

template <class T>
T LinkedList<T>::getLast() const {

    if (!size)
        throw std::out_of_range("list is empty");

    return tail->value; 
}

template <class T>
T LinkedList<T>::get(int index) const {

    if (index < 0 or index >= size)
        throw std::out_of_range("index is out of range");

    Node* current = head;

    for (int i = 0; i < index; ++ i)
        current = current->next;

    return current->value;
}

template <class T>
int LinkedList<T>::getSize() const {
    return size;
}


template <class T>
void LinkedList<T>::append(T value) {

    Node* newNode = new Node(value);

    if (head) {
        tail->next = newNode;
        tail = newNode;
    }
    else {
        head = newNode;
        tail = newNode;
    }
    ++ size;
}

template <class T>
void LinkedList<T>::prepend(T value) {

    Node* newNode = new Node(value);

    if (head) {
        newNode->next = head;
        head = newNode;
    }
    else {
        head = newNode;
        tail = newNode;
    }
    ++ size;
}

template <class T>
void LinkedList<T>::insertAt(T value, int index) {

    if (index < 0 or index >= size)
        throw std::out_of_range("index is out of range");

    if (!index) {
        prepend(value);
        return;
    }

    Node* current = head;

    for (int i = 0; i < index - 1; ++ i) 
        current = current->next;

    Node* newNode = new Node(value, current->next);
    current->next = newNode;
    ++ size;
}

template <class T> 
LinkedList<T>* LinkedList<T>::getSubList(int startIndex, int endIndex) const {

    if (startIndex < 0 or startIndex >= size)
        throw std::out_of_range("index is out of range");

    if (endIndex < 0 or endIndex > size)
        throw std::out_of_range("index is out of range");

    if (startIndex > endIndex)
        throw std::out_of_range("start index cant be greater than end index");

    Node* current = head;

    for (int i = 0; i < startIndex; ++ i)
        current = current->next;

    LinkedList<T>* newLinkedList = new LinkedList<T>();

    for (int i = startIndex; i < endIndex; ++ i) {
        newLinkedList->append(current->value);
        current = current->next;
    }

    return newLinkedList;
}

template <class T>
LinkedList<T>* LinkedList<T>::concat(LinkedList<T>* other) {

    if (!other)
        throw std::invalid_argument("list must be not null");

    LinkedList<T>* newLinkedList = new LinkedList<T>(*this);
    Node* current = other->head;

    while (current) {
        newLinkedList->append(current->value);
        current = current->next;
    }

    return newLinkedList;
}

template <class T>
LinkedList<T>::LinkedListEnumerator::LinkedListEnumerator(Node* head) :
    head(head), current(nullptr), started(false) {}

template <class T>
bool LinkedList<T>::LinkedListEnumerator::moveNext() {

    if (!started) {
        current = head;
        started = true;
    } 
    else if (current) {
        current = current->next;
    }

    return current;
}

template <class T>
T LinkedList<T>::LinkedListEnumerator::getCurrent() const {

    if (!current)
        throw std::out_of_range("enumerator is not on a valid element");

    return current->value;
}

template <class T>
void LinkedList<T>::LinkedListEnumerator::reset() {
    current = nullptr;  started = false;
}

template <class T>
IEnumerator<T>* LinkedList<T>::getEnumerator() const {
    return new LinkedListEnumerator(head);
}
