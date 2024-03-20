#ifndef LOAN_H
#define LOAN_H

#include <string>
#include <ctime>

class Loan {
private:
    // Static member to generate unique loan IDs
    static int nextLoanID; 
    int loanID;
    std::string ISBN;
    int patronID;
    std::time_t dueDateTime;
    std::string status;
    std::time_t checkoutDateTime;
    int numRechecks;

public:
    Loan();
    Loan(std::string ISBN, int patronID, std::time_t checkoutDateTime);

    // Accessors
    int getLoanID() const;
    std::string getISBN() const;
    int getPatronID() const;
    std::time_t getDueDateTime() const;
    std::string getStatus() const;
    std::time_t getCheckoutDateTime() const;
    int getNumRechecks() const;

    // Mutators
    void setStatus(const std::string& status);
    void setDueDateTime(std::time_t dueDateTime);
    void setNumRechecks(int numRechecks);
    void calculateDueDate();
    void incrementNumRechecks();
    //void validate() const;
    static int generateUniqueLoanID();
};

#endif