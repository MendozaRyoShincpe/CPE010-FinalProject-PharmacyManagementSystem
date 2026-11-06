#ifndef STACK_H
#define STACK_H

#include "Transaction.h"
#include <iostream>

// Node for the linked-list Stack
struct StackNode {
    Transaction data;
    StackNode* next;

    StackNode(const Transaction& t)
        : data(t), next(nullptr) {}
};

// Stack using a linked list (LIFO)
class Stack {
private:
    StackNode* top;
    int count;

public:

// Display all Stack records without removing them
void displayAll() const {
    StackNode* current = top;
    int position = 1;

    while (current != nullptr) {
        std::cout << "\nTransaction " << position++ << "\n";
        std::cout << "ID          : "
                  << current->data.transactionID << "\n";
        std::cout << "Date        : "
                  << current->data.date << "\n";
        std::cout << "Description : "
                  << current->data.description << "\n";
        std::cout << "Amount      : PHP "
                  << current->data.amount << "\n";

        current = current->next;
    }
}
    // Constructor
    Stack() : top(nullptr), count(0) {}

    // Destructor
    ~Stack() {
        clear();
    }

    // Prevent accidental shallow copying
    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    // Check if Stack is empty
    bool isEmpty() const {
        return top == nullptr;
    }

    // Get the number of transactions
    int getCount() const {
        return count;
    }

    // Push: Add transaction to the top
    void push(const Transaction& t) {
        StackNode* newNode = new StackNode(t);

        newNode->next = top;
        top = newNode;

        count++;
    }

    // Peek: View the top transaction
    bool peek(Transaction& result) const {
        if (isEmpty()) {
            return false;
        }

        result = top->data;
        return true;
    }

    // Pop: Remove the top transaction
    bool pop() {
        if (isEmpty()) {
            return false;
        }

        StackNode* temp = top;
        top = top->next;

        delete temp;
        count--;

        return true;
    }

    // Release all allocated nodes
    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }
};

#endif