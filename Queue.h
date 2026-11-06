#ifndef QUEUE_H
#define QUEUE_H

#include "Customer.h"

// Queue (FIFO) implemented as a linked list
struct QueueNode {
    Customer data;
    QueueNode* next;

    QueueNode(const Customer& c) : data(c), next(nullptr) {}
};

class Queue {
private:
    QueueNode* front;
    QueueNode* rear;
    int count;

public:
    Queue() : front(nullptr), rear(nullptr), count(0) {}

    ~Queue() { clear(); }

    // Prevent accidental shallow copies of the linked list
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

    bool isEmpty() const { return front == nullptr; }

    int size() const { return count; }

    // Add a customer at the rear
    void enqueue(const Customer& c) {
        QueueNode* node = new QueueNode(c);
        if (rear == nullptr) {
            front = rear = node;
        } else {
            rear->next = node;
            rear = node;
        }
        count++;
    }

    // used if a served customer must be restored to the front of the queue
    void enqueueFront(const Customer& c) {
        QueueNode* node = new QueueNode(c);
        node->next = front;
        front = node;
        if (rear == nullptr) rear = node;
        count++;
    }

    // View the front customer without removing. Returns false if empty.
    bool peek(Customer& out) const {
        if (isEmpty()) return false;
        out = front->data;
        return true;
    }

    // Remove the front customer. Returns false if empty.
    bool dequeue(Customer& out) {
        if (isEmpty()) return false;
        QueueNode* temp = front;
        out = temp->data;
        front = front->next;
        if (front == nullptr) rear = nullptr;
        delete temp;
        count--;
        return true;
    }

    // Display every waiting customer in order (FIFO)
    void displayAll() const {
        int position = 1;
        for (QueueNode* cur = front; cur != nullptr; cur = cur->next) {
            std::cout << position++ << ". [No. " << cur->data.id << "] "
                      << cur->data.name << " - " << cur->data.contactNumber << "\n";
        }
    }

    // Free all nodes
    void clear() {
        QueueNode* cur = front;
        while (cur != nullptr) {
            QueueNode* next = cur->next;
            delete cur;
            cur = next;
        }
        front = rear = nullptr;
        count = 0;
    }
};

#endif