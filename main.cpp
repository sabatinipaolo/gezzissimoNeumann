#include <iostream>
#include <iomanip>
using namespace std;

int ram[9] = {11, 11, 12, 27, 3, 27, 11, 0, 0};
int a = 0;
int b = 0;

int ir = 0;
int ip = 0;

int address_bus = -1;
int data_bus = -1;
char control_bus = ' ';

void mostra_stato()
{
    system("clear");
    cout << endl;
    cout << " +------------- CPU -------------+                             +----RAM-----+" << endl;
    cout << " |     +--------------+          |  /|                     |\\  |     " << setw(2) << ram[0] << "     |   O" << endl;
    cout << " |  A= |      " << setw(2) << a << "      |          | / +----DATA BUS --------+ \\ +------------+" << endl;
    cout << " |     +--------------+          |/                           \\|     " << setw(2) << ram[1] << "     |   1" << endl;
    cout << " |                               |\\               " << setw(2) << (data_bus < 0 ? "" : to_string(data_bus)) << "          /+------------+" << endl;
    cout << " |     +--------------+          | \\ +---------------------+ / |     " << setw(2) << ram[2] << "     |   2" << endl;
    cout << " |  B= |      " << setw(2) << b << "      |          |  \\|                     |/  +------------+" << endl;
    cout << " |     +--------------+          |                             |     " << setw(2) << ram[3] << "     |   3" << endl;
    cout << " |                               |                             +------------+" << endl;
    cout << " |     +--------------+          |                         |\\  |     " << setw(2) << ram[4] << "     |   4" << endl;
    cout << " | IR= |      " << setw(2) << ir << "      |          |---- ADDRESS BUS --------+ \\ +------------+" << endl;
    cout << " |     +--------------+          |                            \\|     " << setw(2) << ram[5] << "     |   5" << endl;
    cout << " |                               |            " << setw(2) << (address_bus < 0 ? "" : to_string(address_bus)) << "              /+------------+" << endl;
    cout << " |                               |-------------------------+ / |     " << setw(2) << ram[6] << "     |   6" << endl;
    cout << " |                               |                         |/  +------------+" << endl;
    cout << " |        +--------------+       |                             |     " << setw(2) << ram[7] << "     |   7" << endl;
    cout << " | IP/PC= |      " << setw(2) << ip << "      |       |---CONTROL BUS-----------\\   +------------+" << endl;
    cout << " |        +--------------+       |            " << control_bus << "             >  |     " << setw(2) << ram[8] << "     |   8" << endl;
    cout << " |                               |-------------------------/   +------------+" << endl;
    cout << " +-------------------------------+" << endl;
}
void premi()
{
    string s;
    cout << endl
         << endl
         << " premi invio per il prossimo ciclo di clock";
    cin.get();
}

