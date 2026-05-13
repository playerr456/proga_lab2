#pragma once
#include "IEnumerator.h"

template <class T>
class LinkedList {
private:
    struct Node {
        T value;
        Node* next;

        Node(const T& value, Node* next = nullptr) : 
            value(value), next(next) {}
    };

    class LinkedListEnumerator : public IEnumerator<T> {
    private:
        Node* head;
        Node* current;
        bool started;
    public:
        explicit LinkedListEnumerator(Node* head);
        bool moveNext() override;
        T getCurrent() const override;
        void reset() override;
    };

    Node* head;
    Node* tail;
    int size;

public:
    LinkedList();
    LinkedList(T* items, int count);
    LinkedList(const LinkedList<T>& other);
    LinkedList(LinkedList<T>&& other) noexcept; // Конструктор перемещения
    // (Для списка не нужен конструктор подсписка, так как уже есть метод getSubList())

    ~LinkedList();

    T getFirst() const;
    T getLast() const;
    T get(int index) const;
    int getSize() const;

    void append(T value); 
    void prepend(T value); 
    void insertAt(T value, int index); 

    LinkedList<T>* getSubList(int startIndex, int endIndex) const; 
    LinkedList<T>* concat(LinkedList<T>* other); 

    IEnumerator<T>* getEnumerator() const;
};

#include "LinkedList.tpp"
