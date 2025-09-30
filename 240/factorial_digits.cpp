// 240 Count Factorial Digits Daily

#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    int N;

    // Get the value for N
    cout << "N value (must be greater than or equal to 0)? ";
    cin >> N;

    // Check if N is a valid input
    if (N < 0 || N > 12)
    {
        cout << "\nInvalid Input: " << N << "\n";
        return 0;
    }

    // Calculate factorial and count digits
    int factorial = 1;
    int digits = 0;
    for (int i = 1; i <= N; ++i)
    {
        factorial *= i;
    }

    // Count the number of digits in the factorial
    int temp = factorial;
    while (temp != 0)
    {
        temp /= 10;
        ++digits;
    }
    // Display the output to the user
    cout << "\n" << N << "! is equal to " << factorial << ". There are " << digits << " digits.\n";

    return 0;
}// end main() 
