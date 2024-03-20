#include "loancollection.h"
#include "book.h"
#include "patron.h"
#include <iostream>
#include <cmath>
#include <cctype>

//addloan function
void LoanCollection::addLoan(const Loan& loan) {
    loans.push_back(loan);
}

//deleteloan function
void LoanCollection::deleteLoan(int loanID) {
    for (size_t i = 0; i < loans.size(); i++) {
        // find loan
        if (loans[i].getLoanID() == loanID) {
            // erase the loan at index i
            loans.erase(loans.begin() + i);
            std::cout << "Loan: " << loanID << " deleted successfully!" << std::endl;
            return;
        }
    }
    std::cout << "Loan with ID " << loanID << " not found." << std::endl;
}

//Findloan function
Loan* LoanCollection::findLoan(int loanID) const {
    //using normal for loop cuz const auto didnt work due to some const issues
    for (size_t i = 0; i < loans.size(); i++) {
        //find loanid
        if (loans[i].getLoanID() == loanID) {
            std::cout << "Loan with ID " << loanID << " found." << std::endl;
            //returning &loan does not work, google suggested using const_cast. it worked
            return const_cast<Loan*>(&loans[i]);
        }
    }
    std::cout << "Loan with ID " << loanID << " not found." << std::endl;
    return nullptr;
}


// Printallloans function
void LoanCollection::printAllLoans() const {
    for (const auto& loan : loans) {
        std::cout << "Loan ID: " << loan.getLoanID() << ", Book ISBN: " << loan.getISBN() << ", Patron ID: " << loan.getPatronID() << std::endl;
    }
}

//checkoutbook function
void LoanCollection::checkOutBook(std::string ISBN, int patronID, BookCollection& books, PatronCollection& patrons) {
    //pointer to the book object
    Book* bookPtr = books.findBook(ISBN); 
    if (bookPtr == nullptr) {
        return;
    }
    // Dereference the pointer to access the book object
    Book& book = *bookPtr; 
    
    //pointer to the patron object
    Patron* patronPtr = patrons.findPatron(patronID);
    if (patronPtr == nullptr) {
        return;
    }
    // Dereference the pointer to access the patron object
    Patron& patron = *patronPtr;

    //checking if it meets conditions
    if (patron.getNumBooksOut() >= 6) {
        std::cout << "Cannot check out more than 6 books." << std::endl;
        return;
    }
    
    if (patron.getFineBalance() > 0) {
        std::cout << "Patron has outstanding fines. Please clear them before checking out a book." << std::endl;
        return;
    }

    // check status before allowing to checkout
    std::string status = book.getStatus();

    //didnt want it to be case senstive so converted string to lowercase before checking
    for (char& c : status) {
        c = std::tolower(c);
    }

    // continue checking if available
    if (status == "out" || status == "repair" || status == "lost") {
        std::cout << "Book is currently " << status << " and not available for checkout." << std::endl;
        return;
    }

    //Creating a new loan
    Loan loan(ISBN, patronID, std::time(nullptr));

    //update status
    book.setStatus("Out");

    //Update patron's books out count
    patron.incrementNumBooksOut();

    //Add the loan to the vector
    addLoan(loan);

    int loanID = loan.getLoanID();
    std::cout << "Book with ID " << ISBN << " checked out to Patron with ID " << patronID << ". Loan ID: " << loanID << std::endl;
}

// Checkinbook function
void LoanCollection::checkInBook(int loanID, int patronID, BookCollection& books, PatronCollection& patrons) {
    //ptr to object
    Loan* loanPtr = findLoan(loanID);
    //checking if it exists
    if (loanPtr == nullptr) {
        std::cout << "Loan with ID " << loanID << " not found." << std::endl;
        return;
    }
    //Dereference the ptr to access the object
    Loan& loan = *loanPtr;

    //check if the loan id given belongs to the patron id given
    if (loan.getPatronID() != patronID) {
        std::cout << "Loan with ID " << loanID << " does not belong to Patron with ID " << patronID << "." << std::endl;
        return;
    }

    Book* bookPtr = books.findBook(loan.getISBN()); 
    if (bookPtr == nullptr) {
        std::cout << "Book associated with loan not found." << std::endl;
        return;
    }
    Book& book = *bookPtr;

    //if book found then change status to in
    book.setStatus("In");

    
    Patron* patronPtr = patrons.findPatron(patronID);
    if (patronPtr == nullptr) {
        return;
    }
    Patron& patron = *patronPtr;

    //if patron found and book found then decrement numbooks out
    patron.decrementNumBooksOut();

    //Calculate fines if book is overdue
    std::time_t currentTime = std::time(nullptr);
    std::time_t dueDateTime = loan.getDueDateTime();
    if (dueDateTime < currentTime) {
        double fine = calculateFine(dueDateTime, currentTime);
        patron.setFineBalance(patron.getFineBalance() + fine);
    }

    deleteLoan(loanID);
    std::cout << "Book checked in successfully." << std::endl;
}

