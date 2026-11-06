#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <string>
#include <cstdlib>
#include "Utilities.h"
#include "Medicine.h"
#include "DynamicArray.h"


//checks if the text is a number, example: 12.50
inline bool isDecimalNumber(std::string text) {
    if (text.length() == 0) {
        return false;
    }
    int dots = 0;
    for (int i = 0; i < (int)text.length(); i++) {
        if (text[i] == '.') {
            dots++;
        } else if (text[i] < '0' || text[i] > '9') {
            return false;
        }
    }
    if (dots > 1 || text == ".") {
        return false;
    }
    return true;
}

//reads text that cannot be empty
inline std::string readText(std::string message) {
    while (true) {
        std::string text = readLine(message);
        if (text.length() == 0) {
            std::cout << "Input cannot be empty." << std::endl;
        } else {
            return text;
        }
    }
}

inline double readPrice(std::string message) {
    while (true) {
        std::string text = readLine(message);
        if (isDecimalNumber(text) && std::atof(text.c_str()) > 0) {
            return std::atof(text.c_str());
        }
        std::cout << "Please enter a valid price greater than 0." << std::endl;
    }
}

inline std::string readDate(std::string message) {
    while (true) {
        std::string text = readLine(message);
        if (isValidDate(text)) {
            return text;
        }
        std::cout << "Invalid date. Use the format YYYY-MM-DD (example: 2027-03-15)." << std::endl;
    }
}

inline bool askYesNo(std::string message) {
    while (true) {
        std::string answer = readLine(message + " (Y/N): ");
        if (answer == "Y" || answer == "y") {
            return true;
        }
        if (answer == "N" || answer == "n") {
            return false;
        }
        std::cout << "Please type Y or N." << std::endl;
    }
}

inline void pressEnter() {
    readLine("\nPress Enter to continue...");
}

// inventory class 

class Inventory {
private:
    DynamicArray<Medicine> medicines;

public:
    //returns how many medicines are in the inventory
    int getSize() const {
        return medicines.size();
    }

    // returns the medicine at a position (used by other modules)
    Medicine getAt(int index) const {
        return medicines[index];
    }

    //returns the whole array. Yazi's searchMenu, sortMenu, and
    // monitoring menu take this.
    const DynamicArray<Medicine>& getMedicines() const {
        return medicines;
    }

    //finds the position of a product code. Returns -1 if not found.
    int findIndex(std::string code) const {
        code = toUpper(code);
        for (int i = 0; i < medicines.size(); i++) {
            if (medicines[i].code == code) {
                return i;
            }
        }
        return -1;
    }

    //adds a medicine in the correct sorted position.
    //returns false if the product code already exists.
    bool addMedicineToArray(Medicine m) {
        m.code = toUpper(m.code);

        if (findIndex(m.code) != -1) {
            return false;
        }

        // find the first medicine with a bigger code, insert before it
        int position = 0;
        while (position < medicines.size() && medicines[position].code < m.code) {
            position++;
        }

        medicines.insertAt(position, m);
        return true;
    }

    //subtracts stock after a sale. Returns false if there is not enough stock.
    bool deductStock(std::string code, int amount) {
        int index = findIndex(code);
        if (index == -1) {
            return false;
        }
        if (amount <= 0 || medicines[index].quantity < amount) {
            return false;
        }

        medicines[index].quantity = medicines[index].quantity - amount;
        return true;
    }

    //1. Add Medicine
    void addMedicine() {
        printTitle("ADD MEDICINE");

        Medicine m;

        // the product code must be unique
        while (true) {
            m.code = toUpper(readText("Product Code: "));
            if (findIndex(m.code) != -1) {
                std::cout << "That product code already exists." << std::endl;
            } else {
                break;
            }
        }

        m.name = readText("Medicine Name: ");
        m.price = readPrice("Price: ");
        m.quantity = readInt("Quantity: ", 0, 1000000);
        m.expiration = readDate("Expiration Date (YYYY-MM-DD): ");

        addMedicineToArray(m);
        std::cout << std::endl << "Medicine added successfully." << std::endl;
        pressEnter();
    }

