
#include <iostream>
#include <chrono>
#include <iomanip>
#include <string>
#include <vector>
#include "Medicine.h"
#include "DynamicArray.h"
#include "Searching.h"
#include "Sorting.h"

using Clock = std::chrono::steady_clock;

// Generate sample medicine records
DynamicArray<Medicine> generateMedicines(int size) {
    DynamicArray<Medicine> medicines;

    for (int i = 0; i < size; i++) {
        Medicine medicine;

        medicine.code = "MED" + std::to_string(100000 + i);
        medicine.name = "Medicine " + std::to_string(i);
        medicine.price = 50.00 + i;
        medicine.quantity = 100;
        
        // Dates are generated in YYYY-MM-DD format
        int day = (i % 28) + 1;
        int month = ((i / 28) % 12) + 1;

        medicine.expiration =
           std::string("2027-") +
           (month < 10 ? "0" : "") + std::to_string(month) +
           "-" +
           (day < 10 ? "0" : "") + std::to_string(day);

        medicines.push_back(medicine);
    }

    return medicines;
}

// Measure Linear Search
double benchmarkLinearSearch(
    const DynamicArray<Medicine>& medicines,
    int repetitions
) {
    auto start = Clock::now();

    for (int i = 0; i < repetitions; i++) {
        // Search for a medicine that does not exist
        for (int j = 0; j < medicines.size(); j++) {
            if (medicines[j].code == "NOTFOUND") {
                break;
            }
        }
    }

    auto end = Clock::now();

    return std::chrono::duration<double, std::milli>(
        end - start
    ).count() / repetitions;
}

// Measure Binary Search
double benchmarkBinarySearch(
    const DynamicArray<Medicine>& medicines,
    int repetitions
) {
    auto start = Clock::now();

    for (int i = 0; i < repetitions; i++) {
        int low = 0;
        int high = medicines.size() - 1;
        std::string target = "NOTFOUND";

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (medicines[mid].code == target) {
                break;
            }
            else if (medicines[mid].code < target) {
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }
    }

    auto end = Clock::now();

    return std::chrono::duration<double, std::milli>(
        end - start
    ).count() / repetitions;
}

// Measure Insertion Sort
double benchmarkInsertionSort(
    const DynamicArray<Medicine>& original,
    int repetitions
) {
    auto start = Clock::now();

    for (int i = 0; i < repetitions; i++) {
        DynamicArray<Medicine> medicines = original;

        for (int j = 1; j < medicines.size(); j++) {
            Medicine key = medicines[j];
            int k = j - 1;

            while (k >= 0 &&
                   medicines[k].expiration > key.expiration) {
                medicines[k + 1] = medicines[k];
                k--;
            }

            medicines[k + 1] = key;
        }
    }

    auto end = Clock::now();

    return std::chrono::duration<double, std::milli>(
        end - start
    ).count() / repetitions;
}

int main() {
    const int repetitions = 5;

    int searchSizes[] = {100, 1000, 5000, 10000};
    int sortSizes[] = {100, 1000, 5000, 10000};

    std::cout << std::fixed << std::setprecision(6);

    std::cout << "\n========================================\n";
    std::cout << " PHARMACY SYSTEM PERFORMANCE BENCHMARK\n";
    std::cout << "========================================\n";

    // SEARCHING BENCHMARK
    std::cout << "\nSEARCHING PERFORMANCE\n";
    std::cout << "----------------------------------------\n";
    std::cout << std::setw(12) << "Input Size"
              << std::setw(20) << "Linear (ms)"
              << std::setw(20) << "Binary (ms)" << "\n";

    for (int size : searchSizes) {
        DynamicArray<Medicine> medicines =
            generateMedicines(size);

        double linearTime =
            benchmarkLinearSearch(medicines, repetitions);

        double binaryTime =
            benchmarkBinarySearch(medicines, repetitions);

        std::cout << std::setw(12) << size
                  << std::setw(20) << linearTime
                  << std::setw(20) << binaryTime << "\n";
    }

    // SORTING BENCHMARK
    std::cout << "\nINSERTION SORT PERFORMANCE\n";
    std::cout << "----------------------------------------\n";
    std::cout << std::setw(12) << "Input Size"
              << std::setw(20) << "Average (ms)" << "\n";

    for (int size : sortSizes) {
        DynamicArray<Medicine> medicines =
            generateMedicines(size);

        double sortingTime =
            benchmarkInsertionSort(medicines, repetitions);

        std::cout << std::setw(12) << size
                  << std::setw(20) << sortingTime << "\n";
    }

    std::cout << "\nBenchmark completed.\n";

    return 0;
}