#include <iostream>
#include <iomanip>
#include <map>
#include <functional>
using namespace std;

struct Registro
{
    int val = 0;
    string nome;
};

struct Sistema
{
    int ram[9] = {23, 4, 0, 3, 27, 2, 28, 3, 0};
    Registro a{0, "A"};
    Registro b{0, "B"};

    Registro mr{0, "MR"};
    Registro dr{0, "DR"};

    Registro ir{0, "IR"};
    Registro ip{0, "IP/PC"};

    int address_bus = -1;
    int data_bus = -1;
    char control_bus = ' ';
    string fase = "FETCH";
    string stato = "RUNNING";

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
    cout << " +---------- CPU -----------------------+                             +----RAM-----+" << endl;
    cout << " |  +- A ----+                          |  /|                     |\\  |     " << setw(2) << sistema.ram[0] << "     |   O" << endl;
    cout << " |  |    " << setw(2) << sistema.a.val << "  |                 +- DR ---+ / +----DATA BUS --------+ \\ +------------+" << endl;
    cout << " |  +--------+                 |    " << setw(2) << sistema.dr.val << "  |/                           \\|     " << setw(2) << sistema.ram[1] << "     |   1" << endl;
    cout << " |                             +--------+\\               " << setw(2) << (sistema.data_bus < 0 ? "" : to_string(sistema.data_bus)) << "          /+------------+" << endl;
    cout << " |  +- B ----+                          | \\ +---------------------+ / |     " << setw(2) << sistema.ram[2] << "     |   2" << endl;
    cout << " |  |    " << setw(2) << sistema.b.val << "  |                          |  \\|                     |/  +------------+" << endl;
    cout << " |  +--------+                          |                             |     " << setw(2) << sistema.ram[3] << "     |   3" << endl;
    cout << " |                                      |                             +------------+" << endl;
    cout << " |  +- IR ---+                          |                         |\\  |     " << setw(2) << sistema.ram[4] << "     |   4" << endl;
    cout << " |  |    " << setw(2) << sistema.ir.val << "  |                 +- AR ---+---- ADDRESS BUS --------+ \\ +------------+" << endl;
    cout << " |  +--------+                 |    " << setw(2) << sistema.mr.val << "  |                            \\|     " << setw(2) << sistema.ram[5] << "     |   5" << endl;
    cout << " |                             +--------+            " << setw(2) << (sistema.address_bus < 0 ? "" : to_string(sistema.address_bus)) << "              /+------------+" << endl;
    cout << " |                                      |-------------------------+ / |     " << setw(2) << sistema.ram[6] << "     |   6" << endl;
    cout << " |                                      |                         |/  +------------+" << endl;
    cout << " |  +-IP/PC -+                          |                             |     " << setw(2) << sistema.ram[7] << "     |   7" << endl;
    cout << " |  |    " << setw(2) << sistema.ip.val << "  |                          |---CONTROL BUS------------\\  +------------+" << endl;
    cout << " |  +--------+                          |            " << sistema.control_bus << "              > |     " << setw(2) << sistema.ram[8] << "     |   8" << endl;
    cout << " |                                      |--------------------------/  +------------+" << endl;
    cout << " +--------------------------------------+" << endl
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

void lettura_da_memoria(Registro sorgente)
{
    cout << "=> " << sorgente.nome << " ---> AR" << endl;
    cout << "   AR ---> ADDRESS BUS   , \"R\" ---> CONTROL BUS" << endl;
    cout << "   RAM[ADDRESS BUS] --> DATA BUS" << endl;
    cout << "   DATA BUS --> DATA REGISTER " << endl;
    premi();

    sistema.mr.val = sorgente.val;
    mostra_stato();

    cout << "   " << sorgente.nome << " ---> AR" << endl;
    cout << "=> AR ---> ADDRESS BUS   , \"R\" ---> CONTROL BUS" << endl;
    cout << "   RAM[ADDRESS BUS] --> DATA BUS" << endl;
    cout << "   DATA BUS --> DATA REGISTER " << endl;
    premi();

    sistema.address_bus = sistema.mr.val;
    sistema.control_bus = 'R';
    mostra_stato();

    cout << "   " << sorgente.nome << " ---> AR" << endl;
    cout << "   AR ---> ADDRESS BUS   , \"R\" ---> CONTROL BUS" << endl;
    cout << "=> RAM[ADDRESS BUS] --> DATA BUS" << endl;
    cout << "   DATA BUS --> DATA REGISTER " << endl;
    premi();

    sistema.data_bus = sistema.ram[sistema.address_bus];
    mostra_stato();

    cout << "   " << sorgente.nome << " ---> AR" << endl;
    cout << "   AR ---> ADDRESS BUS   , \"R\" ---> CONTROL BUS" << endl;
    cout << "   RAM[ADDRESS BUS] --> DATA BUS" << endl;
    cout << "=> DATA BUS --> DATA REGISTER " << endl;
    premi();

    sistema.dr.val = sistema.data_bus;

    sistema.address_bus = -1;
    sistema.data_bus = -1;
    sistema.control_bus = ' ';

    mostra_stato();
}

map<int, Istruzione> set_istruzioni;
void inizializza_set_istruzioni()
{
    set_istruzioni[0] = {0, "\t HLT \n \n \t\tFerma il sistema", []()
                         {
                             cout << "fermo l'esecuzione" << endl;
                             sistema.stato = "HALTED";
                         }};

    set_istruzioni[11] = {11, "\t INC A \n \n \t\tIncrementa il valore contenunto nel registro A", []()
                          {
                              cout << "=>  A + 1 --> A " << endl;
                              sistema.a.val++;
                          }};
    set_istruzioni[12] = {12, "\t DEC A \n \n \t\tDecrementa il valore contenunto nel registro A", []()
                          {
                              cout << "=>  A - 1 --> A " << endl;
                              sistema.a.val--;
                          }};
    set_istruzioni[13] = {13, "\t INC B \n \n \t\tIncrementa il valore contenunto nel registro B", []()
                          {
                              cout << "=>  B + 1 --> A " << endl;
                              sistema.b.val++;
                          }};
    set_istruzioni[14] = {14, "\t DEC B \n \n \t\tDecrementa il valore contenunto nel registro B", []()
                          {
                              cout << "=>  B - 1 --> B " << endl;
                              sistema.b.val--;
                          }};
    set_istruzioni[27] = {27, "\t ADD A , dato \n \n \t\t Addiziona ad A il valore in memoria che segue immediatamente  l'istruzione", []()
                          {
                              lettura_da_memoria(sistema.ip);
                              cout << "   IP/PC +1 --> IP/PC ";
                              premi();
                              sistema.ip.val++;
                              mostra_stato();

                              cout << "=>  A + " << sistema.dr.val << " --> A " << endl;
                              premi();
                              sistema.a.val = sistema.a.val + sistema.dr.val;
                          }};

    set_istruzioni[28] = {28, "\t ADD B , dato \n \n \t\t Addiziona a B il valore in memoria che segue immediatamente  l'istruzione", []()
                          {
                              lettura_da_memoria(sistema.ip);
                              cout << "   IP/PC +1 --> IP/PC ";
                              premi();
                              sistema.ip.val++;
                              mostra_stato();

                              cout << "=>  B + " << sistema.dr.val << " --> B " << endl;
                              premi();
                              sistema.b.val = sistema.b.val + sistema.dr.val;
                          }};

    set_istruzioni[23] = {23, "\t MOV A , dato \n \n \t\t Copia in A il valore in memoria che segue immediatamente  l'istruzione", []()
                          {
                              lettura_da_memoria(sistema.ip);
                              cout << "   IP/PC +1 --> IP/PC ";
                              premi();
                              sistema.ip.val++;
                              mostra_stato();

                              cout << "=>    " << sistema.dr.val << " --> A " << endl;
                              premi();
                              sistema.a.val = sistema.dr.val;
                          }};
    set_istruzioni[24] = {24, "\t MOV B , dato \n \n \t\t Copia in B il valore in memoria che segue immediatamente  l'istruzione", []()
                          {
                              lettura_da_memoria(sistema.ip);
                              cout << "   IP/PC +1 --> IP/PC ";
                              premi();
                              sistema.ip.val++;
                              mostra_stato();

                              cout << "=>    " << sistema.dr.val << " --> B " << endl;
                              premi();
                              sistema.b.val = sistema.dr.val;
                          }};
}

int main()
{
    inizializza_set_istruzioni();

    while (sistema.stato == "RUNNING")
    {
        { // FETCH
            sistema.fase = "FETCH";
            mostra_stato();

            lettura_da_memoria(sistema.ip);
            mostra_stato();

            cout << "=> DR --> IR" << endl;
            premi();
            sistema.ir.val = sistema.dr.val;
            mostra_stato();

            cout << "=> IP/PC +1 --> IP/PC" << endl;
            premi();
            sistema.ip.val++;
            mostra_stato();
        } // fine FETCH

        { // DECODE
            sistema.fase = "DECODE";
            mostra_stato();
            cout << endl
                 << "codice operativo  " << sistema.ir.val << endl
                 << endl;

            if (set_istruzioni.find(sistema.ir.val) == set_istruzioni.end()) // TODO c++20 m.contains( k )
            {
                cout << "op_code non valido" << endl
                     << endl;
                premi();
                continue;
            }
            else
            {
                cout << set_istruzioni[sistema.ir.val].decodifica << endl
                     << endl
                     << endl;
                premi();
            }
        }
        { // EXECUTE
          // TODO assert(set_istruzioni.find(sistema.ir) != set_istruzioni.end()) come si usa?
            sistema.fase = "EXECUTE";
            mostra_stato();
            set_istruzioni[sistema.ir.val].esecuzione();
        }
    }
}