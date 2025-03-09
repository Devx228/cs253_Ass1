#include "Account.h"
#include <iostream>
#include <algorithm>
using namespace std;

Account::Account(double fr, int mp)
    : outstandingFines(0.0), fineRate(fr), maxPeriod(mp) {}

bool Account::borrowBook(Book &book, int currentDay) {
    // Assume availability is checked before calling.
    book.borrow(currentDay, maxPeriod);
    borrowedBooks.push_back(&book);
    return true;
}

bool Account::returnBook(Book &book, int currentDay) {
    auto it = find(borrowedBooks.begin(), borrowedBooks.end(), &book);
    if (it == borrowedBooks.end())
        return false;
    int overdue = currentDay - book.getDueDay();
    if (overdue > 0) {
        if (fineRate > 0) {
            outstandingFines += overdue * fineRate;
            cout << "Book returned " << overdue << " days late. Fine added: "
                 << overdue * fineRate << " rupees.\n";
        } else {
            cout << "Book returned " << overdue << " days late. No fine for faculty.\n";
        }
    }
    borrowingHistory.push_back(book.getISBN());
    borrowedBooks.erase(it);
    book.returnBook();
    return true;
}

double Account::calculateFine() const { return outstandingFines; }
void Account::payFines() { outstandingFines = 0.0; }
double Account::getOutstandingFines() const { return outstandingFines; }
const vector<Book*>& Account::getBorrowedBooks() const { return borrowedBooks; }
const vector<string>& Account::getBorrowingHistory() const { return borrowingHistory; }
void Account::addBorrowedBook(Book* b) { borrowedBooks.push_back(b); }
