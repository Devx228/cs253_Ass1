# cs253_Ass1
# Library Management System

This is a simple command-line library management system written in C++.
## Features

- **Book Borrowing and Returning:**  
  Users (Students and Faculty) can borrow and return books. Fines are applied for overdue returns (for students).

- **Reserve Feature:**  
  If a book is already borrowed, a user may reserve it. When the book is returned, if it is reserved, it remains in a reserved state so that only the reserving user can borrow it.

- **Empty Library Check:**  
  If the library contains no books, the system displays the message "No book available" when a user tries to search or borrow a book.

  In the current implementation, any user can increment the day count, which isn't ideal. This can be revised so that only the librarian has the necessary access—using role-based controls on both the user 
  interface and the backend—to ensure proper system management.Due to some timing issues and the complexity of this, I didn't update this properly but it can be managed accordingly.

- **Data Encoding (Books and Users):**  
  The library uses text files (`books.txt` and `users.txt`) to store data:

  - **`books.txt`**  
    - **First Line:** The current day (integer) representing the library’s time.  
    - **Subsequent Lines:** Each line encodes one book in the format  
      ```sql
      Title|Author|Publisher|Year|ISBN|Status|DueDay
      ```
      For example:
      ```sql
      C++ Primer|Lippman|Addison-Wesley|2012|001|Available|0
      ```
  
  - **`users.txt`**  
    Each line encodes one user in the format  
    ```sql
    UserType|Name|ID|maxBorrowed|maxPeriod|fineRate|Fine|BorrowedBookISBN1|BorrowedBookISBN2|...
    ```
    - **UserType:** `Student`, `Faculty`, or `Librarian`  
    - **Name:** The user’s name  
    - **ID:** Unique identifier  
    - **maxBorrowed:** Maximum books the user can borrow  
    - **maxPeriod:** Maximum number of days per borrow  
    - **fineRate:** Fine rate (rupees per overdue day)  
    - **Fine:** Current outstanding fine (reset when loading)  
    - **BorrowedBookISBNs:** Additional fields for each borrowed book’s ISBN

- **Persistence:**  
  The state of books and users is saved in text files (e.g., `books.txt` and `users.txt`) between runs.

## Compilation Instructions

1. Open a terminal in the project directory where the source files are located.

2. Compile the code using the following command (ensure all source files are included):

   ```bash
   g++ -o library main.cpp Library.cpp Book.cpp Account.cpp User.cpp Menu.cpp

3. After Successful compilation, run the software by executing:
   ```bash
   ./library

