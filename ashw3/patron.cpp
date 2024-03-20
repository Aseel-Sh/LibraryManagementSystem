
#include "patron.h"

Patron::Patron(){
    name = "";
    id = 0;
    fineBalance = 0.0;
    numBooksOut = 0;  
}

Patron::Patron(const std::string& name, int id, double fineBalance, int numBooksOut) {
    this->name = name;
    this->id = id;
    this->fineBalance = fineBalance;
    this->numBooksOut = numBooksOut;
}

std::string Patron::getName() const {
    return name;
}

int Patron::getID() const {
    return id;
}

double Patron::getFineBalance() const {
    return fineBalance;
}

void Patron::setName(std::string name){
    this->name = name;
}

int Patron::getNumBooksOut() const {
    return numBooksOut;
}

void Patron::setFineBalance(double fineBalance) {
    this->fineBalance = fineBalance;
}

void Patron::setNumBooksOut(int numBooksOut) {
    this->numBooksOut = numBooksOut;
}

void Patron::payFines(double amount) {
    fineBalance -= amount;
}

void Patron::incrementNumBooksOut() {
    numBooksOut++;
}

void Patron::decrementNumBooksOut(){
    numBooksOut--;
}