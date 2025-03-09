#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <vector>
#include <string>
#include "Book.h"
using namespace std;

class Account {
private:
    vector<Book*> borrowedBooks;
    vector<string> borrowingHistory;
    double outstandingFines;
    double fineRate;
    int maxPeriod;
public:
    Account(double fr, int mp);
    
    bool borrowBook(Book &book, int currentDay);
    bool returnBook(Book &book, int currentDay);
    double calculateFine() const;
    void payFines();
    
    // Getter for fines and borrowed books
    double getOutstandingFines() const;
    const vector<Book*>& getBorrowedBooks() const;
    const vector<string>& getBorrowingHistory() const;
    
    // For restoring state
    void addBorrowedBook(Book* b);
};

#endif
