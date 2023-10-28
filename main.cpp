#include <iostream>
#include <iomanip>
#include <map>
#include <functional>
using namespace std;

struct Sistema
{
    int ram[9] = {11, 11, 12, 27, 3, 27, 11, 0, 0};
    int a = 0;
    int b = 0;

    int ir = 0;
    int ip = 0;

    int address_bus = 0;
    int data_bus = 0;
    char control_bus = ' ';
    string fase = "FETCH";

} sistema;

struct Istruzione
{
    int op_code; // TODO is ridondante ?
    string decodifica;
    std::function<void()> esecuzione;
};

void mostra_stato()
{
    system("clear");
    cout << " +------------- CPU -------------+                             +----RAM-----+" << endl;
    cout << " |     +--------------+          |  /|                     |\\  |     " << setw(2) << sistema.ram[0] << "     |   O" << endl;
    cout << " |  A= |      " << setw(2) << sistema.a << "      |          | / +----DATA BUS --------+ \\ +------------+" << endl;
    cout << " |     +--------------+          |/                           \\|     " << setw(2) << sistema.ram[1] << "     |   1" << endl;
    cout << " |                               |\\               " << setw(2) << sistema.data_bus << "          /+------------+" << endl;
    cout << " |     +--------------+          | \\ +---------------------+ / |     " << setw(2) << sistema.ram[2] << "     |   2" << endl;
    cout << " |  B= |      " << setw(2) << sistema.b << "      |          |  \\|                     |/  +------------+" << endl;
    cout << " |     +--------------+          |                             |     " << setw(2) << sistema.ram[3] << "     |   3" << endl;
    cout << " |                               |                             +------------+" << endl;
    cout << " |     +--------------+          |                         |\\  |     " << setw(2) << sistema.ram[4] << "     |   4" << endl;
    cout << " | IR= |      " << setw(2) << sistema.ir << "      |          |---- ADDRESS BUS --------+ \\ +------------+" << endl;
    cout << " |     +--------------+          |                            \\|     " << setw(2) << sistema.ram[5] << "     |   5" << endl;
    cout << " |                               |            " << setw(2) << sistema.address_bus << "               /+------------+" << endl;
    cout << " |                               |-------------------------+ / |     " << setw(2) << sistema.ram[6] << "     |   6" << endl;
    cout << " |                               |                         |/  +------------+" << endl;
    cout << " |        +--------------+       |                             |     " << setw(2) << sistema.ram[7] << "     |   7" << endl;
    cout << " | IP/PC= |      " << setw(2) << sistema.ip << "      |       |---CONTROL BUS-----------\\   +------------+" << endl;
    cout << " |        +--------------+       |            " << sistema.control_bus << "             >  |     " << setw(2) << sistema.ram[8] << "     |   8" << endl;
    cout << " |                               |-------------------------/   +------------+" << endl;
    cout << " +-------------------------------+" << endl
         << endl
         << endl;
    cout << sistema.fase << endl
         << endl;
}

void premi()
{
    string s;
    cout << endl
         << endl
         << " premi invio per il prossimo ciclo di clock";
    cin.get();
}

map<int, Istruzione> set_istruzioni;
void inizializza_set_istruzioni()
{
    set_istruzioni[0] = {0, "\t HLT \n \n \t\tFerma il sistema", []()
                         { cout << "exe di 0"; }};

    set_istruzioni[11] = {11, "\t INC A \n \n \t\tIncrementa il valore contenunto nel registro A", []()
                          {
                              cout << "=>  A + 1 --> A " << endl;
                              sistema.a++;
                          }};
    set_istruzioni[12] = {12, "\t DEC A \n \n \t\tDecrementa il valore contenunto nel registro A", []()
                          { cout << "exe di 12"; }};
    set_istruzioni[13] = {13, "\t INC B \n \n \t\tIncrementa il valore contenunto nel registro B", []()
                          { cout << "exe di 13"; }};
    set_istruzioni[14] = {14, "\t DEC B \n \n \t\tDecrementa il valore contenunto nel registro B", []()
                          { cout << "exe di 14"; }};
    set_istruzioni[27] = {27, "\t ADD A , dato \n \n \t\t Addiziona ad A il valore in memoria che segue immediatamente  l'istruzione", []()
                          { cout << "exe di 27"; }};
    set_istruzioni[28] = {28, "\t ADD B , dato \n \n \t\t Addiziona a B il valore in memoria che segue immediatamente  l'istruzione", []()
                          { cout << "exe di 28"; }};

    set_istruzioni[23] = {23, "\t MOV A , dato \n \n \t\t Copia in A il valore in memoria che segue immediatamente  l'istruzione", []()
                          { cout << "exe di 23"; }};
    set_istruzioni[24] = {24, "\t MOV B , dato \n \n \t\t Copia in B il valore in memoria che segue immediatamente  l'istruzione", []()
                          { cout << "exe di 24"; }};
}

