#ifndef LOANCOLLECTION_H
#define LOANCOLLECTION_H

#include <vector>
#include "loan.h"
#include "bookcollection.h"
#include "patroncollection.h"

class LoanCollection {
private:
    std::vector<Loan> loans;

public:
    void addLoan(const Loan& loan);
    void deleteLoan(int loanID);
    Loan* findLoan(int loanID) const;
    void printAllLoans() const;
    void checkOutBook(std::string ISBN, int patronID, BookCollection& books, PatronCollection& patrons);
    void checkInBook(int LoanID, int patronID, BookCollection& books, PatronCollection& patrons);
    void printOverdueBooks() const;
    void listBooksForPatron(int patronID, BookCollection& books) const;
    void updateLoanStatus();
    void recheckBook(int loanID);
    void reportLost(int loanID, BookCollection& bookCollection, PatronCollection& patronCollection);
    int daysUntilDueDate(int loanID) const;
    int hoursUntilDueDate(int loanID) const;
    int minutesUntilDueDate(int loanID) const;
    double calculateFine(std::time_t dueDateTime, std::time_t currentTime) const;
};

#endif

