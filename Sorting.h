#pragma once
#include "DynamicArray.h"
#include "Medicine.h"
#include <iostream>

// Dates are YYYY-MM-DD, so string comparison == chronological comparison.
inline void insertionSortByExpiration(DynamicArray<Medicine>& arr) {
    for (int i = 1; i < arr.size(); ++i) {
        Medicine key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].expiration > key.expiration) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

inline void sortMenu(const DynamicArray<Medicine>& inventory) {
    while (true) {
        printTitle("SORT BY EXPIRATION DATE");
        std::cout << "1. Display Sorted Medicines\n2. Return to Main Menu\n";
        printLine();
        int c = readInt("Enter your choice: ", 1, 2);
        if (c == 1) {
            if (inventory.empty()) {
                std::cout << "Inventory is empty.\n";
                continue;
            }
            DynamicArray<Medicine> copy = inventory;  // original order stays untouched
            insertionSortByExpiration(copy);
            std::cout << "\nMedicines sorted from earliest to latest expiration:\n";
            printMedicineHeader();
            for (int i = 0; i < copy.size(); ++i) printMedicineRow(copy[i]);
        } else {
            return;
        }
    }
}
