#include <iostream>
#include <stdexcept>

#include "ArraySequence.h"
#include "ListSequence.h"


void printSequence(Sequence<int>* seq) {

    if (!seq->getSize()) {
        std::cout << "(empty)\n";
        return;
    }

    IEnumerator<int>* e = seq->getEnumerator();

    std::cout << "[";
    bool first = true;
    while (e->moveNext()) {
        if (!first) std::cout << ", ";
        std::cout << e->getCurrent();
        first = false;
    }
    std::cout << "]  (size = " << seq->getSize() << ")\n";

    delete e;
}


void showMenu() {
    std::cout << "\n--- Operations ---\n"
              << "1. Append\n"
              << "2. Prepend\n"
              << "3. InsertAt\n"
              << "4. Get by index\n"
              << "5. GetFirst\n"
              << "6. GetLast\n"
              << "7. GetSubSequence\n"
              << "8. Concat with new sequence\n"
              << "9. Print sequence\n"
              << "0. Exit\n"
              << ">> ";
}


Sequence<int>* createSequence() {

    std::cout << "\n=== Create Sequence ===\n"
              << "Type:\n"
              << "  1. ArraySequence\n"
              << "  2. ListSequence\n"
              << ">> ";

    int type;
    std::cin >> type;

    std::cout << "Mutability:\n"
              << "  1. Mutable\n"
              << "  2. Immutable\n"
              << ">> ";

    int mut;
    std::cin >> mut;

    std::cout << "Number of initial elements: ";
    int count;
    std::cin >> count;

    int* items = nullptr;
    if (count > 0) {
        items = new int[count];
        std::cout << "Enter " << count << " elements: ";
        for (int i = 0; i < count; ++ i)
            std::cin >> items[i];
    }

    Sequence<int>* seq = nullptr;

    if (type == 1 && mut == 1) seq = new MutableArraySequence<int>(items, count);
    if (type == 1 && mut == 2) seq = new ImmutableArraySequence<int>(items, count);
    if (type == 2 && mut == 1) seq = new MutableListSequence<int>(items, count);
    if (type == 2 && mut == 2) seq = new ImmutableListSequence<int>(items, count);

    delete[] items;

    if (!seq) {
        std::cout << "Invalid choice, creating MutableArraySequence by default\n";
        seq = new MutableArraySequence<int>(nullptr, 0);
    }

    std::cout << "Created: ";
    printSequence(seq);

    return seq;
}


int main() {

    std::cout << "=== Sequence Demo ===\n";
    Sequence<int>* seq = createSequence();

    bool running = true;
    while (running) {

        showMenu();
        int choice;
        std::cin >> choice;

        try {
            switch (choice) {

                case 1: {
                    std::cout << "Value: ";
                    int val; std::cin >> val;
                    Sequence<int>* result = seq->append(val);
                    if (result != seq) { delete seq; seq = result; }
                    std::cout << "OK: ";
                    printSequence(seq);
                    break;
                }

                case 2: {
                    std::cout << "Value: ";
                    int val; std::cin >> val;
                    Sequence<int>* result = seq->prepend(val);
                    if (result != seq) { delete seq; seq = result; }
                    std::cout << "OK: ";
                    printSequence(seq);
                    break;
                }

                case 3: {
                    std::cout << "Value: ";
                    int val; std::cin >> val;
                    std::cout << "Index: ";
                    int idx; std::cin >> idx;
                    Sequence<int>* result = seq->insertAt(val, idx);
                    if (result != seq) { delete seq; seq = result; }
                    std::cout << "OK: ";
                    printSequence(seq);
                    break;
                }

                case 4: {
                    std::cout << "Index: ";
                    int idx; std::cin >> idx;
                    std::cout << "Value: " << seq->get(idx) << "\n";
                    break;
                }

                case 5: {
                    std::cout << "First: " << seq->getFirst() << "\n";
                    break;
                }

                case 6: {
                    std::cout << "Last: " << seq->getLast() << "\n";
                    break;
                }

                case 7: {
                    std::cout << "startIndex: ";
                    int s; std::cin >> s;
                    std::cout << "endIndex: ";
                    int e; std::cin >> e;
                    Sequence<int>* sub = seq->getSubSequence(s, e);
                    std::cout << "SubSequence: ";
                    printSequence(sub);
                    delete sub;
                    break;
                }

                case 8: {
                    std::cout << "Number of elements to concat: ";
                    int cnt; std::cin >> cnt;
                    int* items = cnt > 0 ? new int[cnt] : nullptr;
                    if (cnt > 0) {
                        std::cout << "Enter " << cnt << " elements: ";
                        for (int i = 0; i < cnt; ++ i)
                            std::cin >> items[i];
                    }
                    MutableArraySequence<int> other(items, cnt);
                    delete[] items;
                    Sequence<int>* result = seq->concat(&other);
                    if (result != seq) { delete seq; seq = result; }
                    std::cout << "OK: ";
                    printSequence(seq);
                    break;
                }

                case 9: {
                    printSequence(seq);
                    break;
                }

                case 0: {
                    running = false;
                    break;
                }

                default:
                    std::cout << "Unknown command\n";
            }
        }
        catch (const std::exception& ex) {
            std::cout << "Error: " << ex.what() << "\n";
        }
    }

    delete seq;
    std::cout << "Finished.\n";

    return 0;
}
