//240 Count Down daily

#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    int N;

    // Ask user for N value and validate
    do
    {
        cout << "N value (must be greater than or equal to 1)? ";
        cin >> N;

        if (N < 1)
        {
            cout << "Error: the N-value must be greater than or equal to 1. Try again:";
        }
    } while (N < 1);

	cout << endl;

    // Display values from N to 1
    for (int i = N; i >= 1; --i)
    {
        cout << setw(3) << i;
    }

    cout << endl;

    return 0;
} // end main() 

