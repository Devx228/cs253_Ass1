#ifndef BOOK_H
#define BOOK_H

#include <string>
using namespace std;

// Forward declaration to avoid circular dependency.
class User;

class Book {
private:
    string title;
    string author;
    string publisher;
    int year;
    string ISBN;
    string status; // "Available", "Borrowed", or "Reserved"
    int dueDay;
    User* reservedBy;

public:
    Book(string t, string a, string pub, int y, string isbn);

    // Getters
    string getTitle() const;
    string getAuthor() const;
    string getPublisher() const;
    int getYear() const;
    string getISBN() const;
    string getStatus() const;
    bool getIsAvailable() const;
    int getDueDay() const;
    User* getReservedBy() const;

    // Methods
    void borrow(int currentDay, int period);
    void returnBook();
       
    void reserve(User* user);  
    void clearReservation();

    void setStatus(const string &s);
    void setDueDay(int d);
};

#endif
