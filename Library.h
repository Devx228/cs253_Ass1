#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <string>
#include "Book.h"
#include "User.h"
using namespace std;

class Library {
private:
    vector<Book*> books;
    vector<User*> users;
    int currentDay;
    
    // Private management functions
    void addBook(Book* book);
    void removeBook(const string& ISBN);
    void addUser(User* user);
    void removeUser(const string& id);
public:
    Library();
    ~Library();
    
    // Public interface
    Book* searchBook(const string& query);
    User* searchUser(const string& id);
    void incrementDay(int days = 1);
    int getCurrentDay() const;
    bool isEmpty() const;
    
    void saveState();
    void loadState();
    
    // Give Librarian friend access
    friend class Librarian;
};

#endif
