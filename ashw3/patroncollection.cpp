
#include "patroncollection.h"
#include <iostream>
#include "loan.h"

//addpatron function
void PatronCollection::addPatron(const Patron& patron) {
    patrons.push_back(patron);
}

//editpatron function
void PatronCollection::editPatron() {
    int patronID;
    std::cout << "Enter patron ID to edit: ";
    std::cin >> patronID;
    std::cin.ignore();

    for (Patron& patron : patrons) {
        if (patron.getID() == patronID) {
            std::string newName;
            double newFineBalance;
            int newNumBooksOut;

            std::cout << "Enter updated name: ";
            std::getline(std::cin, newName);

            std::cout << "Enter updated fine balance: ";
            std::cin >> newFineBalance;

            std::cout << "Enter updated number of books checked out: ";
            std::cin >> newNumBooksOut;

            // Update the patron with the new information
            patron.setName(newName);
            patron.setFineBalance(newFineBalance);
            patron.setNumBooksOut(newNumBooksOut);

            std::cout << "Patron with ID " << patronID << " updated successfully!" << std::endl;
            return;
        }
    }
    std::cout << "Patron with ID " << patronID << " not found." << std::endl;
}
//deletepatron function
void PatronCollection::deletePatron(int id) {
    for (auto it = patrons.begin(); it != patrons.end(); it++) {
        if (it->getID() == id) {
            patrons.erase(it);
            std::cout << "Patron with ID " << id << " deleted successfully." << std::endl;
            return; 
        }
    }
    std::cout << "Patron with ID " << id << " not found." << std::endl;
}

//findpatron function
Patron* PatronCollection::findPatron(int id) {
    for (Patron& patron : patrons) {
        if (patron.getID() == id) {
            std::cout << "Patron with ID " << id << " found." << std::endl;
            return &patron;
        }
    }
    std::cout << "Patron with ID " << id << " not found." << std::endl;
    return nullptr;
}

//printallpatrons function
void PatronCollection::printAllPatrons() const {
    for (const auto& patron : patrons) {
        std::cout << "Name: " << patron.getName() << ", ID: " << patron.getID() << std::endl;
    }
}

//printpatrondetails function
void PatronCollection::printPatronDetails(int id) const {
    for (const auto& patron : patrons) {
        //find patron
        if (patron.getID() == id) {
            std::cout << "Patron details:" << std::endl;
            std::cout << "Name: " << patron.getName() << std::endl;
            std::cout << "ID: " << patron.getID() << std::endl;
            std::cout << "Fine Balance: $" << patron.getFineBalance() << std::endl;
            std::cout << "Number of books out: " << patron.getNumBooksOut() << std::endl;
            return;
        }
    }
    std::cout << "Patron with ID " << id << " not found." << std::endl;
}

//payfines function
void PatronCollection::payFines(int patronID) {
    for (Patron& patron : patrons) {
        //find patron
        if (patron.getID() == patronID) {
            double finesPaid = patron.getFineBalance();
            patron.payFines(finesPaid);
            std::cout << "Fine of $" << finesPaid << " successfully paid off for patron with ID: " << patronID << std::endl;
            return;
        }
    }
    std::cout << "Patron with ID " << patronID << " not found." << std::endl;
}

//getfinebalance function

double PatronCollection::getFineBalance(int patronID) const {
    for (const Patron& patron : patrons) {
        // Find patron by ID
        if (patron.getID() == patronID) {
            return patron.getFineBalance();
        }
    }
    // Print message if patron not found
    std::cout << "Patron with ID " << patronID << " not found." << std::endl;
    return 0.0;
}