int main()
{
    inizializza_set_istruzioni();

    while (true)
    {
        { // FETCH
            sistema.fase = "FETCH";
            mostra_stato();
            cout << "=> IP/PC  --> ADDRESS BUS" << endl;
            cout << "   \"R\" ---> CONTROL BUS" << endl;
            cout << "   RAM[ADDRESS BUS] --> DATA BUS" << endl;
            cout << "   DATA BUS --> IR" << endl;
            cout << "   IP/PC +1 --> IP/PC" << endl;
            premi();

            sistema.address_bus = sistema.ip;
            mostra_stato();

            cout << "   IP/PC  --> ADDRESS BUS" << endl;
            cout << "=> \"R\" ---> CONTROL BUS" << endl;
            cout << "   RAM[ADDRESS BUS] --> DATA BUS" << endl;
            cout << "   DATA BUS --> IR" << endl;
            cout << "   IP/PC +1 --> IP/PC" << endl;
            premi();

            sistema.control_bus = 'R';
            mostra_stato();

            cout << "   IP/PC  --> ADDRESS BUS" << endl;
            cout << "   \"R\" ---> CONTROL BUS" << endl;
            cout << "=> RAM[ADDRESS BUS] --> DATA BUS" << endl;
            cout << "   DATA BUS --> IR" << endl;
            cout << "   IP/PC +1 --> IP/PC" << endl;
            premi();

            sistema.data_bus = sistema.ram[sistema.address_bus];
            mostra_stato();

            cout << "   IP/PC  --> ADDRESS BUS" << endl;
            cout << "   \"R\" ---> CONTROL BUS" << endl;
            cout << "   RAM[ADDRESS BUS] --> DATA BUS" << endl;
            cout << "=> DATA BUS --> IR" << endl;
            cout << "   IP/PC +1 --> IP/PC" << endl;
            premi();

            sistema.ir = sistema.data_bus;
            sistema.address_bus = -1;
            sistema.data_bus = -1;
            sistema.control_bus = ' ';

            mostra_stato();

            cout << "   IP/PC  --> ADDRESS BUS" << endl;
            cout << "   \"R\" ---> CONTROL BUS" << endl;
            cout << "   RAM[ADDRESS BUS] --> DATA BUS" << endl;
            cout << "   DATA BUS --> IR" << endl;
            cout << "=> IP/PC +1 --> IP/PC" << endl;
            premi();

            sistema.ip++;

            mostra_stato();
        } // fine FETCH
        { // DECODE
            sistema.fase = "DECODE";
            mostra_stato();
            cout << endl
                 << "codice operativo  " << sistema.ir << endl
                 << endl;

            if (set_istruzioni.find(sistema.ir) == set_istruzioni.end()) // TODO c++20 m.contains( k )
            {
                cout << "op_code non valido" << endl
                     << endl;
                premi();
                continue;
            }
            else
            {
                cout << set_istruzioni[sistema.ir].decodifica << endl
                     << endl
                     << endl;
                premi();
            }
        }
        { // EXECUTE
          // TODO assert(set_istruzioni.find(sistema.ir) != set_istruzioni.end()) come si usa?
            sistema.fase = "EXECUTE";
            mostra_stato();
            set_istruzioni[sistema.ir].esecuzione();
            cout << endl
                 << endl;
            premi();
        }
    }
}