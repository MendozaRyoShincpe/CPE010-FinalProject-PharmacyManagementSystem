#ifndef CUSTOMERQUEUE_H
#define CUSTOMERQUEUE_H
#include <iostream>
#include <string>
#include <limits>
#include "Customer.h"
#include "Queue.h"
 
// Customer Queue Management.
class CustomerQueue {
private:
    Queue waiting;
    Customer current;
    bool hasCurrent;
    int nextId;
 
    static void line() {
        std::cout << "========================================\n";
    }
 
    static void pause() {
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }
 
    static int readInt() {
        int value;
        while (!(std::cin >> value)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Enter a number: ";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return value;
    }
 
public:
    CustomerQueue() : hasCurrent(false), nextId(1) {}
 
    // Operations 
 
    void addCustomer() {
        std::string name, contact;
        std::cout << "Enter customer name: ";
        std::getline(std::cin, name);
        if (name.empty()) {
            std::cout << "Name cannot be empty. Customer not added.\n";
            return;
        }
        std::cout << "Enter contact number: ";
        std::getline(std::cin, contact);
 
        Customer c(nextId++, name, contact);
        waiting.enqueue(c);
        std::cout << "\n" << c.name << " was added to the queue as Customer No. "<< c.id << ".\n";
        std::cout << "Customers waiting: " << waiting.size() << "\n";
    }
 
    void viewNextCustomer() const {
        Customer c;
        if (!waiting.peek(c)) {
            std::cout << "The queue is empty.\n";
            return;
        }
        std::cout << "Next customer in line:\n";
        c.display();
    }
 
    // IsEmpty -> Peek -> Dequeue
    void serveNextCustomer() {
        if (hasCurrent) {
            std::cout << "Customer No. " << current.id << " (" << current.name<< ") is still being served.\n"
                      << "Complete or cancel their purchase in Sales and Checkout first.\n";
            return;
        }
        if (waiting.isEmpty()) {
            std::cout << "The queue is empty. No customer to serve.\n";
            return;
        }
        Customer next;
        waiting.peek(next);
        waiting.dequeue(current);
        hasCurrent = true;
        std::cout << "Now serving:\n";
        current.display();
        std::cout << "\nProceed to Sales and Checkout to process the purchase.\n";
    }
 
    void viewWaitingCustomers() const {
        if (waiting.isEmpty()) {
            std::cout << "No customers are waiting.\n";
            return;
        }
        std::cout << "Waiting customers (" << waiting.size() << "):\n";
        waiting.displayAll();
    }
 
    //Interface for Sales 
 
    bool hasCustomerBeingServed() const { return hasCurrent; }
 
    // Returns the customer currently being served (valid only if hasCustomerBeingServed())
    const Customer& getCurrentCustomer() const { return current; }
 
    // Call after a completed purchase
    void finishCurrentCustomer() { hasCurrent = false; }
 
    // Call if the customer cancels: they go back to the front of the line
    void returnCurrentCustomerToQueue() {
        if (hasCurrent) {
            waiting.enqueueFront(current);
            hasCurrent = false;
        }
    }
 
    int waitingCount() const { return waiting.size(); }
 
    // Menu 
 
    void showMenu() {
        int choice;
        do {std::cout << "\n";
            line();
            std::cout << "CUSTOMER QUEUE MANAGEMENT\n";
            line();
            std::cout << "1. Add Customer to Queue\n"
                      << "2. View Next Customer\n"
                      << "3. Serve Next Customer\n"
                      << "4. View Waiting Customers\n"
                      << "5. Return to Main Menu\n";
            line();
            std::cout << "Enter your choice: ";
            choice = readInt();
            std::cout << "\n";
 
            switch (choice) {
                case 1: addCustomer(); pause(); break;
                case 2: viewNextCustomer(); pause(); break;
                case 3: serveNextCustomer(); pause(); break;
                case 4: viewWaitingCustomers(); pause(); break;
                case 5: break;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
                    pause();
            }
        } while (choice != 5);
    }
};
 
#endif
 