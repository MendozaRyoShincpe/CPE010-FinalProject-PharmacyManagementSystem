#include <iostream>
#include <limits>

#include "Inventory.h"
#include "Searching.h"
#include "Sorting.h"
#include "Monitoring.h"
#include "CustomerQueue.h"
#include "TransactionsManager.h"
#include "FileManager.h"
#include "Sales.h"

// Display main menu
void displayMainMenu() {
    std::cout << "\n========================================\n";
    std::cout << "       PHARMACY MANAGEMENT SYSTEM\n";
    std::cout << "========================================\n";
    std::cout << "1. Inventory Management\n";
    std::cout << "2. Search Medicine\n";
    std::cout << "3. Sort Medicines by Expiration\n";
    std::cout << "4. Customer Queue Management\n";
    std::cout << "5. Sales and Checkout\n";
    std::cout << "6. Recent Transactions\n";
    std::cout << "7. Transaction History\n";
    std::cout << "8. Stock and Expiration Monitoring\n";
    std::cout << "9. Exit\n";
    std::cout << "========================================\n";
}

// Read a valid main menu choice
int getMenuChoice() {
    int choice;

    std::cout << "Enter your choice: ";

    while (!(std::cin >> choice) || choice < 1 || choice > 9) {
        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n'
        );

        std::cout << "Invalid choice. Enter a number from 1 to 9: ";
    }

    std::cin.ignore(
        std::numeric_limits<std::streamsize>::max(), '\n'
    );

    return choice;
}

// Recent transaction menu
void recentTransactionsMenu(TransactionsManager& manager) {
    int choice;

    do {
        std::cout << "\n========================================\n";
        std::cout << "          RECENT TRANSACTIONS\n";
        std::cout << "========================================\n";
        std::cout << "1. View Latest Transaction\n";
        std::cout << "2. Remove Latest from Recent Stack\n";
        std::cout << "3. View All Recent Transactions\n";
        std::cout << "4. Return to Main Menu\n";
        std::cout << "========================================\n";
        std::cout << "Enter your choice: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n'
            );
            choice = 0;
        } else {
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n'
            );
        }

        switch (choice) {
            case 1:
                manager.viewRecentTransaction();
                break;

            case 2:
                manager.removeRecentTransaction();
                break;

            case 3:
                manager.viewAllRecentTransactions();
                break;

            case 4:
                break;

            default:
                std::cout << "Invalid choice.\n";
        }

    } while (choice != 4);
}

// Permanent transaction history menu
void transactionHistoryMenu(FileManager& fileManager) {
    int choice;

    do {
        std::cout << "\n========================================\n";
        std::cout << "          TRANSACTION HISTORY\n";
        std::cout << "========================================\n";
        std::cout << "1. View All Transactions\n";
        std::cout << "2. Search Transaction by ID\n";
        std::cout << "3. Return to Main Menu\n";
        std::cout << "========================================\n";
        std::cout << "Enter your choice: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n'
            );
            choice = 0;
        } else {
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n'
            );
        }

        switch (choice) {
            case 1:
                fileManager.displayTransactionHistory();
                break;

            case 2: {
                std::string id;

                std::cout << "Enter transaction ID: ";
                std::getline(std::cin, id);

                fileManager.searchTransactionByID(id);
                break;
            }

            case 3:
                break;

            default:
                std::cout << "Invalid choice.\n";
        }

    } while (choice != 3);
}

int main() {
    Inventory inventory;
    CustomerQueue customerQueue;
    TransactionsManager transactionsManager;
    FileManager fileManager;

    // Connect Sales to the other modules
    Sales sales(
        inventory,
        customerQueue,
        transactionsManager,
        fileManager
    );

    // Load saved medicine inventory
    std::cout << "Loading pharmacy records...\n";
    fileManager.loadInventory(inventory);

    int choice;

    do {
        displayMainMenu();
        choice = getMenuChoice();

        switch (choice) {
            case 1:
                inventory.runMenu();
                break;

            case 2:
                searchMenu(inventory.getMedicines());
                break;

            case 3:
                sortMenu(inventory.getMedicines());
                break;

            case 4:
                customerQueue.showMenu();
                break;

            case 5:
                sales.processPurchase();
                break;

            case 6:
                recentTransactionsMenu(transactionsManager);
                break;

            case 7:
                transactionHistoryMenu(fileManager);
                break;

            case 8:
                monitoringMenu(inventory.getMedicines());
                break;

            case 9:
                fileManager.saveInventory(inventory);
                std::cout << "\nInventory saved successfully.\n";
                std::cout << "Thank you for using the Pharmacy Management System.\n";
                break;
        }

    } while (choice != 9);

    return 0;
}