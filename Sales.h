#ifndef SALES_H
#define SALES_H

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <ctime>
#include <sstream>
#include <cctype>

#include "Inventory.h"
#include "CustomerQueue.h"
#include "TransactionsManager.h"
#include "FileManager.h"

// One item selected for checkout
struct CartItem {
    std::string code;
    std::string name;
    double price;
    int quantity;

    CartItem() : code(""), name(""), price(0.0), quantity(0) {}
};

class Sales {
private:
    Inventory& inventory;
    CustomerQueue& customerQueue;
    TransactionsManager& transactionsManager;
    FileManager& fileManager;

    static int& transactionCounter() {
    static int counter = 0;
    return counter;
}

    // Read a whole number safely
    int readQuantity() {
        int value;

        while (!(std::cin >> value) || value <= 0) {
            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n'
            );
            std::cout << "Enter a valid quantity greater than zero: ";
        }

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n'
        );

        return value;
    }

    // Read a yes/no confirmation
    bool confirmPurchase() {
        char answer;

        while (true) {
            std::cout << "Confirm purchase? (Y/N): ";

            if (std::cin >> answer) {
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(), '\n'
                );

                if (answer == 'Y' || answer == 'y') {
                    return true;
                }

                if (answer == 'N' || answer == 'n') {
                    return false;
                }
            } else {
                std::cin.clear();
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(), '\n'
                );
            }

            std::cout << "Invalid choice. Enter Y or N.\n";
        }
    }

    // Get the current date in YYYY-MM-DD format
    std::string getTodayDate() const {
        std::time_t now = std::time(nullptr);
        std::tm* localTime = std::localtime(&now);

        if (localTime == nullptr) {
            return "0000-00-00";
        }

        char buffer[11];

        std::strftime(
            buffer, sizeof(buffer), "%Y-%m-%d", localTime
        );

        return std::string(buffer);
    }

    // Generate a transaction ID
    std::string generateTransactionID() {
        std::time_t now = std::time(nullptr);

        std::ostringstream id;
        id << "TXN" << now << "-" << ++transactionCounter();

        return id.str();
    }