    //2. View All Medicines
    void viewAllMedicines() {
        printTitle("ALL MEDICINES");

        if (medicines.empty()) {
            std::cout << "There are no medicines in the inventory." << std::endl;
        } else {
            printMedicineHeader();
            for (int i = 0; i < medicines.size(); i++) {
                printMedicineRow(medicines[i]);
            }
            std::cout << std::endl << "Total medicines: " << medicines.size() << std::endl;
        }
        pressEnter();
    }

    //3. Update Medicine
    void updateMedicine() {
        printTitle("UPDATE MEDICINE");

        if (medicines.empty()) {
            std::cout << "There are no medicines to update." << std::endl;
            pressEnter();
            return;
        }

        std::string code = readText("Enter the Product Code to update: ");
        int index = findIndex(code);

        if (index == -1) {
            std::cout << "Medicine not found." << std::endl;
            pressEnter();
            return;
        }

        Medicine m = medicines[index];
        std::cout << std::endl << "Current information:" << std::endl;
        printMedicineHeader();
        printMedicineRow(m);

        // The product code cannot be changed because the array is sorted by it
        std::cout << std::endl << "What do you want to update?" << std::endl;
        std::cout << "1. Name" << std::endl;
        std::cout << "2. Price" << std::endl;
        std::cout << "3. Stock Quantity" << std::endl;
        std::cout << "4. Expiration Date" << std::endl;
        std::cout << "5. Cancel" << std::endl;
        int choice = readInt("Enter your choice: ", 1, 5);

        if (choice == 5) {
            std::cout << "Update cancelled." << std::endl;
            pressEnter();
            return;
        }

        if (choice == 1) {
            m.name = readText("New Name: ");
        } else if (choice == 2) {
            m.price = readPrice("New Price: ");
        } else if (choice == 3) {
            m.quantity = readInt("New Quantity: ", 0, 1000000);
        } else if (choice == 4) {
            m.expiration = readDate("New Expiration Date (YYYY-MM-DD): ");
        }

        if (askYesNo("Save the changes?")) {
            medicines[index] = m;
            std::cout << "Medicine updated successfully." << std::endl;
        } else {
            std::cout << "Update cancelled. Nothing was changed." << std::endl;
        }
        pressEnter();
    }

    //4. Delete Medicine
    void deleteMedicine() {
        printTitle("DELETE MEDICINE");

        if (medicines.empty()) {
            std::cout << "There are no medicines to delete." << std::endl;
            pressEnter();
            return;
        }

        std::string code = readText("Enter the Product Code to delete: ");
        int index = findIndex(code);

        if (index == -1) {
            std::cout << "Medicine not found." << std::endl;
            pressEnter();
            return;
        }

        std::cout << std::endl;
        printMedicineHeader();
        printMedicineRow(medicines[index]);
        std::cout << std::endl;

        if (askYesNo("Are you sure you want to delete this medicine?")) {
            medicines.removeAt(index);
            std::cout << "Medicine deleted successfully." << std::endl;
        } else {
            std::cout << "Delete cancelled." << std::endl;
        }
        pressEnter();
    }

    // inventory management menu
    void runMenu() {
        int choice = 0;

        while (choice != 5) {
            printTitle("INVENTORY MANAGEMENT");
            std::cout << "1. Add Medicine" << std::endl;
            std::cout << "2. View All Medicines" << std::endl;
            std::cout << "3. Update Medicine" << std::endl;
            std::cout << "4. Delete Medicine" << std::endl;
            std::cout << "5. Return to Main Menu" << std::endl;
            printLine();

            choice = readInt("Enter your choice: ", 1, 5);

            if (choice == 1) {
                addMedicine();
            } else if (choice == 2) {
                viewAllMedicines();
            } else if (choice == 3) {
                updateMedicine();
            } else if (choice == 4) {
                deleteMedicine();
            }
        }
    }
};

#endif
