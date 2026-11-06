
#pragma once
#include "Utils.h"
#include "DynamicArray.h"
#include "Medicine.h"

const int LOW_STOCK_THRESHOLD = 10;  
const int NEAR_EXPIRY_DAYS = 30;     

inline bool isExpired(const Medicine& m, const string& today) {
    return m.expiration < today;
}

inline bool isNearExpiration(const Medicine& m, const string& today) {
    if (isExpired(m, today)) return false;
    return daysBetween(today, m.expiration) <= NEAR_EXPIRY_DAYS;
}

inline void showLowStock(const DynamicArray<Medicine>& inv) {
    printTitle("LOW-STOCK MEDICINES (qty <= " + to_string(LOW_STOCK_THRESHOLD) + ")");
    int found = 0;
    for (int i = 0; i < inv.size(); ++i) {
        if (inv[i].quantity <= LOW_STOCK_THRESHOLD) {
            if (found == 0) printMedicineHeader();
            printMedicineRow(inv[i]);
            ++found;
        }
    }
    if (found == 0) cout << "No low-stock medicines.\n";
}

inline void showExpired(const DynamicArray<Medicine>& inv) {
    printTitle("EXPIRED MEDICINES");
    string today = currentDate();
    int found = 0;
    for (int i = 0; i < inv.size(); ++i) {
        if (isExpired(inv[i], today)) {
            if (found == 0) printMedicineHeader();
            printMedicineRow(inv[i]);
            ++found;
        }
    }
    if (found == 0) cout << "No expired medicines.\n";
}

inline void showNearExpiration(const DynamicArray<Medicine>& inv) {
    printTitle("NEAR-EXPIRATION MEDICINES (within " + to_string(NEAR_EXPIRY_DAYS) + " days)");
    string today = currentDate();
    int found = 0;
    for (int i = 0; i < inv.size(); ++i) {
        if (isNearExpiration(inv[i], today)) {
            if (found == 0) printMedicineHeader();
            printMedicineRow(inv[i]);
            ++found;
        }
    }
    if (found == 0) cout << "No near-expiration medicines.\n";
}

inline void monitoringMenu(const DynamicArray<Medicine>& inv) {
    while (true) {
        printTitle("STOCK AND EXPIRATION MONITORING");
        cout << "1. View Low-Stock Medicines\n2. View Expired Medicines\n"
                "3. View Near-Expiration Medicines\n4. Return to Main Menu\n";
        printLine();
        int c = readInt("Enter your choice: ", 1, 4);
        if (c == 1) showLowStock(inv);
        else if (c == 2) showExpired(inv);
        else if (c == 3) showNearExpiration(inv);
        else return;
    }
}
