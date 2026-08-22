---
title: "Practice Projects"
bookHidden: true
header: 'CS0.101 Computer Programming (Monsoon 24)'
footer: '![width:100px](IIIT_Hyderabad_Logo.jpg)'
---


# 🧠 C Mini Projects for Practice — Dynamic Memory, Structs, Enums & File I/O

These projects are designed to test and reinforce your understanding of:
- Dynamic Memory Allocation (`malloc`, `calloc`, `realloc`, `free`)
- Structs and Enums
- Pointers and Arrays
- File I/O (`fopen`, `fprintf`, `fscanf`, etc.)
- Modular Design and Debugging

Each project can typically be completed in **1–2 weeks** with good testing and documentation.


More projects available here:  
https://github.com/cpro-iiit/snake-project-starter.        
https://cs50.harvard.edu/x/2023/labs/4/smiley/.      
https://cs50.harvard.edu/x/2023/labs/4/volume/.    
https://cs50.harvard.edu/x/2023/labs/5/.    
https://cs50.harvard.edu/x/2023/labs/2/.    
 
Reading/understanding these code and adding to it, will give you the confidence for large scale coding.

---

## 🚀 Project 1: Student Record Management System

### Description
Build a program to manage student records (name, roll number, marks, grade, etc.). Support dynamic addition/deletion of students, sorting by marks, and saving/loading from file.

### Key Concepts
- Dynamic arrays of structs
- File I/O (save/load)
- Struct assignment and deep copies

### Example Features
- Add/Delete/Update students
- Calculate class average
- Write to `records.txt`

---

## 🧾 Project 2: Inventory Tracker for a Store

### Description
Implement a simple inventory system that tracks items, quantities, and prices.

### Key Concepts
- Structs for product info
- File persistence
- Enum for category (ELECTRONICS, FOOD, CLOTHING)

### Features
- Add/Remove items
- Search by name
- Generate invoice file

---

## 🧩 Project 3: Library Management System

### Description
Manage a small digital library database.

### Key Concepts
- Linked list of books (dynamic allocation)
- Struct with nested structs (Book, Author)
- File I/O to store data between runs

### Features
- Add/Remove/Search books
- Issue/Return functionality
- Save state to `library.dat`

---

## 🧮 Project 4: Matrix Operations Toolkit

### Description
Write a program to handle matrix operations (addition, multiplication, transpose, determinant).

### Key Concepts
- 2D dynamic arrays (pointer to pointer)
- Functions that allocate and free matrices
- Error checking for dimensions

### Bonus
- Include file-based input/output for matrices.

---

## 🧠 Project 5: Quiz Game with Leaderboard

### Description
A text-based quiz game that reads questions from a file, accepts answers, and maintains a leaderboard.

### Key Concepts
- File I/O for question bank and leaderboard
- Struct for player data
- Enum for difficulty level

### Features
- Add questions via file
- Randomize question order
- Save top 5 scores

---


## 🧑‍🤝‍🧑 Project 6 — Mini Social Network

### 🎯 Goal
Simulate a simple social network using `structs`, `pointers`, and `dynamic memory`.

### 🧩 Key Concepts
- Dynamic memory (`malloc`, `realloc`, `free`)
- Structs with pointer fields
- Recursion for “friends-of-friends”
- File persistence
- Bidirectional relationships

### 🗂️ Example Structures

```c
typedef struct Person {
    char name[30];
    struct Person** friends;
    int num_friends;
} Person;
```

### 🧾 Features
1. Add new people
2. Add friendships (bi-directional links)
3. Print network connections
4. Save / load network from file

### 💡 Example Run
```
Enter name: Alice
Enter name: Bob
Make friends? (Alice, Bob): y
Friendship created!
Alice’s friends: Bob
Bob’s friends: Alice
```

---

## 🏪 Project 7 — Store Receipt Management System

### 🎯 Goal
Create a store checkout and receipt generator that stores items, computes totals, and saves transactions.

### 🧩 Key Concepts
- Structs for product, cart item, and receipt
- Enums for product category
- Dynamic arrays for cart items
- File I/O for saving receipts

### 🗂️ Example Structures

