#ifndef PATRONCOLLECTION_H
#define PATRONCOLLECTION_H

#include <vector>
#include "patron.h"
#include "loan.h"

class PatronCollection {
private:
    std::vector<Patron> patrons;

public:
    void addPatron(const Patron& patron);
    void editPatron();
    void deletePatron(int id);
    Patron* findPatron(int id);
    void printAllPatrons() const;
    void printPatronDetails(int id) const;
    void payFines(int patronID);
    double getFineBalance(int patronID) const;

};

#endif


