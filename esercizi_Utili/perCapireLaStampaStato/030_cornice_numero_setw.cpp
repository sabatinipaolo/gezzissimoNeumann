#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int numero;
    cout << "inserire un numero intero ";
    cin >> numero;
    cout << "+------------+" << endl;
    cout << "| " << setw(10) << numero << " |" << endl;
    cout << "+------------+" << endl
         << endl;
}