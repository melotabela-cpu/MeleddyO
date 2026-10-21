/*******************************************************
Name: Mel
Description: Full linked list program (combined version).
Contains ListNode struct, LinkedList class, and driver.
********************************************************/

#include <iostream>
using namespace std;

/******************** NODE STRUCT **********************/
template <typename T>
struct ListNode {
    T data;
    ListNode* next;
};

/******************** LINKED LIST CLASS ****************/
template <typename T>
class LinkedList {
private:
    ListNode<T>* head;
    ListNode<T>* tail;
    int size;

public:
    LinkedList();
    ~LinkedList();

    void addItem(T item);
    void remove(T item);
    bool find(T item) const;
    int getSize() const;

    // Overloaded insertion operator
    friend ostream& operator<<(ostream& os, const LinkedList<T>& list) {
        ListNode<T>* current = list.head;
        while (current != nullptr) {
            os << current->data << " ";
            current = current->next;
        }
        return os;
    }
};

/******************** IMPLEMENTATION ********************/

// Constructor
template <typename T>
LinkedList<T>::LinkedList() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

// Destructor
template <typename T>
LinkedList<T>::~LinkedList() {
    ListNode<T>* current = head;
    while (current != nullptr) {
        ListNode<T>* temp = current;
        current = current->next;
        delete temp;
    }
}

// Add item
template <typename T>
void LinkedList<T>::addItem(T item) {
    ListNode<T>* newNode = new ListNode<T>{ item, nullptr };

    if (head == nullptr) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }

    size++;
}

// Remove item
template <typename T>
void LinkedList<T>::remove(T item) {
    if (head == nullptr) return;

    // Remove head
    if (head->data == item) {
        ListNode<T>* temp = head;
        head = head->next;
        delete temp;
        size--;

        if (head == nullptr) tail = nullptr;
        return;
    }

    // Remove non-head
    ListNode<T>* current = head;
    while (current->next != nullptr && current->next->data != item) {
        current = current->next;
    }

    if (current->next != nullptr) {
        ListNode<T>* temp = current->next;
        current->next = current->next->next;

        if (temp == tail) tail = current;

        delete temp;
        size--;
    }
}

// Find item
template <typename T>
bool LinkedList<T>::find(T item) const {
    ListNode<T>* current = head;
    while (current != nullptr) {
        if (current->data == item) return true;
        current = current->next;
    }
    return false;
}

// Get size
template <typename T>
int LinkedList<T>::getSize() const {
    return size;
}

/******************** MAIN DRIVER ***********************/
int main() {
    LinkedList<int> list;

    cout << "Adding items 1 through 10...\n";
    for (int i = 1; i <= 10; i++) {
        list.addItem(i);
    }

    cout << "List: " << list << "\n";
    cout << "Size: " << list.getSize() << "\n\n";

    cout << "Removing first item (1)...\n";
    list.remove(1);
    cout << "List: " << list << "\n";

    cout << "Removing last item (10)...\n";
    list.remove(10);
    cout << "List: " << list << "\n";

    cout << "Removing middle item (5)...\n";
    list.remove(5);
    cout << "List: " << list << "\n";

    cout << "Trying to remove item not in list (100)...\n";
    list.remove(100);
    cout << "List: " << list << "\n";

    cout << "Finding item 7: " << (list.find(7) ? "Found" : "Not Found") << "\n";
    cout << "Finding item 50: " << (list.find(50) ? "Found" : "Not Found") << "\n";

    cout << "Removing all items...\n";
    for (int i = 2; i <= 9; i++) {
        list.remove(i);
    }

    cout << "List after clearing: " << list << "\n";
    cout << "Final size: " << list.getSize() << "\n";

    return 0;
}
