#ifndef CUSTOMER_H
#define CUSTOMER_H
 
#include <string>
#include <iostream>
 
// Customer data structure
struct Customer {

    int id;                    // Auto-generated customer number
    std::string name;
    std::string contactNumber;
 
    Customer() : id(0), name(""), contactNumber("") {}
    Customer(int id, const std::string& name, const std::string& contact)
        : id(id), name(name), contactNumber(contact) {}
 
    void display() const {
        std::cout << "Customer No. : " << id << "\n"
                  << "Name         : " << name << "\n"
                  << "Contact No.  : " << contactNumber << "\n";
    }
};
 
#endif