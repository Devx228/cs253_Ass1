#include "Menu.h"
#include <iostream>
using namespace std;

void newRegistration(Library &library) {
    int roleChoice;
    string name, id;
    cout << "\n--- New Registration ---\n";
    cout << "Enter role (1: Student, 2: Faculty, 3: Librarian): ";
    cin >> roleChoice;
    cout << "Enter your Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter your ID: ";
    cin >> id;
    
    User* newUser = nullptr;
    if (roleChoice == 1)
        newUser = new Student(name, id);
    else if (roleChoice == 2)
        newUser = new Faculty(name, id);
    else if (roleChoice == 3)
        newUser = new Librarian(name, id);
    else {
        cout << "Invalid role selection.\n";
        return;
    }
    
    if (library.searchUser(id) != nullptr) {
        cout << "A user with this ID already exists.\n";
        delete newUser;
    } else {
        // Using a temporary librarian to add the user
        Librarian temp("temp", "temp");
        temp.addUser(library, newUser);
        cout << "Registration successful!\n";
        // Save state so the new user is reflected in users.txt
        library.saveState();
    }
}
void userMenu(Library &library, User* user) {
    int choice;
    do {
        cout << "\n--- User Menu (Day " << library.getCurrentDay() << ") ---\n";
        cout << "Welcome, " << user->getName() << "\n";
        cout << "1. Borrow Book\n";
        cout << "2. Return Book\n";
        cout << "3. View Outstanding Fines\n";
        cout << "4. Pay Fines\n";
        cout << "5. View Borrowing History\n";
        cout << "6. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;
        
        if (choice == 1) {
            // Check if the library has any books
            if (library.isEmpty()) {
                cout << "No book available.\n";
            } else {
                string isbn;
                cout << "Enter ISBN of the book to borrow: ";
                cin >> isbn;
                Book* book = library.searchBook(isbn);
                if (!book) {
                    cout << "Book not found.\n";
                } else {
                    if (book->getStatus() == "Available") {
                        if (user->borrowBook(*book, library.getCurrentDay())) {
                            cout << "Book borrowed successfully.\n";
                            library.saveState();
                        } else {
                            cout << "Borrowing failed.\n";
                        }
                    } else if (book->getStatus() == "Reserved") {
                        if (book->getReservedBy() == user) {
                            // Reserved by this user; allow borrowing
                            if (user->borrowBook(*book, library.getCurrentDay())) {
                                cout << "Reserved book borrowed successfully.\n";
                                library.saveState();
                            } else {
                                cout << "Borrowing failed.\n";
                            }
                        } else {
                            cout << "Book is reserved by another user.\n";
                        }
                    } else { // status is "Borrowed"
                        cout << "Book is currently borrowed.\n";
                        char reserveChoice;
                        cout << "Would you like to reserve it? (y/n): ";
                        cin >> reserveChoice;
                        if (reserveChoice == 'y' || reserveChoice == 'Y') {
                            if (user->reserveBook(*book)) {
                                library.saveState();
                            }
                        }
                    }
                }
            }
        } else if (choice == 2) {
            string isbn;
            cout << "Enter ISBN of the book to return: ";
            cin >> isbn;
            Book* book = library.searchBook(isbn);
            if (book && user->returnBook(*book, library.getCurrentDay())) {
                cout << "Book returned successfully.\n";
                library.saveState();
            } else {
                cout << "Return failed.\n";
            }
        } else if (choice == 3) {
            cout << "Outstanding fines: " << user->calculateFine() << " rupees.\n";
        } else if (choice == 4) {
            user->account->payFines();
            cout << "Fines cleared.\n";
            library.saveState();
        } else if (choice == 5) {
            const auto &history = user->account->getBorrowingHistory();
            if (history.empty()) {
                cout << "No borrowing history available.\n";
            } else {
                cout << "Borrowing History:\n";
                for (const auto &isbn : history) {
                    cout << "Book ISBN: " << isbn << "\n";
                }
            }
        } else if (choice == 6) {
            cout << "Logging out...\n";
        } else {
            cout << "Invalid option. Try again.\n";
        }
    } while (choice != 6);
}


void librarianMenu(Library &library, Librarian* librarian) {
    int choice;
    do {
        cout << "\n--- Librarian Menu (Day " << library.getCurrentDay() << ") ---\n";
        cout << "Welcome, " << librarian->getName() << "\n";
        cout << "1. Add Book\n";
        cout << "2. Remove Book\n";
        cout << "3. Add User\n";
        cout << "4. Remove User\n";
        cout << "5. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;
        if (choice == 1) {
            string title, author, publisher, isbn;
            int year;
            cout << "Enter Book Title: ";
            cin.ignore();
            getline(cin, title);
            cout << "Enter Author: ";
            getline(cin, author);
            cout << "Enter Publisher: ";
            getline(cin, publisher);
            cout << "Enter Year: ";
            cin >> year;
            cout << "Enter ISBN: ";
            cin >> isbn;
            Book* newBook = new Book(title, author, publisher, year, isbn);
            librarian->addBook(library, newBook);
            cout << "Book added successfully.\n";
            // Save state so that the new book is reflected in books.txt
            library.saveState();
        } else if (choice == 2) {
            string isbn;
            cout << "Enter ISBN of the book to remove: ";
            cin >> isbn;
            librarian->removeBook(library, isbn);
            cout << "Book removed (if it existed).\n";
            library.saveState();
        } else if (choice == 3) {
            newRegistration(library);
            library.saveState();
        } else if (choice == 4) {
            string uid;
            cout << "Enter ID of the user to remove: ";
            cin >> uid;
            librarian->removeUser(library, uid);
            cout << "User removed (if existed).\n";
            library.saveState();
        } else if (choice == 5) {
            cout << "Logging out...\n";
        } else {
            cout << "Invalid option. Try again.\n";
        }
    } while (choice != 5);
}
