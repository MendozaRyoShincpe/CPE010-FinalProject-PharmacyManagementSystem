# Pharmacy Management System

A console-based Pharmacy Management System developed using **C++** for the CPE010 – Data Structures and Algorithms course at Technological Institute of the Philippines – Quezon City.

The system simulates the basic operations of a single-branch pharmacy, including medicine inventory management, customer queue handling, sales processing, and transaction monitoring. It demonstrates the practical application of different data structures and algorithms in managing pharmacy operations.

## Project Information

| **Information** | **Details** |
|---|---|
| Course | CPE010 – Data Structures and Algorithms |
| Program / Section | Computer Engineering – CPE21S1 |
| Project | Pharmacy Management System |
| Programming Language | C++ |
| Compiler Standard | C++17 |
| Interface | Console-Based |
| Group | Group 5 |

## Features

### 1. Medicine Inventory Management
- Add new medicine records.
- View available medicines.
- Update medicine information.
- Delete medicine records.
- Maintain inventory records using product codes.

### 2. Medicine Searching
- Search medicines by name using Linear Search.
- Search medicines by product code using Binary Search.

### 3. Medicine Sorting
- Sort medicine records by expiration date using Insertion Sort.

### 4. Stock and Expiration Monitoring
- Monitor medicines with low stock levels.
- Identify expired medicines.
- Monitor medicines nearing their expiration dates.

### 5. Customer Queue Management
- Add customers to the waiting queue.
- View the next customer.
- Serve customers using the First-In, First-Out (FIFO) principle.

### 6. Sales and Checkout
- Process customer purchases.
- Validate available medicine quantities.
- Calculate purchase totals.
- Update inventory after successful purchases.

### 7. Transaction Management
- View recent transactions using a Stack.
- View permanent transaction history.
- Search transaction records by transaction ID.

### 8. File Management
- Save medicine inventory records.
- Load previously saved inventory data.
- Store transaction records in text files.
- Maintain data even after the program is closed.

## Data Structures and Algorithms Used

| **Data Structure / Algorithm** | **Application in the System** |
|---|---|
| Dynamic Array | Stores and manages medicine inventory records. |
| Queue (Linked List) | Manages customers waiting for service using FIFO. |
| Stack (Linked List) | Stores and displays recent transactions using LIFO. |
| Linear Search | Finds medicines based on their names. |
| Binary Search | Finds medicines using sorted product codes. |
| Insertion Sort | Arranges medicine records by expiration date. |

## Project Structure

```text
CPE010-FInalProject-PharmacySystem/
│
├── main.cpp
├── Medicine.h
├── DynamicArray.h
├── Inventory.h
├── Utilities.h
├── Searching.h
├── Sorting.h
├── Monitoring.h
├── Customer.h
├── Queue.h
├── CustomerQueue.h
├── Transaction.h
├── Stack.h
├── Transactions.h
├── Sales.h
├── FileManager.h
│
├── benchmark.cpp
├── medicines.txt
├── transactions.txt
│
└── README.md
```

## Requirements

Before running the program, make sure you have:

- A C++ compiler that supports C++17.
- GCC / MinGW-w64 or an equivalent C++ compiler.
- A terminal or command prompt.

## How to Compile and Run

### 1. Clone the Repository

Open your terminal or Command Prompt and execute:

```bash
git clone https://github.com/MendozaRyoShincpe/CPE010-FInalProject-PharmacySystem.git
```

### 2. Navigate to the Project Folder

```bash
cd CPE010-FInalProject-PharmacySystem
```

### 3. Compile the Program

```bash
g++ -std=c++17 -O2 main.cpp -o PharmacySystem.exe
```

### 4. Run the Program

For Windows:

```bash
.\PharmacySystem.exe
```

## Main Menu

The program provides the following main menu options:

```text
========================================
       PHARMACY MANAGEMENT SYSTEM
========================================

1. Inventory Management
2. Search Medicine
3. Sort Medicines by Expiration
4. Customer Queue Management
5. Sales and Checkout
6. Recent Transactions
7. Transaction History
8. Stock and Expiration Monitoring
9. Exit
```

Select an option by entering its corresponding number.

## Performance Benchmark

The project also includes `benchmark.cpp`, which measures the execution time of the implemented searching and sorting algorithms using different input sizes.

### Compile the Benchmark

```bash
g++ -std=c++17 -O2 -mconsole benchmark.cpp -o benchmark.exe
```

### Run the Benchmark

```bash
.\benchmark.exe
```

The benchmark evaluates:

- Linear Search
- Binary Search
- Insertion Sort

The measured execution times are used for the theoretical and experimental performance analysis.

## Team Members

| **Name** | **Student Number** | **Main Contribution** |
|---|---|---|
| Ryo Shin P. Mendoza | 2512353 | Project Leader, Main Program, Sales, File Management |
| Mike Justin A. Cabangon | 2513369 | Medicine, Dynamic Array, Inventory, Utilities |
| Prince Yazinel Corro | 2516028 | Searching, Sorting, Stock and Expiration Monitoring |
| Andrew Jr. S. Doloso | 2516697 | Customer, Queue, Customer Queue Management |
| Jave Joaquin C. Obias | 2517052 | Transaction, Stack, Transaction Management |

## Project Scope and Limitations

The Pharmacy Management System is designed for a single-branch pharmacy and operates through a console-based interface on one computer.

The system focuses on basic inventory management, medicine searching and sorting, customer queue management, sales processing, transaction tracking, and file-based data storage.

It does not currently support online purchases, delivery services, online payments, multiple branches, advanced accounting, prescription verification, or medical consultations.

## Acknowledgment

This project was developed as part of the requirements for **CPE010 – Data Structures and Algorithms** at the Technological Institute of the Philippines – Quezon City.

**Group 5 – CPE21S1**

2026
