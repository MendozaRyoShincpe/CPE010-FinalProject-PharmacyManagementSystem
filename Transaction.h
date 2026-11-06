#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

// Transaction record
struct Transaction {
    std::string transactionID;
    std::string date;
    std::string description;
    double amount;

    // Default constructor
    Transaction()
        : transactionID(""), date(""), description(""), amount(0.0) {}

    // Parameterized constructor
    Transaction(const std::string& id,
                const std::string& d,
                const std::string& desc,
                double amt)
        : transactionID(id), date(d), description(desc), amount(amt) {}
};

#endif