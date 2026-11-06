#ifndef TRANSACTIONSMANAGER_H
#define TRANSACTIONSMANAGER_H

#include <iostream>
#include <iomanip>

#include "Stack.h"
#include "Transaction.h"

class TransactionsManager {
private:
    Stack recentTransactions;

public:
    // Add transaction to the recent Stack (Push)
    void addTransaction(const Transaction& transaction) {
        recentTransactions.push(transaction);

        std::cout << "[Success] Transaction "
                  << transaction.transactionID
                  << " recorded successfully!\n";
    }

    // View latest transaction (Peek)
    void viewRecentTransaction() const {
        Transaction recent;

        if (!recentTransactions.peek(recent)) {
            std::cout << "No recent transactions found.\n";
            return;
        }

        std::cout << "\n========================================\n";
        std::cout << "          RECENT TRANSACTION\n";
        std::cout << "========================================\n";

        std::cout << "ID          : " << recent.transactionID << "\n";
        std::cout << "Date        : " << recent.date << "\n";
        std::cout << "Description : " << recent.description << "\n";

        std::cout << "Amount      : PHP "
                  << std::fixed << std::setprecision(2)
                  << recent.amount << "\n";

        std::cout << "========================================\n";
    }

    // View all recent transactions
    void viewAllRecentTransactions() const {
        if (recentTransactions.isEmpty()) {
            std::cout << "No recent transactions found.\n";
            return;
        }

        std::cout << "\n========================================\n";
        std::cout << "          ALL RECENT TRANSACTIONS\n";
        std::cout << "========================================\n";

        recentTransactions.displayAll();

        std::cout << "========================================\n";
    }

    // Remove latest transaction from recent Stack (Pop)
    void removeRecentTransaction() {
        if (!recentTransactions.pop()) {
            std::cout << "No recent transaction to remove.\n";
            return;
        }

        std::cout << "Latest transaction removed from recent records.\n";
        std::cout << "Permanent transaction history remains unchanged.\n";
    }

    // Get number of recent transactions
    int getRecentCount() const {
        return recentTransactions.getCount();
    }
};

#endif