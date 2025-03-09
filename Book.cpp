#include "Book.h"
#include <iostream>

Book::Book(string t, string a, string pub, int y, string isbn)
    : title(t), author(a), publisher(pub), year(y), ISBN(isbn),
      status("Available"), dueDay(0), reservedBy(nullptr) {}

string Book::getTitle() const { return title; }
string Book::getAuthor() const { return author; }
string Book::getPublisher() const { return publisher; }
int Book::getYear() const { return year; }
string Book::getISBN() const { return ISBN; }
string Book::getStatus() const { return status; }
bool Book::getIsAvailable() const { return status == "Available"; }
int Book::getDueDay() const { return dueDay; }
User* Book::getReservedBy() const { return reservedBy; }

void Book::borrow(int currentDay, int period) {
    // Allow borrowing if the book is available or if reserved by the same user.
    if (status == "Available" || status == "Reserved") {
         status = "Borrowed";
         dueDay = currentDay + period;
         clearReservation();  // Clear any reservation upon borrowing.
    }
}

void Book::returnBook() {
    if (reservedBy != nullptr) {
         // If reserved, do not mark as available.
         status = "Reserved";
         dueDay = 0; // Reset due day – the reserving user must now borrow it.
    } else {
         status = "Available";
         dueDay = 0;
    }
}

void Book::reserve(User* user) {
    // Only allow reservation if the book is currently borrowed.
    if (status == "Borrowed") {
         if (reservedBy == nullptr) {
             reservedBy = user;
             status = "Reserved";
             cout << "Book reserved successfully.\n";
         } else {
             cout << "Book is already reserved.\n";
         }
    } else {
         cout << "Book is available. You can borrow it directly.\n";
    }
}

void Book::clearReservation() {
    reservedBy = nullptr;
}

void Book::setStatus(const string &s) { status = s; }
void Book::setDueDay(int d) { dueDay = d; }
