// Customer.cpp
#include <sstream>
#include <vector>
#include "Customer.h"

using std::ostringstream;
using std::vector;

using namespace std;

double Customer::calculateAmount(Rental rental){
    double amount = 0;

    switch ( rental.getMovie().getPriceCode() ) {
        case Movie::REGULAR:
            amount+= 2;
            if ( rental.getDaysRented() > 2 )
                amount += ( rental.getDaysRented() - 2 ) * 1.5 ;
            break;
        case Movie::NEW_RELEASE:
            amount += rental.getDaysRented() * 3;
            break;
        case Movie::CHILDRENS:
            amount += 1.5;
            if ( rental.getDaysRented() > 3 )
                amount += ( rental.getDaysRented() - 3 ) * 1.5;
            break;
    }

    return amount;
}

string Customer::statement()
{
    double totalAmount = 0;
    int frequentRenterPoints = 0;
    ostringstream result;

    result << "Rental Record for " << getName() << "\n";

    for ( auto each : _rentals ) {
        double thisAmount = calculateAmount(each);

        // add frequent renter points
        frequentRenterPoints++;
        // add bonus for a two day new release rental
        if ( ( each.getMovie().getPriceCode() == Movie::NEW_RELEASE )
             && each.getDaysRented() > 1 ) frequentRenterPoints++;

        // show figures for this rental
        result << "\t" << each.getMovie().getTitle() << "\t"
               << thisAmount << "\n";
        totalAmount += thisAmount;
    }
    // add footer lines
    result << "Amount owed is " << totalAmount << "\n";
    result << "You earned " << frequentRenterPoints
           << " frequent renter points";
    return result.str();
}