```c
typedef enum {
    GROCERY,
    ELECTRONICS,
    CLOTHING
} Category;

typedef struct {
    int id;
    char name[50];
    float price;
    Category type;
} Product;

typedef struct {
    Product *product;
    int quantity;
} CartItem;

typedef struct {
    int receipt_id;
    CartItem *items;
    int item_count;
    float total;
} Receipt;
```

### 💻 Features
1. Add products
2. Display catalog
3. Add to cart dynamically
4. Generate and print receipts
5. Save receipts to file

### 💾 Example Output
```
===== STORE MENU =====
1. Add product
2. Purchase
3. Print receipt
4. Exit

Product: Milk
Qty: 2
Total: 91.00
Receipt saved to receipts.txt
```

---

## 🏧 Project 8 — ATM Transaction System

### 🎯 Goal
Simulate an ATM machine where users can create accounts, deposit, withdraw, and view transaction history.

### 🧩 Key Concepts
- Structs and enums
- Dynamic transaction list
- File I/O for persistence
- Secure PIN check

### 🗂️ Example Structures

```c
typedef enum {
    DEPOSIT,
    WITHDRAWAL,
    BALANCE_CHECK
} TransactionType;

typedef struct {
    TransactionType type;
    float amount;
    char timestamp[30];
} Transaction;

typedef struct {
    int account_number;
    char name[50];
    int pin;
    float balance;
    Transaction* history;
    int transaction_count;
} Account;
```

### 💻 Features
1. Create account
2. Login with PIN
3. Deposit / Withdraw
4. Show balance and transactions
5. Save all data to file

### 🧾 Example Output
```
=== ATM SYSTEM ===
1. Create Account
2. Login
3. Exit

Account created: Alice (Acc #1001)
Deposit 500 → Balance = 500.00
Withdraw 100 → Balance = 400.00
```

---

## Project 9 - Fractals

Read about Fractals, Madelbrot Set and BMP image format:
- https://en.wikipedia.org/wiki/Fractal.  
- https://en.wikipedia.org/wiki/Mandelbrot_set 
- https://en.wikipedia.org/wiki/BMP_file_format 

Understand the code for generating a BMP image of Madelbrot Set Fractal here: [madelbrot](./madelbrot.c). There are also several exercises given in the comments, including modifying the code to generate the [Julia set](https://en.wikipedia.org/wiki/Julia_set), which you can try.  
 
Modularize the code, by splitting it into several files/folders and have a makefile.


---

## Project 10: Image editor

Learn about the [PPM image format](https://en.wikipedia.org/wiki/Netpbm) and complete the exercises in the code: [image editor](./image_editor.c).

Also modularize the code by splitting it into headers, .c files, include, src folder and add makefile.

---

## Project 11 - Jon Conway's Game of Life

Read about John Conway's Game of life:
- https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life 
- https://playgameoflife.com/ 

Complete the c code implementing it here: [gameoflife.c](./gameoflife.c)

# 🗂️ Submission & Documentation Checklist

### 1. Cover Page
Include title, student details, course name, instructor name, and date.

### 2. Project Report (3–5 pages)
#### Recommended Sections
- Introduction  
- Design and Approach  
- Implementation Details  
- Testing and Results  
- Conclusion and Future Work  

### 3. Source Code Folder
- `.c` files and a `Makefile`
- Use header files for modularity
- Compile with `gcc -Wall -Wextra`

### 4. README File
- Compilation and execution instructions
- Input/output format description
- Example runs

### 5. Example Input/Output Files
Include at least **3 test cases**:
- Small, medium, and edge-case dataset.

### 6. Evaluation Rubric

| Criteria | Description | Marks |
|-----------|--------------|-------|
| Correctness | Program compiles and meets requirements | 30 |
| Memory Handling | Proper use of malloc/free, no leaks | 15 |
| Structs/Enums | Modular and clean design | 15 |
| File I/O | Robust input/output | 10 |
| Code Quality | Comments, naming, readability | 10 |
| Testing & Documentation | Examples, explanations | 20 |
| **Total** |  | **100** |

---

**💡 Tip:** Always run your code through Valgrind to check for memory leaks before submission!
