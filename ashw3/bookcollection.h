#ifndef BOOKCOLLECTION_H
#define BOOKCOLLECTION_H

#include <vector>
#include "book.h"

class BookCollection {
private:
    std::vector<Book> books;

public:
    void addBook(const Book& book);
    void editBook();
    void deleteBook(std::string ISBN);
    Book* findBook(std::string ISBN);
    void printAllBooks() const;
    void printBookDetails(std::string ISBN) const;
};

#endif
