#include "Library.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
using namespace std;

Library::Library() : currentDay(0) {}

Library::~Library() {
    for (Book* b : books) delete b;
    for (User* u : users) delete u;
}

void Library::addBook(Book* book) { books.push_back(book); }

void Library::removeBook(const string& ISBN) {
    books.erase(remove_if(books.begin(), books.end(),
        [&](Book* b) { return b->getISBN() == ISBN; }), books.end());
}

void Library::addUser(User* user) { users.push_back(user); }

void Library::removeUser(const string& id) {
    users.erase(remove_if(users.begin(), users.end(),
        [&](User* u) { return u->getId() == id; }), users.end());
}

Book* Library::searchBook(const string& query) {
    for (Book* b : books) {
        if (b->getISBN() == query ||
            b->getTitle() == query ||
            b->getAuthor() == query)
            return b;
    }
    return nullptr;
}

User* Library::searchUser(const string& id) {
    for (User* u : users) {
        if (u->getId() == id)
            return u;
    }
    return nullptr;
}

void Library::incrementDay(int days) {
    currentDay += days;
}

int Library::getCurrentDay() const { return currentDay; }

bool Library::isEmpty() const { return books.empty(); }

void Library::saveState() {
    ofstream booksFile("books.txt");
    if (booksFile.is_open()) {
        booksFile << currentDay << "\n";
        for (Book* b : books) {
            booksFile << b->getTitle() << "|" << b->getAuthor() << "|" 
                      << b->getPublisher() << "|" << b->getYear() << "|" 
                      << b->getISBN() << "|" << b->getStatus() << "|" 
                      << b->getDueDay() << "\n";
        }
        booksFile.close();
    }
    ofstream usersFile("users.txt");
    if (usersFile.is_open()) {
        for (User* u : users) {
            string role = "User";
            if (dynamic_cast<Student*>(u))
                role = "Student";
            else if (dynamic_cast<Faculty*>(u))
                role = "Faculty";
            else if (dynamic_cast<Librarian*>(u))
                role = "Librarian";
            usersFile << role << "|" << u->getName() << "|" << u->getId() << "|"
                      << u->getMaxBorrowed() << "|" << u->getMaxPeriod() << "|" 
                      << u->getFineRate() << "|" << u->calculateFine();
            const vector<Book*>& bb = u->account->getBorrowedBooks();
            for (Book* b : bb) {
                usersFile << "|" << b->getISBN();
            }
            usersFile << "\n";
        }
        usersFile.close();
    }
}

void Library::loadState() {
    ifstream booksFile("books.txt");
    if (booksFile.is_open()) {
        string line;
        if(getline(booksFile, line))
            currentDay = stoi(line);
        while (getline(booksFile, line)) {
            istringstream iss(line);
            vector<string> tokens;
            string token;
            while(getline(iss, token, '|'))
                tokens.push_back(token);
            if (tokens.size() >= 7) {
                Book* b = new Book(tokens[0], tokens[1], tokens[2], stoi(tokens[3]), tokens[4]);
                b->setStatus(tokens[5]);
                b->setDueDay(stoi(tokens[6]));
                books.push_back(b);
            }
        }
        booksFile.close();
    }
    ifstream usersFile("users.txt");
    if (usersFile.is_open()) {
        string line;
        while (getline(usersFile, line)) {
            istringstream iss(line);
            vector<string> tokens;
            string token;
            while(getline(iss, token, '|'))
                tokens.push_back(token);
            if(tokens.size() >= 7) {
                User* user = nullptr;
                if(tokens[0] == "Student")
                    user = new Student(tokens[1], tokens[2]);
                else if(tokens[0] == "Faculty")
                    user = new Faculty(tokens[1], tokens[2]);
                else if(tokens[0] == "Librarian")
                    user = new Librarian(tokens[1], tokens[2]);
                if(user != nullptr) {
                    user->account->payFines(); // Reset fines
                    for (size_t i = 7; i < tokens.size(); i++) {
                        Book* b = searchBook(tokens[i]);
                        if (b != nullptr)
                            user->account->addBorrowedBook(b);
                    }
                    addUser(user);
                }
            }
        }
        usersFile.close();
    }
}
