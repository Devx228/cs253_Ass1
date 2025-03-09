#include <iostream>
#include "Library.h"
#include "Menu.h"
#include "User.h"
#include "Book.h"
using namespace std;

int main() {
    Library library;
    library.loadState();
    
    // If no books exist (first run), initialize sample books and default users.
    if (library.isEmpty()) {
        Librarian libAdmin("Admin", "LIB001");
        libAdmin.addBook(library, new Book("C++ Primer", "Lippman", "Addison-Wesley", 2012, "001"));
        libAdmin.addBook(library, new Book("Clean Code", "Martin", "Prentice Hall", 2008, "002"));
        libAdmin.addBook(library, new Book("The C Programming Language", "Kernighan & Ritchie", "Prentice Hall", 1988, "003"));
        libAdmin.addBook(library, new Book("Design Patterns", "Gamma et al.", "Addison-Wesley", 1994, "004"));
        libAdmin.addBook(library, new Book("Effective C++", "Meyers", "O'Reilly", 2005, "005"));
        libAdmin.addUser(library, new Student("Alice", "STU001"));
        libAdmin.addUser(library, new Faculty("Dr. Smith", "FAC001"));
    }
    
    int mainChoice;
    do {
        cout << "\n=== Library System Main Menu (Day " << library.getCurrentDay() << ") ===\n";
        cout << "1. New Registration\n";
        cout << "2. Login\n";
        cout << "3. Increment Day\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> mainChoice;
        if (mainChoice == 1) {
            newRegistration(library);
        } else if (mainChoice == 2) {
            string loginId;
            cout << "Enter your ID to login: ";
            cin >> loginId;
            User* user = library.searchUser(loginId);
            if (user == nullptr) {
                cout << "User not found.\n";
            } else {
                if (dynamic_cast<Librarian*>(user))
                    librarianMenu(library, dynamic_cast<Librarian*>(user));
                else
                    userMenu(library, user);
            }
        } else if (mainChoice == 3) {
            int days;
            cout << "Enter number of days to increment: ";
            cin >> days;
            library.incrementDay(days);
            cout << "Current day is now " << library.getCurrentDay() << ".\n";
        } else if (mainChoice == 4) {
            cout << "Exiting and saving state...\n";
            library.saveState();
        } else {
            cout << "Invalid option. Try again.\n";
        }
    } while (mainChoice != 4);
    
    return 0;
}
