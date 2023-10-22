#include "conta.hpp"
#include <random>
#include <fstream>
using namespace std;

int main() {
    bank_account contas[20];
    for(int i = 0; i < 10; i++) {
        contas[rand()%20].deposit(rand()%500);
        contas[rand()%20].withdraw(rand()%500);
        contas[rand()%20].get_balance();
    }
    
    ofstream output;
    output.open("resultado_serial.txt", ios::out);
    for(int i = 0; i < 20; i++) {
        output << contas[i].get_balance() << endl;
    }

    return 0;
} 