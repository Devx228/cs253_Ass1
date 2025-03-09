#ifndef MENU_H
#define MENU_H

#include "Library.h"
#include "User.h"
using namespace std;

void newRegistration(Library &library);
void userMenu(Library &library, User* user);
void librarianMenu(Library &library, Librarian* librarian);

#endif
