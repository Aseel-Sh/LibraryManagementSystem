

#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book {
private:
    std::string author;
    std::string title;
    std::string isbn;
    double cost;
    std::string status;

public:
    Book();
    Book(const std::string& author, const std::string& title, const std::string& isbn, double cost, const std::string& status);

    // Accessors
    std::string getAuthor() const;
    std::string getTitle() const;
    std::string getISBN() const;
    double getCost() const;
    std::string getStatus() const;

    // Mutators
    void setAuthor(std::string author);
    void setTitle(std::string title);
    void setCost(double cost);
    void setISBN(std::string isbn);
    void setStatus(const std::string& status);
};

#endif