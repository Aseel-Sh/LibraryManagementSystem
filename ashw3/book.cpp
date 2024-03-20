#include "book.h"

Book::Book()
{
author = "";
title = "";
isbn = "";
cost= 0.0;
status = "";
}

Book::Book(const std::string &author, const std::string &title, const std::string &isbn, double cost, const std::string &status)
{
    this->author = author;
    this->title = title;
    this->isbn = isbn;
    this->cost = cost;
    this->status = status;
}

std::string Book::getAuthor() const
{
    return author;
}

std::string Book::getTitle() const
{
    return title;
}

std::string Book::getISBN() const
{
    return isbn;
}


double Book::getCost() const
{
    return cost;
}

std::string Book::getStatus() const
{
    return status;
}

void Book::setAuthor(std::string author){
    this->author = author;
}

void Book::setTitle(std::string title){
    this->title = title;
}

void Book::setCost(double cost){
    this->cost = cost;
}

void Book::setISBN(std::string isbn){
    this->isbn = isbn;
}

void Book::setStatus(const std::string &status)
{
    this->status = status;
}
