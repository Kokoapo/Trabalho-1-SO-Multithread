#include "conta.hpp"
#include <random>
#include <fstream>
#include <functional>
#include <thread>
#include <iostream>
#include <vector>

void deposit(bank_account *contas, int c, int valor) {
    contas[c].deposit(valor);
}

void withdraw(bank_account *contas, int c, int valor) {
    contas[c].withdraw(valor);
}

void balance(bank_account *contas, int c) {
    contas[c].get_balance();
}

int main() {
    srand(1);
    bank_account contas[20];
    std::thread threads[300000];
    for(int i = 0; i < 300000; i+=3) {
        int c1 = rand()%10;
        int c2 = rand()%10;
        int valor = rand()%500;
        threads[i] = std::thread(deposit, contas, c1, valor);
        threads[i+1] = std::thread(withdraw, contas, c2, valor);
        threads[i+2] = std::thread(balance, contas, c1);
        //printf("R$%d de %d para %d\n", valor, c2, c1);
        threads[i].join();
        threads[i+1].join();
        threads[i+2].join();
    }

    /*for(int i = 0; i < 30000; i++) {
        threads[i].join();
    }*/

    std::ofstream output;
    output.open("resultado_paralelo_thread_safe.txt", std::ios::out);
    for(int i = 0; i < 10; i++) {
        output << contas[i].get_balance() << std::endl;
    }

    return 0;
} 