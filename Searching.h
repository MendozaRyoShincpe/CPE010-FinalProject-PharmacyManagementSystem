
#pragma once
#include "Utils.h"
#include "DynamicArray.h"
#include "Medicine.h"


inline int linearSearchByName(const DynamicArray<Medicine>& arr, const string& name,
                              DynamicArray<int>& matches) {
    string key = toLower(name);
    for (int i = 0; i < arr.size(); ++i) {
        if (toLower(arr[i].name).find(key) != string::npos) matches.push_back(i);
    }
    return matches.size();
}
inline int binarySearchByCode(const DynamicArray<Medicine>& arr, const string& code) {
    int low = 0, high = arr.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid].code == code) return mid;
        if (arr[mid].code < code) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

inline void searchMenu(const DynamicArray<Medicine>& inventory) {
    while (true) {
        printTitle("SEARCH MEDICINE");
        cout << "1. Search by Medicine Name\n2. Search by Product Code\n3. Return to Main Menu\n";
        printLine();
        int c = readInt("Enter your choice: ", 1, 3);
        if (c == 1) {
            string name = readLine("Enter medicine name: ");
            DynamicArray<int> matches;
            if (name.empty() || linearSearchByName(inventory, name, matches) == 0) {
                cout << "No medicine found.\n";
            } else {
                cout << "\nFound " << matches.size() << " result(s) (Linear Search):\n";
                printMedicineHeader();
                for (int i = 0; i < matches.size(); ++i) printMedicineRow(inventory[matches[i]]);
            }
        } else if (c == 2) {
            string code = toUpper(readLine("Enter product code: "));
            int idx = binarySearchByCode(inventory, code);
            if (idx == -1) {
                cout << "No medicine found.\n";
            } else {
                cout << "\nFound (Binary Search):\n";
                printMedicineHeader();
                printMedicineRow(inventory[idx]);
            }
        } else {
            return;
        }
    }
}
