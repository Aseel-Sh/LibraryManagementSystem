#include "loan.h"
#include <iostream>

// Initialize the static member variable
int Loan::nextLoanID = 1;

Loan::Loan(){
    loanID = 0;
    ISBN = "";
    patronID = 0;
    dueDateTime = 0;
    status = "";
    checkoutDateTime = 0;
    numRechecks = 0;
}

Loan::Loan(std::string ISBN, int patronID, std::time_t checkoutDateTime) {
    this->loanID = generateUniqueLoanID();
    this->ISBN = ISBN;
    this->patronID = patronID;
    this->checkoutDateTime = checkoutDateTime;
    this->status = "Checked Out";
    this->numRechecks = 0;

    calculateDueDate();
}


int Loan::getLoanID() const {
    return loanID;
}

std::string Loan::getISBN() const {
    return ISBN;
}

int Loan::getPatronID() const {
    return patronID;
}

std::time_t Loan::getDueDateTime() const {
    return dueDateTime;
}

std::string Loan::getStatus() const {
    return status;
}

std::time_t Loan::getCheckoutDateTime() const {
    return checkoutDateTime;
}

int Loan::getNumRechecks() const {
    return numRechecks;
}

void Loan::setStatus(const std::string& status) {
    this->status = status;
}

void Loan::setDueDateTime(std::time_t dueDateTime) {
    this->dueDateTime = dueDateTime;
}

void Loan::setNumRechecks(int numRechecks) {
    this->numRechecks = numRechecks;
}

void Loan::calculateDueDate() {
    //10 days in secs + checkouttime
    dueDateTime = checkoutDateTime + (10 * 24 * 60 * 60); 
}

void Loan::incrementNumRechecks() {
    numRechecks++;
}

// void Loan::validate() const {
//     //check if the book is overdue
//     std::time_t currentTime = std::time(nullptr);
//     if (status == "Checked Out" && dueDateTime < currentTime) {
//         std::cout << "Warning: Book with loan ID " << loanID << " is overdue!" << std::endl;
//     }

// }

int Loan::generateUniqueLoanID() {
    return nextLoanID++;
}