#ifndef MONITORING_H
#define MONITORING_H

#include <iostream>
#include <string>

#include "DynamicArray.h"
#include "Medicine.h"
#include "Utilities.h"

const int LOW_STOCK_THRESHOLD = 10;
const int NEAR_EXPIRY_DAYS = 30;

// Check if medicine is expired
inline bool isExpired(
    const Medicine& m,
    const std::string& today
) {
    return m.expiration < today;
}

// Check if medicine is near expiration
inline bool isNearExpiration(
    const Medicine& m,
    const std::string& today
) {
    if (isExpired(m, today)) {
        return false;
    }

    int days = daysBetween(today, m.expiration);

    return days >= 0 && days <= NEAR_EXPIRY_DAYS;
}

// Display low-stock medicines
inline void showLowStock(const DynamicArray<Medicine>& inv) {
    printTitle(
        "LOW-STOCK MEDICINES (qty <= "
        + std::to_string(LOW_STOCK_THRESHOLD) + ")"
    );

    int found = 0;

    for (int i = 0; i < inv.size(); ++i) {
        if (inv[i].quantity <= LOW_STOCK_THRESHOLD) {
            if (found == 0) {
                printMedicineHeader();
            }

            printMedicineRow(inv[i]);
            ++found;
        }
    }

    if (found == 0) {
        std::cout << "No low-stock medicines.\n";
    }
}

// Display expired medicines
inline void showExpired(const DynamicArray<Medicine>& inv) {
    printTitle("EXPIRED MEDICINES");

    std::string today = currentDate();
    int found = 0;

    for (int i = 0; i < inv.size(); ++i) {
        if (isExpired(inv[i], today)) {
            if (found == 0) {
                printMedicineHeader();
            }

            printMedicineRow(inv[i]);
            ++found;
        }
    }

    if (found == 0) {
        std::cout << "No expired medicines.\n";
    }
}

// Display near-expiration medicines
inline void showNearExpiration(const DynamicArray<Medicine>& inv) {
    printTitle(
        "NEAR-EXPIRATION MEDICINES (within "
        + std::to_string(NEAR_EXPIRY_DAYS) + " days)"
    );

    std::string today = currentDate();
    int found = 0;

    for (int i = 0; i < inv.size(); ++i) {
        if (isNearExpiration(inv[i], today)) {
            if (found == 0) {
                printMedicineHeader();
            }

            printMedicineRow(inv[i]);
            ++found;
        }
    }

    if (found == 0) {
        std::cout << "No near-expiration medicines.\n";
    }
}

// Stock and expiration monitoring menu
inline void monitoringMenu(const DynamicArray<Medicine>& inv) {
    while (true) {
        printTitle("STOCK AND EXPIRATION MONITORING");

        std::cout
            << "1. View Low-Stock Medicines\n"
            << "2. View Expired Medicines\n"
            << "3. View Near-Expiration Medicines\n"
            << "4. Return to Main Menu\n";

        printLine();

        int choice = readInt("Enter your choice: ", 1, 4);

        if (choice == 1) {
            showLowStock(inv);
        }
        else if (choice == 2) {
            showExpired(inv);
        }
        else if (choice == 3) {
            showNearExpiration(inv);
        }
        else {
            return;
        }
    }
}

#endif