int main()
{

    mostra_stato();

    while (true)
    {
        { // FETCH
            cout << endl
                 << "FETCH **********" << endl
                 << endl;
            cout << "=> IP/PC  --> ADDRESS BUS" << endl;
            cout << "   \"R\" ---> CONTROL BUS" << endl;
            cout << "   RAM[ADDRESS BUS] --> DATA BUS" << endl;
            cout << "   DATA BUS --> IR" << endl;
            cout << "   IP/PC +1 --> IP/PC" << endl;
            premi();

            address_bus = ip;
            mostra_stato();

            cout << endl
                 << "FETCH" << endl
                 << endl;
            cout << "   IP/PC  --> ADDRESS BUS" << endl;
            cout << "=> \"R\" ---> CONTROL BUS" << endl;
            cout << "   RAM[ADDRESS BUS] --> DATA BUS" << endl;
            cout << "   DATA BUS --> IR" << endl;
            cout << "   IP/PC +1 --> IP/PC" << endl;
            premi();

            control_bus = 'R';
            mostra_stato();

            cout << endl
                 << "FETCH" << endl
                 << endl;
            cout << "   IP/PC  --> ADDRESS BUS" << endl;
            cout << "   \"R\" ---> CONTROL BUS" << endl;
            cout << "=> RAM[ADDRESS BUS] --> DATA BUS" << endl;
            cout << "   DATA BUS --> IR" << endl;
            cout << "   IP/PC +1 --> IP/PC" << endl;
            premi();

            data_bus = ram[address_bus];
            mostra_stato();

            cout << endl
                 << "FETCH" << endl
                 << endl;
            cout << "   IP/PC  --> ADDRESS BUS" << endl;
            cout << "   \"R\" ---> CONTROL BUS" << endl;
            cout << "   RAM[ADDRESS BUS] --> DATA BUS" << endl;
            cout << "=> DATA BUS --> IR" << endl;
            cout << "   IP/PC +1 --> IP/PC" << endl;
            premi();

            ir = data_bus;
            address_bus = -1;
            data_bus = -1;
            control_bus = ' ';

            mostra_stato();

            cout << endl
                 << "FETCH" << endl
                 << endl;
            cout << "   IP/PC  --> ADDRESS BUS" << endl;
            cout << "   \"R\" ---> CONTROL BUS" << endl;
            cout << "   RAM[ADDRESS BUS] --> DATA BUS" << endl;
            cout << "   DATA BUS --> IR" << endl;
            cout << "=> IP/PC +1 --> IP/PC" << endl;
            premi();

            ip++;

            mostra_stato();
        } // fine FETCH

        { // DECODE
            cout << endl
                 << "DECODE di " << ir << " **********" << endl
                 << endl;
            switch (ir)
            {
            case 11:
                cout << " INC A" << endl;
                cout << " incrementa il valore del registro A " << endl
                     << endl;
                break;
            case 12:
                cout << " DEC A" << endl;
                cout << " decrementa il valore del registro A " << endl
                     << endl;
                break;
            case 27:
                cout << " ADD A , n " << endl;
                cout << " addiziona ad A il valore in memoria che segue immediatamente  l'istruzione" << endl
                     << endl;
                break;
            case 0:
                cout << " HLT " << endl;
                cout << " ferma il sistema " << endl
                     << endl;
                break;
            default:

                break;
            }
            premi();
            mostra_stato();
        } // fine DECODE

        { // EXECUTE
            cout << endl
                 << "EXECUTE **********" << endl
                 << endl;

            switch (ir)
            {
            case 11:
                cout << "=>  A + 1 --> A " << endl;
                premi();
                a++;
                mostra_stato();
                break;

            case 12:
                cout << "=>  A - 1 --> A " << endl;
                premi();
                a--;
                mostra_stato();
                break;

            case 27:
                cout << "=> IP/PC  --> ADDRESS BUS" << endl;
                cout << "   \"R\" ---> CONTROL BUS" << endl;
                cout << "   RAM[ADDRESS BUS] --> DATA BUS" << endl;
                cout << "   A + DATA BUS --> A" << endl;
                cout << "   IP/PC +1 --> IP/PC" << endl;
                premi();

                address_bus = ip;
                mostra_stato();

                cout << endl
                     << "EXECUTE" << endl
                     << endl;
                cout << "   IP/PC  --> ADDRESS BUS" << endl;
                cout << "=> \"R\" ---> CONTROL BUS" << endl;
                cout << "   RAM[ADDRESS BUS] --> DATA BUS" << endl;
                cout << "   A + DATA BUS --> A" << endl;
                cout << "   IP/PC +1 --> IP/PC" << endl;
                premi();

                control_bus = 'R';
                mostra_stato();

                cout << endl
                     << "EXECUTE" << endl
                     << endl;
                cout << "   IP/PC  --> ADDRESS BUS" << endl;
                cout << "   \"R\" ---> CONTROL BUS" << endl;
                cout << "=> RAM[ADDRESS BUS] --> DATA BUS" << endl;
                cout << "   A + DATA BUS --> A" << endl;
                cout << "   IP/PC +1 --> IP/PC" << endl;
                premi();

                data_bus = ram[address_bus];
                mostra_stato();

                cout << endl
                     << "EXECUTE" << endl
                     << endl;
                cout << "   IP/PC  --> ADDRESS BUS" << endl;
                cout << "   \"R\" ---> CONTROL BUS" << endl;
                cout << "   RAM[ADDRESS BUS] --> DATA BUS" << endl;
                cout << "=> A + DATA BUS --> A" << endl;
                cout << "   IP/PC +1 --> IP/PC" << endl;
                premi();

                a = a + data_bus;
                address_bus = -1;
                data_bus = -1;
                control_bus = ' ';

                mostra_stato();

                cout << endl
                     << "EXECUTE" << endl
                     << endl;
                cout << "   IP/PC  --> ADDRESS BUS" << endl;
                cout << "   \"R\" ---> CONTROL BUS" << endl;
                cout << "   RAM[ADDRESS BUS] --> DATA BUS" << endl;
                cout << "   A + DATA BUS --> A" << endl;
                cout << "=> IP/PC +1 --> IP/PC" << endl;
                premi();

                ip++;

                mostra_stato();
                break;

            case 0:
                return 0;

            default:
                break;
            }
        }
    }
}