//printOverdueBooks function
void LoanCollection::printOverdueBooks() const {
    std::cout << "Overdue Books:" << std::endl;
    //to track if any overdue books are found
    bool foundOverdue = false; 
    for (const Loan& loan : loans) {
        std::string status = loan.getStatus();
        // Convert status to lowercase
        for (char& c : status) {
            c = std::tolower(c);
        }
        if (status == "overdue") {
            std::cout << "Loan ID: " << loan.getLoanID() << ", Book ISBN: " << loan.getISBN() 
                      << ", Patron ID: " << loan.getPatronID() << std::endl;
            //make true if at least one overdue book is found
            foundOverdue = true; 
        }
    }
    if (!foundOverdue) {
        std::cout << "No overdue books found." << std::endl;
    }
}

//listBooksForPatron func
void LoanCollection::listBooksForPatron(int patronID, BookCollection& books) const{
    std::cout << "Books for Patron with ID " << patronID << ":" << std::endl;
    //to track if patron has books borrowed
    bool foundBooks = false;
    for (const Loan& loan : loans) {
        if (loan.getPatronID() == patronID) {
            Book* bookPtr = books.findBook(loan.getISBN());
            if (bookPtr != nullptr) {
                Book& book = *bookPtr;
                std::cout << "Loan ID: " << loan.getLoanID() << ", Book ISBN: " << book.getISBN() << std::endl;
                //if atleast one book found then make true
                foundBooks = true;
            }
        }
    }
    if (!foundBooks) {
        std::cout << "No books found for Patron with ID " << patronID << "." << std::endl;
    }
}

//updateLoanStatus(e.g., normal or overdue) function
void LoanCollection::updateLoanStatus() {
    std::time_t currentTime = std::time(nullptr);
    for (Loan& loan : loans) {
        if (loan.getStatus() == "Checked Out" && loan.getDueDateTime() < currentTime) {
            loan.setStatus("Overdue");
        } else if (loan.getStatus() == "Checked Out" && loan.getDueDateTime() >= currentTime) {
            loan.setStatus("Normal");
        }
    }
}

//Recheckbook function (extend due date)
void LoanCollection::recheckBook(int loanID) {
    //ptr to obj
    Loan* loanPtr = findLoan(loanID);
    if (loanPtr == nullptr) {
        return;
    }
    //deref
    Loan& loan = *loanPtr;
    
    //Check if the number of rechecks has reached the maximum allowed
    if (loan.getNumRechecks() >= 1) {
        std::cout << "Maximum number of rechecks reached for loan with ID " << loanID << "." << std::endl;
        return;
    }

    //Update the due date by adding 10 days
    std::time_t currentDueDate = loan.getDueDateTime();
    std::time_t newDueDate = currentDueDate + (10 * 24 * 60 * 60); // 10 days in seconds

    //Increment the number of rechecks
    loan.incrementNumRechecks();

    //Update the loan's due date
    loan.setDueDateTime(newDueDate);

    int daysLeft = daysUntilDueDate(loanID);
    int hoursLeft = hoursUntilDueDate(loanID);

    if (daysLeft != -1) {
        std::cout << "Book with loan ID " << loanID << " rechecked successfully. Days left until due date: " << daysLeft << " days and " << hoursLeft << " hours." << std::endl;
    } else {
        std::cout << "Book with loan ID " << loanID << " rechecked successfully. Due date: (past due)" << std::endl;
    }
}

