#include <iostream>
#include <cassert>
#include <stdexcept>

#include "ArraySequence.h"
#include "ListSequence.h"

void testDynamicArray() {
    std::cout << "Testing DynamicArray..." << std::endl;
    DynamicArray<int> arr(5);
    assert(arr.getSize() == 5);
    arr.set(10, 0);
    assert(arr.get(0) == 10);
    arr.resize(10);
    assert(arr.getSize() == 10);
    arr.set(20, 9);
    assert(arr.get(9) == 20);
}

void testLinkedList() {
    std::cout << "Testing LinkedList..." << std::endl;
    LinkedList<int> list;
    list.append(1);
    list.append(2);
    list.prepend(0);
    assert(list.getSize() == 3);
    assert(list.get(0) == 0);
    assert(list.get(1) == 1);
    assert(list.get(2) == 2);
}

void testMutableArraySequence() {
    std::cout << "Testing MutableArraySequence..." << std::endl;
    Sequence<int>* seq = new MutableArraySequence<int>();
    seq->append(1);
    seq->append(2);
    assert(seq->getSize() == 2);
    
    Sequence<int>* res = seq->prepend(0);
    assert(res == seq); 
    assert(seq->get(0) == 0);
    assert(seq->getSize() == 3);
    
    delete seq;
}

void testImmutableArraySequence() {
    std::cout << "Testing ImmutableArraySequence..." << std::endl;
    Sequence<int>* seq = new ImmutableArraySequence<int>();
    Sequence<int>* next1 = seq->append(1); 
    assert(next1 != seq); 
    assert(seq->getSize() == 0);
    assert(next1->getSize() == 1);
    
    Sequence<int>* next2 = next1->append(2);
    assert(next2 != next1);
    assert(next2->getSize() == 2);
    assert(next2->get(1) == 2);
    
    delete seq;
    delete next1;
    delete next2;
}

void testMutableListSequence() {
    std::cout << "Testing MutableListSequence..." << std::endl;
    Sequence<int>* seq = new MutableListSequence<int>();
    seq->append(10);
    seq->append(20);
    assert(seq->getSize() == 2);
    assert(seq->get(1) == 20);
    
    seq->insertAt(15, 1);
    assert(seq->get(1) == 15);
    assert(seq->getSize() == 3);
    
    delete seq;
}

void testImmutableListSequence() {
    std::cout << "Testing ImmutableListSequence..." << std::endl;
    Sequence<int>* seq = new ImmutableListSequence<int>();
    Sequence<int>* next = seq->append(100);
    assert(next != seq);
    assert(next->get(0) == 100);
    
    delete seq;
    delete next;
}

void testSubSequenceAndConcat() {
    std::cout << "Testing SubSequence and Concat..." << std::endl;
    int data[] = {1, 2, 3, 4, 5};
    MutableArraySequence<int> seq(data, 5);
    
    Sequence<int>* sub = seq.getSubSequence(1, 4);
    assert(sub->getSize() == 3);
    assert(sub->get(0) == 2);
    assert(sub->get(2) == 4);
    
    int data2[] = {6, 7};
    MutableArraySequence<int> seq2(data2, 2);
    Sequence<int>* combined = seq.concat(&seq2);
    
    assert(combined != &seq);
    assert(combined->getSize() == 7);
    assert(combined->get(5) == 6);
    assert(combined->get(6) == 7);
    assert(seq.getSize() == 5);
    
    delete sub;
    delete combined;
}

void testExceptions() {
    std::cout << "Testing Exceptions..." << std::endl;
    MutableArraySequence<int> seq;
    
    bool caught = false;
    try {
        seq.getFirst();
    } catch (const std::out_of_range&) {
        caught = true;
    }
    assert(caught);

    caught = false;
    seq.append(10);
    try {
        seq.get(5);
    } catch (const std::out_of_range&) {
        caught = true;
    }
    assert(caught);
}

void testEnumerator() {
    std::cout << "Testing Enumerator..." << std::endl;
    int data[] = {10, 20, 30};
    MutableArraySequence<int> seq(data, 3);
    
    IEnumerator<int>* e = seq.getEnumerator();
    assert(e->moveNext());
    assert(e->getCurrent() == 10);
    assert(e->moveNext());
    assert(e->getCurrent() == 20);
    assert(e->moveNext());
    assert(e->getCurrent() == 30);
    assert(!e->moveNext());
    
    e->reset();
    assert(e->moveNext());
    assert(e->getCurrent() == 10);
    
    delete e;
}


int main() {
    try {
        testDynamicArray();
        testLinkedList();
        testMutableArraySequence();
        testImmutableArraySequence();
        testMutableListSequence();
        testImmutableListSequence();
        testSubSequenceAndConcat();
        testExceptions();
        testEnumerator();
        
        std::cout << "\n-----------------------------" << std::endl;
        std::cout << "  ALL TESTS PASSED SUCCESSFULLY" << std::endl;
        std::cout << "-----------------------------" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "\n!!! TEST FAILED !!!" << std::endl;
        std::cerr << "Reason: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
