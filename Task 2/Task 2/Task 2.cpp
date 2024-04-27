#include <iostream>
using namespace std;

// node structure for doubly linked list
struct Node {
    int data;   //stores data
    Node* prev;   // stores prev node
    Node* next;  // stores next node

    Node(int val) : data(val), prev(nullptr), next(nullptr) {}
};

// function to insert a node at the end of a doubly linked list
void insert(Node*& head, int val) {
    Node* newNode = new Node(val);  // creates new node 
    if (!head) {
        head = newNode;  // checks if head is null, if so set new node as head
    }
    else {
        Node* current = head;
        while (current->next) {
            current = current->next;  // if not, loop through liked list until end
        }                               // then add new node at the end and link it to the prev node
        current->next = newNode;
        newNode->prev = current;
    }
}

// function to print a doubly linked list
void printLinkedList(Node* head) {
    Node* current = head;
    while (current) {                     // loop through nodes and print data
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// function to partition the list and return the pivot node
Node* partition(Node* low, Node* high) {
    int pivot = high->data;             // set pivot
    Node* i = low->prev;

    for (Node* j = low; j != high; j = j->next) {
        if (j->data <= pivot) {
            i = (i == nullptr) ? low : i->next; // sort data so values smaller than pivot are before and 
            swap(i->data, j->data);             // values larger are after
        }
    }

    i = (i == nullptr) ? low : i->next;
    swap(i->data, high->data);
    return i;
}

// Function to perform Quick Sort on a doubly linked list
void quickSort(Node* low, Node* high) {
    if (high != nullptr && low != high && low != high->next) { //checks to see if list/sublist is sorted
        Node* pivot = partition(low, high);   // divides into partitions
        quickSort(low, pivot->prev);            // sort half before pivot
        quickSort(pivot->next, high);           // sorts half after pivot
    }
}

// Main function for testing
int main() {
    Node* head = nullptr;

    // Insert elements into the doubly linked list
    insert(head, 12);
    insert(head, 7);
    insert(head, 9);
    insert(head, 4);
    insert(head, 5);
    insert(head, 3);

    cout << "Original list: ";
    printLinkedList(head);

    // Perform Quick Sort on the doubly linked list
    Node* lastNode = head;
    while (lastNode->next) {
        lastNode = lastNode->next;
    }
    quickSort(head, lastNode);

    cout << "Sorted list: ";
    printLinkedList(head);

    return 0;
}
