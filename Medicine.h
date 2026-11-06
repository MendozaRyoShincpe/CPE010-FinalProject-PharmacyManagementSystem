#ifndef MEDICINE_H
#define MEDICINE_H

#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>

// This stores the information of one medicine
struct Medicine {
    std::string code;         // product code (always UPPERCASE)
    std::string name;
    double price = 0;
    int quantity = 0;
    std::string expiration;   // format is YYYY-MM-DD (example: 2027-03-15)
};

// Checks if the date is written correctly as YYYY-MM-DD
inline bool isValidDate(std::string date) {
    // must be 10 characters long
    if (date.length() != 10) {
        return false;
    }

    // the dashes must be in the correct place
    if (date[4] != '-' || date[7] != '-') {
        return false;
    }

    // all the other characters must be digits
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) {
            continue;
        }
        if (date[i] < '0' || date[i] > '9') {
            return false;
        }
    }

    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

    if (year < 1900 || year > 2200) {
        return false;
    }
    if (month < 1 || month > 12) {
        return false;
    }

    // find how many days the month has
    int maxDay = 31;
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        maxDay = 30;
    }
    if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
            maxDay = 29;   // leap year
        } else {
            maxDay = 28;
        }
    }

    if (day < 1 || day > maxDay) {
        return false;
    }
    return true;
}

// Prints the column titles of the medicine table
inline void printMedicineHeader() {
    std::cout << std::left << std::setw(10) << "CODE"
              << std::setw(25) << "NAME"
              << std::setw(10) << "PRICE"
              << std::setw(8) << "QTY"
              << "EXPIRATION" << std::endl;
    std::cout << "------------------------------------------------------------" << std::endl;
}

// Prints one medicine as one row of the table
inline void printMedicineRow(const Medicine& m) {
    std::cout << std::left << std::setw(10) << m.code
              << std::setw(25) << m.name
              << std::setw(10) << std::fixed << std::setprecision(2) << m.price
              << std::setw(8) << m.quantity
              << m.expiration << std::endl;
}

#endif
