#include "bookcollection.h"
#include <iostream>

//addBook function
void BookCollection::addBook(const Book& book) {
        books.push_back(book);
    std::cout << "Book added successfully!" << std::endl;
}

//editBook function
void BookCollection::editBook() {
    std::string bookISBN;
    std::cout << "Enter book ISBN to edit: ";
    std::cin >> bookISBN;
    std::cin.ignore();

    // Check if the book exists
    for (Book& book : books) {
        if (book.getISBN() == bookISBN) {
            std::string newTitle, newAuthor, newStatus;
            double newCost;

            std::cout << "Enter updated title: ";
            //std::cin.ignore();
            std::getline(std::cin, newTitle);
            //std::cin >> newTitle;
            std::cout << "Enter updated author: ";
            //std::cin >> newAuthor;
            //std::cin.ignore();
            std::getline(std::cin, newAuthor);
            std::cout << "Enter updated cost: ";
            std::cin >> newCost;
            std::cout << "Enter updated status: ";
            std::cin >> newStatus;

            // Update the book with the new information
            book.setTitle(newTitle);
            book.setAuthor(newAuthor);
            book.setCost(newCost);
            book.setStatus(newStatus);

            std::cout << "Book with ISBN " << bookISBN << " updated successfully!" << std::endl;
            return;
        }
    }
    std::cout << "Book with ISBN " << bookISBN << " not found." << std::endl;
}

//deleteBook function
void BookCollection::deleteBook(std::string ISBN) {
    for (auto iter = books.begin(); iter != books.end(); iter++) {
        if (iter->getISBN() == ISBN) {
            books.erase(iter);
            std::cout << "Book with Book ISBN " << ISBN << " deleted successfully!" << std::endl;
            return;
        }
    }
    std::cout << "Book with Book ISBN " << ISBN << " not found." << std::endl;
}

// Implementation of findBook function
Book* BookCollection::findBook(std::string ISBN) {
    for (Book& book : books) {
        if (book.getISBN() == ISBN) {
            std::cout << "Book with ISBN " << ISBN << " found." << std::endl;
            return &book;
        }
    }
    std::cout << "Book with ISBN " << ISBN << " not found." << std::endl;
    return nullptr;
}

//printAllBooks function
void BookCollection::printAllBooks() const {
    if (books.empty()) {
        std::cout << "No books in the collection." << std::endl;
        return;
    }
    std::cout << "Printing all books:" << std::endl;
    for (const Book& book : books) {
        std::cout << "Title: " << book.getTitle() << ", Author: " << book.getAuthor() << std::endl;
    }
}

//printBookDetails function
void BookCollection::printBookDetails(std::string ISBN) const {
    for (const Book& book : books) {
        //find book
        if (book.getISBN() == ISBN) {
            std::cout << "Title: " << book.getTitle() << std::endl;
            std::cout << "Author: " << book.getAuthor() << std::endl;
            std::cout << "ISBN: " << book.getISBN() << std::endl;
            std::cout << "Cost: " << book.getCost() << std::endl;
            std::cout << "Status: " << book.getStatus() << std::endl;
            return;
        }
    }
    std::cout << "Book with Book ISBN " << ISBN << " not found." << std::endl;
}
