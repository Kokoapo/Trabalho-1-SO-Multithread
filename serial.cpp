#include "conta.hpp"
#include <random>
#include <fstream>
using namespace std;

int main() {
    srand(1);
    bank_account contas[10];
    for(int i = 0; i < 100000; i++) {
        int conta1 = rand()%10;
        int conta2 = rand()%10;
        int valor = rand()%500;
        //printf("R$%d de %d para %d\n", valor, conta2, conta1);
        contas[conta1].deposit(valor);
        contas[conta2].withdraw(valor);
        contas[rand()%10].get_balance();
    }
    
    ofstream output;
    output.open("resultado_serial.txt", ios::out);
    for(int i = 0; i < 10; i++) {
        output << contas[i].get_balance() << endl;
    }

    return 0;
} 