#include "User.h"
#include "Book.h"
#include "Library.h"
#include <iostream>
using namespace std;

User::User(string n, string i, int mb, int mp, double fr)
    : name(n), id(i), maxBorrowed(mb), maxPeriod(mp), fineRate(fr) {
    account = new Account(fineRate, maxPeriod);
}

User::~User() { delete account; }

string User::getName() const { return name; }
string User::getId() const { return id; }
int User::getMaxBorrowed() const { return maxBorrowed; }
int User::getMaxPeriod() const { return maxPeriod; }
double User::getFineRate() const { return fineRate; }

bool User::canBorrow(int currentDay) const {
    return (account->getBorrowedBooks().size() < (size_t)maxBorrowed) &&
           (account->getOutstandingFines() == 0);
}

bool User::borrowBook(Book &book, int currentDay) {
    if (!canBorrow(currentDay) || !book.getIsAvailable()) {
        if (account->getOutstandingFines() > 0)
            cout << "Outstanding fines exist. Please clear them before borrowing.\n";
        return false;
    }
    // For Faculty (fineRate == 0), check for any overdue books > 60 days.
    if (fineRate == 0) {
        for (Book* b : account->getBorrowedBooks()) {
            if (currentDay - b->getDueDay() > 60) {
                cout << "Cannot borrow: a book is overdue by more than 60 days.\n";
                return false;
            }
        }
    }
    return account->borrowBook(book, currentDay);
}

bool User::returnBook(Book &book, int currentDay) {
    return account->returnBook(book, currentDay);
}
bool User::reserveBook(Book &book) {
    if (book.getStatus() == "Borrowed") {
         book.reserve(this);
         return true;
    } else if (book.getStatus() == "Reserved") {
         if (book.getReservedBy() == this)
             cout << "You have already reserved this book.\n";
         else
             cout << "Book is already reserved by another user.\n";
         return false;
    } else {
         cout << "Book is available; you can borrow it directly.\n";
         return false;
    }
}

double User::calculateFine() const { return account->calculateFine(); }

Student::Student(string n, string i)
    : User(n, i, 3, 15, 10.0) {}

Faculty::Faculty(string n, string i)
    : User(n, i, 5, 30, 0.0) {}

Librarian::Librarian(string n, string i)
    : User(n, i, 0, 0, 0.0) {}

bool Librarian::borrowBook(Book &book, int currentDay) {
    cout << "Librarians cannot borrow books!\n";
    return false;
}

// Librarian management methods
void Librarian::addBook(Library &lib, Book* book) {
    lib.addBook(book);
}

void Librarian::removeBook(Library &lib, const string& ISBN) {
    lib.removeBook(ISBN);
}

void Librarian::addUser(Library &lib, User* user) {
    lib.addUser(user);
}

void Librarian::removeUser(Library &lib, const string& id) {
    lib.removeUser(id);
}