//reportLost function and update patron's fine balance
void LoanCollection::reportLost(int loanID, BookCollection& books, PatronCollection& patrons) {
    //find loan
    Loan* loanPtr = findLoan(loanID);
    if (loanPtr == nullptr) {
        std::cout << "Loan with ID " << loanID << " not found." << std::endl;
        return;
    }
    Loan& loan = *loanPtr;

    //find book
    Book* bookPtr = books.findBook(loan.getISBN());
    if (bookPtr == nullptr) {
        std::cout << "Book associated with loan not found." << std::endl;
        return;
    }
    Book& book = *bookPtr;

    //find patron
    Patron* patronPtr = patrons.findPatron(loan.getPatronID());
    if (patronPtr == nullptr) {
        std::cout << "Patron associated with loan not found." << std::endl;
        return;
    }
    Patron& patron = *patronPtr;

    //Update patron's fine balance with the cost of the lost book
    double bookCost = book.getCost();
    patron.setFineBalance(patron.getFineBalance() + bookCost);

    //update the book's status as "Lost"
    book.setStatus("Lost");

    std::cout << "Book reported as lost. Patron's fine balance updated." << std::endl;
}

//daysUntilDueDate func
int LoanCollection::daysUntilDueDate(int loanID) const {
    //find loan
    Loan* loanPtr = findLoan(loanID);
    if (loanPtr == nullptr) {
        std::cout << "Loan with ID " << loanID << " not found." << std::endl;
        return -1;
    }

    Loan& loan = *loanPtr;

    //find time diff btwn due date and current time
    std::time_t currentTime = std::time(nullptr);
    std::time_t dueDateTime = loan.getDueDateTime();
    std::time_t timeDifference = dueDateTime - currentTime;

    // Calculate as days (originally as secs)
    int daysLeft = timeDifference / (60 * 60 * 24);

    return daysLeft;
}

//hoursUntilDueDate function
int LoanCollection::hoursUntilDueDate(int loanID) const {
    // Find loan
    Loan* loanPtr = findLoan(loanID);
    if (loanPtr == nullptr) {
        std::cout << "Loan with ID " << loanID << " not found." << std::endl;
        return -1;
    }

    Loan& loan = *loanPtr;
    
    // Get time difference
    std::time_t currentTime = std::time(nullptr);
    std::time_t dueDateTime = loan.getDueDateTime();
    std::time_t timeDifference = dueDateTime - currentTime;

    // Convert the seconds to hours
    int remainingHours = timeDifference / (60 * 60);

    // Calculate remaining days
    int remainingDays = timeDifference / (60 * 60 * 24);

    // Calculate remaining hours after subtracting complete days
    int remainingHoursAfterDays = remainingHours - (remainingDays * 24);

    return remainingHoursAfterDays;
}
int LoanCollection::minutesUntilDueDate(int loanID) const {
    // Find the loan
    Loan* loanPtr = findLoan(loanID);
    if (loanPtr == nullptr) {
        std::cout << "Loan with ID " << loanID << " not found." << std::endl;
        return -1;
    }

    Loan& loan = *loanPtr;
    
    // Get the time difference in seconds
    std::time_t currentTime = std::time(nullptr);
    std::time_t dueDateTime = loan.getDueDateTime();
    std::time_t timeDifference = dueDateTime - currentTime;

    // Convert the seconds to minutes
    int remainingMinutes = timeDifference / 60;

    // Calculate remaining hours
    int remainingHours = remainingMinutes / 60;

    // Calculate remaining days
    int remainingDays = remainingHours / 24;

    // Calculate remaining minutes after subtracting complete days and hours
    int remainingMinutesAfterHours = remainingMinutes - (remainingHours * 60);

    return remainingMinutesAfterHours;
}

//calculateFine function
double LoanCollection::calculateFine(std::time_t dueDateTime, std::time_t currentTime) const {
    // Fine rate per day ($0.25)
    const double fineRatePerDay = 0.25;
    // Number of seconds in a day
    const double secondsInDay = 24 * 60 * 60;

    //get the diff
    double daysLate = (currentTime - dueDateTime) / secondsInDay;

    //Round up to the nearest whole day
    daysLate = std::ceil(daysLate);

    //Calculate the fine based on the number of days late
    double fine = fineRatePerDay * daysLate;

    return fine;
}