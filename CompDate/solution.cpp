//Collen Larsen z1930118

#include "date.h"

bool operator<(const date& d1, const date& d2)
{
	// Comparing years
    if (d1.year < d2.year)
        return true;
    else if (d1.year > d2.year)
        return false;
        
	// If years are equal, comparing months
    if (d1.month < d2.month)
        return true;
    else if (d1.month > d2.month)
        return false;
        
	// If years and months are equal, comparing days
    if (d1.day < d2.day)
        return true;
        
	// If all fields are equal, dates are not less than each other
    return false;
}

