#include <iostream>
#include <iomanip>
using namespace std;

int ram[9]={11,11,12,27,3,27,11,0,0};
int a=0; 
int b=0;

int ir=0;
int ip=0;

int address_bus = 0;
int data_bus=0; 
char control_bus = ' ';


void mostra_stato(){

 
cout << " +------------- CPU -------------+                             +----RAM-----+"<<endl;
cout << " |     +--------------+          |  /|                     |\\  |     "<<setw(2)<<ram[0]<<"     |   O"<<endl;
cout << " |  A= |      "<<setw(2)<<a<<"      |          | / +----DATA BUS --------+ \\ +------------+"<<endl;
cout << " |     +--------------+          |/                           \\|     "<<setw(2)<<ram[1]<<"     |   1"<<endl;
cout << " |                               |\\               "<<setw(2)<<data_bus<<"          /+------------+"<<endl;
cout << " |     +--------------+          | \\ +---------------------+ / |     "<<setw(2)<<ram[2]<<"     |   2"<<endl;
cout << " |  B= |      "<<setw(2)<<b<<"      |          |  \\|                     |/  +------------+"<<endl;
cout << " |     +--------------+          |                             |     "<<setw(2)<<ram[3]<<"     |   3"<<endl;
cout << " |                               |                             +------------+"<<endl;
cout << " |     +--------------+          |                         |\\  |     "<<setw(2)<<ram[4]<<"     |   4"<<endl;
cout << " | IR= |      "<<setw(2)<<ir<<"      |          |---- ADDRESS BUS --------+ \\ +------------+"<<endl;
cout << " |     +--------------+          |                            \\|     "<<setw(2)<<ram[5]<<"     |   5"<<endl;
cout << " |                               |            "<<setw(2)<<address_bus<<"               /+------------+"<<endl;
cout << " |                               |-------------------------+ / |     "<<setw(2)<<ram[6]<<"     |   6"<<endl;
cout << " |                               |                         |/  +------------+"<<endl;
cout << " |        +--------------+       |                             |     "<<setw(2)<<ram[7]<<"     |   7"<<endl;
cout << " | IP/PC= |      "<<setw(2)<<ip<<"      |       |---CONTROL BUS-----------\\   +------------+"<<endl;
cout << " |        +--------------+       |            "<<control_bus<<"             >  |     "<<setw(2)<<ram[8]<<"     |   8"<<endl;
cout << " |                               |-------------------------/   +------------+"<<endl;
cout << " +-------------------------------+"<<endl;
   
}

int main(){


mostra_stato();

}