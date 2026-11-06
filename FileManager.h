#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include "Inventory.h"
#include "Transaction.h"

class FileManager {
private:
    const std::string medicineFile = "medicines.txt";
    const std::string transactionFile = "transactions.txt";

    // Replace pipe characters to protect the file format
    std::string cleanField(const std::string& value) const {
        std::string result = value;

        for (int i = 0; i < static_cast<int>(result.length()); i++) {
            if (result[i] == '|') {
                result[i] = '/';
            }
        }

        return result;
    }

public:
    // Load medicine records into the Dynamic Array
    void loadInventory(Inventory& inventory) {
        std::ifstream file(medicineFile.c_str());

        if (!file.is_open()) {
            std::cout << "Medicine file not found. Starting with an empty inventory.\n";
            return;
        }

        std::string line;

        while (std::getline(file, line)) {
            if (line.empty()) {
                continue;
            }

            std::stringstream ss(line);
            std::string code, name, priceText, quantityText, expiration;

            if (!std::getline(ss, code, '|') ||
                !std::getline(ss, name, '|') ||
                !std::getline(ss, priceText, '|') ||
                !std::getline(ss, quantityText, '|') ||
                !std::getline(ss, expiration)) {
                continue;
            }

            try {
                double price = std::stod(priceText);
                int quantity = std::stoi(quantityText);

                if (price < 0 || quantity < 0) {
                    continue;
                }

                Medicine medicine;
                medicine.code = code;
                medicine.name = name;
                medicine.price = price;
                medicine.quantity = quantity;
                medicine.expiration = expiration;

                // Inventory inserts records in product-code order
                inventory.addMedicineToArray(medicine);
            }
            catch (...) {
                std::cout << "Skipped an invalid medicine record.\n";
            }
        }

        file.close();
        std::cout << "Medicine inventory loaded successfully.\n";
    }

    // Save all medicine records
    bool saveInventory(const Inventory& inventory) {
        std::ofstream file(medicineFile.c_str());

        if (!file.is_open()) {
            std::cout << "Error: Unable to save medicine inventory.\n";
            return false;
        }

        const DynamicArray<Medicine>& medicines = inventory.getMedicines();

        for (int i = 0; i < medicines.size(); i++) {
            const Medicine& medicine = medicines[i];

            file << cleanField(medicine.code) << "|"
                 << cleanField(medicine.name) << "|"
                 << std::fixed << std::setprecision(2) << medicine.price << "|"
                 << medicine.quantity << "|"
                 << medicine.expiration << "\n";
        }

        file.close();
        return true;
    }

    // Append a transaction to permanent history
    bool saveTransaction(const Transaction& transaction) {
        std::ofstream file(transactionFile.c_str(), std::ios::app);

        if (!file.is_open()) {
            std::cout << "Error: Unable to save transaction.\n";
            return false;
        }

        file << cleanField(transaction.transactionID) << "|"
             << cleanField(transaction.date) << "|"
             << cleanField(transaction.description) << "|"
             << std::fixed << std::setprecision(2)
             << transaction.amount << "\n";

        file.close();
        return true;
    }

    // Display all transactions from the permanent file
    void displayTransactionHistory() const {
        std::ifstream file(transactionFile.c_str());

        if (!file.is_open()) {
            std::cout << "No transaction history found.\n";
            return;
        }

        std::string line;
        int count = 0;

        std::cout << "\n========================================\n";
        std::cout << "          TRANSACTION HISTORY\n";
        std::cout << "========================================\n";

        while (std::getline(file, line)) {
            if (line.empty()) {
                continue;
            }

            std::stringstream ss(line);
            std::string id, date, description, amount;

            if (!std::getline(ss, id, '|') ||
                !std::getline(ss, date, '|') ||
                !std::getline(ss, description, '|') ||
                !std::getline(ss, amount)) {
                continue;
            }

            std::cout << "\nTransaction ID : " << id << "\n";
            std::cout << "Date            : " << date << "\n";
            std::cout << "Description     : " << description << "\n";
            std::cout << "Amount          : PHP " << amount << "\n";
            std::cout << "----------------------------------------\n";

            count++;
        }

        if (count == 0) {
            std::cout << "Transaction history is empty.\n";
        } else {
            std::cout << "Total Transactions: " << count << "\n";
        }

        file.close();
    }

    // Search permanent transaction history by ID
    void searchTransactionByID(const std::string& searchID) const {
        std::ifstream file(transactionFile.c_str());

        if (!file.is_open()) {
            std::cout << "No transaction history found.\n";
            return;
        }

        std::string line;
        bool found = false;

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string id, date, description, amount;

            if (!std::getline(ss, id, '|') ||
                !std::getline(ss, date, '|') ||
                !std::getline(ss, description, '|') ||
                !std::getline(ss, amount)) {
                continue;
            }

            if (id == searchID) {
                std::cout << "\nTransaction found:\n";
                std::cout << "Transaction ID : " << id << "\n";
                std::cout << "Date            : " << date << "\n";
                std::cout << "Description     : " << description << "\n";
                std::cout << "Amount          : PHP " << amount << "\n";

                found = true;
                break;
            }
        }

        if (!found) {
            std::cout << "Transaction ID not found.\n";
        }

        file.close();
    }
};

#endif