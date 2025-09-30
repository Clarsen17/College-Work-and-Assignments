#include <iostream>
#include <iomanip>

using namespace std;

int getInt3 ( stirng, int );

int main ()
{
// test score
int test_score;
test score = getInt3 ("Enter a test score: ", 0)

cout << "The test score is " << test_score << endl;


// age 


	
	
	
	
}

int getInt3 ( string prompt, int lower_bound )
{
int user_val; 

cout <<prompt << " (must be greater than " << lower_bound << "); ";
cin >> user_val


//loop
while ( user_val < lower_bound )
{
	cout << "You messed up! Try again: ";
	cin >> user_val;
}

return user_val;
	
}
