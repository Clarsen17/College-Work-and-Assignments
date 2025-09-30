#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	int score;
	
	cout << "What is the test score? ";
	cin >> score;
	cout << endl;
	// Determine the letter grade using if statements
    	if (score >= 92 && score <= 100) 
		{
        cout << "The score " << score << " earns the grade A" << endl;
    	} else if (score >= 84 && score <= 91) {
        cout << "The score " << score << " earns the grade B" << endl;
    	} else if (score >= 76 && score <= 83) {
        cout << "The score " << score << " earns the grade C" << endl;
    	} else if (score >= 68 && score <= 75) {
        cout << "The score " << score << " earns the grade D" << endl;
    	} else if (score >= 0 && score <= 67) {
        cout << "The score " << score << " earns the grade F" << endl;
    	} 
        
        
    
	
	return 0;
}

