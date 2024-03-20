
#ifndef PATRON_H
#define PATRON_H

#include <string>

class Patron {
private:
    std::string name;
    int id;
    double fineBalance;
    int numBooksOut;

public:
    Patron();
    Patron(const std::string& name, int id, double fineBalance, int numBooksOut);

    // Accessors
    std::string getName() const;
    int getID() const;
    double getFineBalance() const;
    int getNumBooksOut() const;

    // Mutators
    void setName(std::string name);
    void setFineBalance(double fineBalance);
    void setNumBooksOut(int numBooksOut);
    void payFines(double amount);
    void incrementNumBooksOut();
    void decrementNumBooksOut();
};

#endif
