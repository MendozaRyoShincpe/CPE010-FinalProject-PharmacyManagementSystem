#ifndef SEARCHING_H
#define SEARCHING_H

#include <iostream>
#include <string>

#include "DynamicArray.h"
#include "Medicine.h"
#include "Utilities.h"

// Linear Search by Medicine Name
inline int linearSearchByName(
    const DynamicArray<Medicine>& arr,
    const std::string& name,
    DynamicArray<int>& matches
) {
    std::string key = toLower(name);

    // Clear previous search results
    matches.clear();

    for (int i = 0; i < arr.size(); ++i) {
        if (toLower(arr[i].name).find(key) != std::string::npos) {
            matches.push_back(i);
        }
    }

    return matches.size();
}

// Binary Search by Product Code
inline int binarySearchByCode(
    const DynamicArray<Medicine>& arr,
    const std::string& code
) {
    int low = 0;
    int high = arr.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid].code == code) {
            return mid;
        }

        if (arr[mid].code < code) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }

    return -1;
}

// Medicine Search Menu
inline void searchMenu(const DynamicArray<Medicine>& inventory) {
    while (true) {
        printTitle("SEARCH MEDICINE");

        std::cout
            << "1. Search by Medicine Name\n"
            << "2. Search by Product Code\n"
            << "3. Return to Main Menu\n";

        printLine();

        int choice = readInt("Enter your choice: ", 1, 3);

        if (choice == 1) {
            std::string name = readLine("Enter medicine name: ");

            DynamicArray<int> matches;

            if (name.empty() ||
                linearSearchByName(inventory, name, matches) == 0) {

                std::cout << "No medicine found.\n";
            }
            else {
                std::cout
                    << "\nFound " << matches.size()
                    << " result(s) using Linear Search:\n";

                printMedicineHeader();

                for (int i = 0; i < matches.size(); ++i) {
                    printMedicineRow(inventory[matches[i]]);
                }
            }
        }
        else if (choice == 2) {
            std::string code = toUpper(
                readLine("Enter product code: ")
            );

            int index = binarySearchByCode(inventory, code);

            if (index == -1) {
                std::cout << "No medicine found.\n";
            }
            else {
                std::cout << "\nMedicine found using Binary Search:\n";

                printMedicineHeader();
                printMedicineRow(inventory[index]);
            }
        }
        else {
            return;
        }
    }
}

#endif