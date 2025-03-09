#ifndef USER_H
#define USER_H

#include <string>
#include "Account.h"
using namespace std;

class Book; // Forward declaration for Book (defined in Book.h)

class User {
protected:
    string name;
    string id;
    int maxBorrowed;
    int maxPeriod;
    double fineRate;
public:
    Account* account;  // Each user has an Account
    User(string n, string i, int mb, int mp, double fr);
    virtual ~User();
    
    // Getters
    string getName() const;
    string getId() const;
    int getMaxBorrowed() const;
    int getMaxPeriod() const;
    double getFineRate() const;
    
    // Methods
    virtual bool canBorrow(int currentDay) const;
    virtual bool borrowBook(Book &book, int currentDay);
    virtual bool returnBook(Book &book, int currentDay);
    virtual double calculateFine() const;

    virtual bool reserveBook(Book &book);
};

class Student : public User {
public:
    Student(string n, string i);
};

class Faculty : public User {
public:
    Faculty(string n, string i);
};

class Librarian : public User {
public:
    Librarian(string n, string i);
    bool borrowBook(Book &book, int currentDay) override;
    
    // Librarian management methods (to be used with Library)
    void addBook(class Library &lib, Book* book);
    void removeBook(class Library &lib, const string& ISBN);
    void addUser(class Library &lib, User* user);
    void removeUser(class Library &lib, const string& id);
};

#endif
