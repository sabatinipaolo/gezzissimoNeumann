#include <iostream>
#include <iomanip>
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
    int op_code;
    string decodifica;

    // todo funzione execute
};

void
mostra_stato()
{

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

int main()
{
    mostra_stato();
}