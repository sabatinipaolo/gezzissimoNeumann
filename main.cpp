#include <iostream>
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
cout << " |     +--------------+          |  /|                     |\\  |     "<<ram[0]<<"     |   O"<<endl;
cout << " |  A= |      "<<a<<"       |          | / +----DATA BUS --------+ \\ +------------+"<<endl;
cout << " |     +--------------+          |/                           \\|     "<<ram[1]<<"     |   1"<<endl;
cout << " |                               |\\               "<<data_bus<<"          /+------------+"<<endl;
cout << " |     +--------------+          | \\ +---------------------+ / |     "<<ram[2]<<"     |   2"<<endl;
cout << " |  B= |      "<<b<<"       |          |  \\|                     |/  +------------+"<<endl;
cout << " |     +--------------+          |                             |     "<<ram[3]<<"     |   3"<<endl;
cout << " |                               |                             +------------+"<<endl;
cout << " |     +--------------+          |                         |\\  |    "<<ram[4]<<"      |   4"<<endl;
cout << " | IR= |      "<<ir<<"       |          |---- ADDRESS BUS --------+ \\ +------------+"<<endl;
cout << " |     +--------------+          |                            \\|    "<<ram[5]<<"     |   5"<<endl;
cout << " |                               |            "<<address_bus<<"               /+------------+"<<endl;
cout << " |                               |-------------------------+ / |     "<<ram[6]<<"    |   6"<<endl;
cout << " |                               |                         |/  +------------+"<<endl;
cout << " |        +--------------+       |                             |     "<<ram[7]<<"      |   7"<<endl;
cout << " | IP/PC= |      "<<ip<<"       |       |---CONTROL BUS-----------\\   +------------+"<<endl;
cout << " |        +--------------+       |            "<<control_bus<<"             >  |     "<<ram[8]<<"      |   8"<<endl;
cout << " |                               |-------------------------/   +------------+"<<endl;
cout << " +-------------------------------+"<<endl;
   
}

int main(){


mostra_stato();

}