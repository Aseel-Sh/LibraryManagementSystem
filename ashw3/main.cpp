/*
Name: Aseel shaheen
Course: CSCE 1040.501
Hw: Hwk3
*/

#include <iostream>
#include <iomanip>
#include <string>
#include "patroncollection.h"
#include "bookcollection.h"
#include "loancollection.h"

void printMenu() {
    std::cout << std::endl << "Library Management System Menu:" << std::endl;
    std::cout << "1. Access Patrons" << std::endl;
    std::cout << "2. Access Books" << std::endl;
    std::cout << "3. Access Loans" << std::endl;
    std::cout << "4. Exit" << std::endl;
}

void patronMenu() {
    std::cout << "Patron Menu:" << std::endl;
    std::cout << "1. Add Patron" << std::endl;
    std::cout << "2. Edit Patron" << std::endl;
    std::cout << "3. Delete Patron" << std::endl;
    std::cout << "4. Find Patron" << std::endl;
    std::cout << "5. Print All Patrons" << std::endl;
    std::cout << "6. Print Patron Details" << std::endl;
    std::cout << "7. Pay Fines" << std::endl;
    std::cout << "8. Show Fine Balance" << std::endl;
    std::cout << "9. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

void bookMenu() {
    std::cout << "Book Menu:" << std::endl;
    std::cout << "1. Add Book" << std::endl;
    std::cout << "2. Edit Book" << std::endl;
    std::cout << "3. Delete Book" << std::endl;
    std::cout << "4. Find Book" << std::endl;
    std::cout << "5. Print All Books" << std::endl;
    std::cout << "6. Print Book Details" << std::endl;
    std::cout << "7. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

void loanMenu() {
    std::cout << "Loan Menu:" << std::endl;
    std::cout << "1. Check Out Book" << std::endl;
    std::cout << "2. Check In Book" << std::endl;
    std::cout << "3. List Overdue Books" << std::endl;
    std::cout << "4. List Books for Patron" << std::endl;
    std::cout << "5. Re-Check a Book" << std::endl;
    std::cout << "6. Report Lost Book" << std::endl;
    std::cout << "7. Days until due date" << std::endl;
    std::cout << "8. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

void handleMenuChoice(int choice, PatronCollection& patrons, BookCollection& books, LoanCollection& loans) {
    switch (choice) {
        case 1: {
            int patronChoice;
            do {
                patronMenu();
                std::cin >> patronChoice;
                std::cin.ignore();
                switch (patronChoice) {
                    case 1: {
                        std::string name;
                        int id;
                        double fineBalance;
                        int numBooksOut;
                        
                        std::cout << "Enter patron name: ";
                        //std::cin.ignore();
                        std::getline(std::cin, name);
                        //std::cin >> name;

                        std::cout << "Enter patron ID: ";
                        std::cin >> id;
                        std::cin.ignore();
                        
                        // Validation for the number of books checked out
                        std::cout << "Enter number of books checked out (not greater than 6): ";
                        do {
                            std::cin >> numBooksOut;
                            if (numBooksOut <= 6) {
                                break;  // If the input is valid, exit the loop
                            } else {
                                std::cout << "Invalid input! Number of books checked out must not be greater than 6. Try again: ";
                            }
                        } while (true);

                        std::cout << "Enter fine balance: ";
                        std::cin >> fineBalance;

                        std::cin.ignore();

                        // Create patron and add to collection
                        Patron newPatron(name, id, fineBalance, numBooksOut);
                        patrons.addPatron(newPatron);
                        break;
                    }
                    case 2: {
                        patrons.editPatron();
                        break;
                    }
                    case 3: {
                        int patronIDToDelete;
                        std::cout << "Enter patron ID to delete: ";
                        std::cin >> patronIDToDelete;
                        patrons.deletePatron(patronIDToDelete);
                        break;
                    }
                    case 4: {
                        int patronIDToFind;
                        std::cout << "Enter patron ID to find: ";
                        std::cin >> patronIDToFind;
                        Patron* foundPatronPtr = patrons.findPatron(patronIDToFind);
                        if (foundPatronPtr != nullptr) {
                            Patron& foundPatron = *foundPatronPtr;
                        }
                        break;
                    }
                    case 5: {
                        patrons.printAllPatrons();
                        break;
                    }
                    case 6: {
                        int patronIDToPrintDetails;
                        std::cout << "Enter patron ID to print details: ";
                        std::cin >> patronIDToPrintDetails;
                        patrons.printPatronDetails(patronIDToPrintDetails);
                        break;
                    }
                    case 7: {
                        int patronIDToPay;
                        std::cout << "Enter patron ID to pay fines: ";
                        std::cin >> patronIDToPay;
                        patrons.payFines(patronIDToPay);
                        break;
                    }
                    case 8: {
                        int patronID;
                        std::cout << "Enter patron ID to check fine balance: ";
                        std::cin >> patronID;
                        std::cin.ignore();
                        double fineBalance = patrons.getFineBalance(patronID);
                        if (fineBalance != 0.0) {
                            std::cout << "Fine balance for patron with ID " << patronID << " is: $" << fineBalance << std::endl;
                        }
                        break;
                    }
                    case 9:
                        break;
                    default:
                        std::cout << "Invalid choice. Please try again." << std::endl;
                }
            } while (patronChoice != 9);
            break;
        }
        case 2: {
            int bookChoice;
            do {
                bookMenu();
                std::cin >> bookChoice;
                std::cin.ignore();
                switch (bookChoice) {
                    case 1: {
                        std::string author, title, isbn, status;
                        double cost;
                        
                        std::cout << "Enter author: ";
                        std::getline(std::cin, author);
                        //std::cin >> author;
                        std::cout << "Enter title: ";
                        std::getline(std::cin, title);
                        std::cout << "Enter ISBN: ";
                        std::cin >> isbn;
                        std::cout << "Enter cost: ";
                        std::cin >> cost;
                        std::cout << "Enter status(In, Out, Repair, Lost): ";
                        std::cin >> status;
                        
                        Book newBook(author, title, isbn, cost, status);
                        books.addBook(newBook);
                        break;
                    }
                    case 2: {
                        books.editBook();
                        break;
                    }
                    case 3: {
                        std::string bookIDToDelete;
                        std::cout << "Enter book ISBN to delete: ";
                        std::cin >> bookIDToDelete;
                        books.deleteBook(bookIDToDelete);
                        break;
                    }
                    case 4: {
                        std::string bookIDToFind;
                        std::cout << "Enter book ISBN to find: ";
                        std::cin >> bookIDToFind;
                        Book* foundBookPtr = books.findBook(bookIDToFind);
                        if (foundBookPtr != nullptr) {
                            Book& foundBook = *foundBookPtr;
                        }
                        break;
                    }
                    case 5: {
                        books.printAllBooks();
                        break;
                    }
                    case 6: {
                        std::string bookIDToPrintDetails;
                        std::cout << "Enter book ISBN to print details: ";
                        std::cin >> bookIDToPrintDetails;
                        books.printBookDetails(bookIDToPrintDetails);
                        break;
                    }
                    case 7:
                        break;
                    default:
                        std::cout << "Invalid choice. Please try again." << std::endl;
                }
            } while (bookChoice != 7);
            break;
        }
        case 3: {
            int loanChoice;
            do {
                loanMenu();
                std::cin >> loanChoice;
                std::cin.ignore();
                switch (loanChoice) {
                    case 1: {
                        std::string bookIDToCheckOut;
                        int patronID;
                        std::cout << "Enter book ISBN to check out: ";
                        std::cin >> bookIDToCheckOut;
                        std::cout << "Enter patron ID: ";
                        std::cin >> patronID;
                        loans.checkOutBook(bookIDToCheckOut, patronID, books, patrons);
                        break;
                    }
                    case 2: {
                        int loanIDToCheckIn, patronID;
                        std::cout << "Enter loan ID to check in: ";
                        std::cin >> loanIDToCheckIn;
                        std::cout << "Enter patron ID: ";
                        std::cin >> patronID;
                        loans.checkInBook(loanIDToCheckIn, patronID, books, patrons);
                        break;
                    }
                    case 3: {
                        loans.printOverdueBooks();
                        break;
                    }
                    case 4: {
                        int patronIDForBooks;
                        std::cout << "Enter patron ID to list books: ";
                        std::cin >> patronIDForBooks;
                        loans.listBooksForPatron(patronIDForBooks, books);
                        break;
                    }
                    case 5: {
                        int loanIDToRecheck;
                        std::cout << "Enter loan ID to recheck: ";
                        std::cin >> loanIDToRecheck;
                        loans.recheckBook(loanIDToRecheck);
                        break;
                    }
                    case 6: {
                        int loanIDToReportLost;
                        std::cout << "Enter loan ID to report lost: ";
                        std::cin >> loanIDToReportLost;
                        loans.reportLost(loanIDToReportLost, books, patrons);
                        break;
                    }
                    case 7: {
                        int loanID;
                        std::cout << "Enter loan ID to check days left: ";
                        std::cin >> loanID;
                        int daysLeft = loans.daysUntilDueDate(loanID);
                        int hoursLeft = loans.hoursUntilDueDate(loanID);
                        int minsLeft = loans.minutesUntilDueDate(loanID);

                        if (daysLeft != -1) {
                            std::cout << "Days left until due date: " << daysLeft << " days, " << hoursLeft << " hours, and " << minsLeft << " minutes." << std::endl;
                        } else {
                            std::cout << "Loan not found or due date has passed." << std::endl;
                        }
                        break;
                    }
                    case 8: {
                        break;
                    }
                    default:
                        std::cout << "Invalid choice. Please try again." << std::endl;
                }
            } while (loanChoice != 8);
            break;
        }
        case 4:
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
    }
}


int main() {
    PatronCollection patrons;
    BookCollection books;
    LoanCollection loans;

    int choice;
    do {
        printMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        handleMenuChoice(choice, patrons, books, loans);

    } while (choice != 4);

    return 0;
}