public:
    Sales(
        Inventory& inv,
        CustomerQueue& queue,
        TransactionsManager& transactions,
        FileManager& files
    )
        : inventory(inv),
          customerQueue(queue),
          transactionsManager(transactions),
          fileManager(files) {}

    // Process a purchase for the customer currently being served
    void processPurchase() {
        if (!customerQueue.hasCustomerBeingServed()) {
            std::cout << "No customer is currently being served.\n";
            std::cout << "Please serve the next customer first.\n";
            return;
        }

        const Customer& customer = customerQueue.getCurrentCustomer();

        std::cout << "\n========================================\n";
        std::cout << "             SALES AND CHECKOUT\n";
        std::cout << "========================================\n";

        std::cout << "Customer No. : " << customer.id << "\n";
        std::cout << "Customer     : " << customer.name << "\n";

        if (inventory.getSize() == 0) {
            std::cout << "\nInventory is empty. Purchase cannot proceed.\n";
            return;
        }

        DynamicArray<CartItem> cart;
        char addAnother = 'Y';

        while (addAnother == 'Y' || addAnother == 'y') {
            std::string code;
            std::cout << "\nEnter medicine product code: ";
            std::getline(std::cin, code);

            // Convert code to uppercase
            for (int i = 0; i < static_cast<int>(code.length()); i++) {
                code[i] = static_cast<char>(
                    std::toupper(static_cast<unsigned char>(code[i]))
                );
            }

            int index = inventory.findIndex(code);

            if (index == -1) {
                std::cout << "Medicine not found.\n";
            } else {
                Medicine medicine = inventory.getAt(index);

                std::cout << "Medicine : " << medicine.name << "\n";
                std::cout << "Price    : PHP "
                          << std::fixed << std::setprecision(2)
                          << medicine.price << "\n";
                std::cout << "Stock    : " << medicine.quantity << "\n";

                if (medicine.quantity <= 0) {
                    std::cout << "This medicine is out of stock.\n";
                } else {
                    std::cout << "Enter quantity: ";
                    int quantity = readQuantity();

                    // Check quantities already added to the cart
                    int alreadySelected = 0;

                    for (int i = 0; i < cart.size(); i++) {
                        if (cart[i].code == medicine.code) {
                            alreadySelected += cart[i].quantity;
                        }
                    }

                    if (quantity + alreadySelected > medicine.quantity) {
                        std::cout << "Insufficient stock. Available stock: "
                                  << medicine.quantity - alreadySelected
                                  << "\n";
                    } else {
                        int existingIndex = -1;

                        for (int i = 0; i < cart.size(); i++) {
                            if (cart[i].code == medicine.code) {
                                existingIndex = i;
                                break;
                            }
                        }

                        if (existingIndex != -1) {
                            cart[existingIndex].quantity += quantity;
                        } else {
                            CartItem item;
                            item.code = medicine.code;
                            item.name = medicine.name;
                            item.price = medicine.price;
                            item.quantity = quantity;

                            cart.push_back(item);
                        }

                        std::cout << "Medicine added to cart.\n";
                    }
                }
            }

            std::cout << "\nAdd another medicine? (Y/N): ";
            std::cin >> addAnother;
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n'
            );
        }

        if (cart.empty()) {
            std::cout << "\nNo medicines were selected.\n";
            return;
        }

        // Display order summary and calculate total
        double total = 0.0;

        std::cout << "\n========================================\n";
        std::cout << "              PURCHASE SUMMARY\n";
        std::cout << "========================================\n";

        for (int i = 0; i < cart.size(); i++) {
            double subtotal = cart[i].price * cart[i].quantity;
            total += subtotal;

            std::cout << cart[i].name
                      << " x " << cart[i].quantity
                      << " = PHP " << std::fixed << std::setprecision(2)
                      << subtotal << "\n";
        }

        std::cout << "----------------------------------------\n";
        std::cout << "TOTAL: PHP " << std::fixed << std::setprecision(2)
                  << total << "\n";
        std::cout << "========================================\n";

        if (!confirmPurchase()) {
            std::cout << "\nPurchase cancelled. No stock was deducted.\n";
            return;
        }

        // Deduct stock only after the customer confirms
        for (int i = 0; i < cart.size(); i++) {
            if (!inventory.deductStock(
                    cart[i].code, cart[i].quantity)) {
                std::cout << "Error updating stock for "
                          << cart[i].name << ".\n";
                std::cout << "Please check the inventory before continuing.\n";
                return;
            }
        }

        // Create transaction description
        std::string description = "Customer: " + customer.name + "; Items: ";

        for (int i = 0; i < cart.size(); i++) {
            if (i > 0) {
                description += ", ";
            }

            description += cart[i].name
                         + " x "
                         + std::to_string(cart[i].quantity);
        }

        Transaction transaction(
            generateTransactionID(),
            getTodayDate(),
            description,
            total
        );

        // Save permanent transaction record first
        bool transactionSaved = fileManager.saveTransaction(transaction);

        // Add transaction to the recent Stack
        transactionsManager.addTransaction(transaction);

        // Save updated inventory
        bool inventorySaved = fileManager.saveInventory(inventory);

        std::cout << "\n========================================\n";
        std::cout << "           PURCHASE COMPLETED\n";
        std::cout << "========================================\n";
        std::cout << "Transaction ID : "
                  << transaction.transactionID << "\n";
        std::cout << "Customer       : " << customer.name << "\n";
        std::cout << "Total          : PHP "
                  << std::fixed << std::setprecision(2)
                  << total << "\n";

        if (!transactionSaved) {
            std::cout << "Warning: Transaction could not be saved permanently.\n";
        }

        if (!inventorySaved) {
            std::cout << "Warning: Updated inventory could not be saved.\n";
        }

        // Release the current customer after checkout
        customerQueue.finishCurrentCustomer();
    }
};

#endif