#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <string>
#include <limits>
#include <cctype>
#include <ctime>
#include <cstdio>

// Read a line of text
inline std::string readLine(const std::string& prompt) {
    std::string value;

    std::cout << prompt;
    std::getline(std::cin, value);

    return value;
}

// Read and validate an integer within a range
inline int readInt(
    const std::string& prompt,
    int minimum,
    int maximum
) {
    int value;

    while (true) {
        std::cout << prompt;

        if (std::cin >> value &&
            value >= minimum &&
            value <= maximum) {

            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n'
            );

            return value;
        }

        std::cout << "Invalid input. Enter a number from "
                  << minimum << " to " << maximum << ".\n";

        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n'
        );
    }
}

// Convert text to uppercase
inline std::string toUpper(const std::string& text) {
    std::string result = text;

    for (int i = 0; i < static_cast<int>(result.length()); i++) {
        result[i] = static_cast<char>(
            std::toupper(static_cast<unsigned char>(result[i]))
        );
    }

    return result;
}

// Convert text to lowercase
inline std::string toLower(const std::string& text) {
    std::string result = text;

    for (int i = 0; i < static_cast<int>(result.length()); i++) {
        result[i] = static_cast<char>(
            std::tolower(static_cast<unsigned char>(result[i]))
        );
    }

    return result;
}

// Display a section heading
inline void printTitle(const std::string& title) {
    std::cout << "\n========================================\n";
    std::cout << "          " << title << "\n";
    std::cout << "========================================\n";
}

// Display a separator
inline void printLine() {
    std::cout << "----------------------------------------\n";
}

// Get current date in YYYY-MM-DD format
inline std::string currentDate() {
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

// Calculate the number of days between two YYYY-MM-DD dates
inline int daysBetween(
    const std::string& startDate,
    const std::string& endDate
) {
    int startYear, startMonth, startDay;
    int endYear, endMonth, endDay;

    if (std::sscanf(
            startDate.c_str(),
            "%d-%d-%d",
            &startYear, &startMonth, &startDay
        ) != 3) {
        return -1;
    }

    if (std::sscanf(
            endDate.c_str(),
            "%d-%d-%d",
            &endYear, &endMonth, &endDay
        ) != 3) {
        return -1;
    }

    std::tm start = {};
    start.tm_year = startYear - 1900;
    start.tm_mon = startMonth - 1;
    start.tm_mday = startDay;
    start.tm_hour = 12;

    std::tm end = {};
    end.tm_year = endYear - 1900;
    end.tm_mon = endMonth - 1;
    end.tm_mday = endDay;
    end.tm_hour = 12;

    std::time_t startTime = std::mktime(&start);
    std::time_t endTime = std::mktime(&end);

    if (startTime == -1 || endTime == -1) {
        return -1;
    }

    double difference = std::difftime(endTime, startTime);

    return static_cast<int>(difference / (60 * 60 * 24));
}

#endif