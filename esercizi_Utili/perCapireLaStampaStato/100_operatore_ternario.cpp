#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    /* l'operatore ternario:

         condizione ? espressione_vera : espressione_falsa

         serve ad abbreviare il codice in situazioni abbastanza ricorrenti..
     */

    int numero;

    cout << "inserire un numero intero e positivo ";
    cin >> numero;

    // esempio invece di scrivere :

    cout << " il numero inserito è ";
    if ((numero % 2) == 0)
        cout << "pari";
    else
        cout << "dispari";

    cout << endl;

    // posso scrivere

    cout << " il numero inserito è " << ((numero % 2) == 0 ? "pari" : "dispari") << endl;
}
