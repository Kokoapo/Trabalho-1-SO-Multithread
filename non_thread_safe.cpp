#include "conta.hpp"
#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
using namespace std;
atomic<bool> start; // vamos iniciar todos os threads juntos, quero ver um data race.
void do_a_lot_of_transfers(bank_account *c1, bank_account *c2)
{
    while (!start)
    {
    }
    for (int i = 0; i < 1000; i++)
        transfer(*c1, *c2, 10);
}
void join_all(vector<thread *> &tvect)
{
    for (int i = 0; i < tvect.size(); i++)
        tvect[i]->join();
    tvect.clear();
}
void prepare_a_lot_of_transfers(vector<thread *> &tvect, bank_account &c1, bank_account &c2)
{
    start = false;
    for (int i = 0; i < 1000; i++)
        tvect.push_back(new thread(do_a_lot_of_transfers, &c1, &c2));
    start = true;
}
int main()
{
    vector<thread *> tvect;
    bank_account &c1 = create_not_safe_account(), &c2 = create_not_safe_account();
    prepare_a_lot_of_transfers(tvect, c1, c2);
    join_all(tvect);
    prepare_a_lot_of_transfers(tvect, c2, c1);
    join_all(tvect);
    cout << "resultado: conta1=" << c1.get_balance() << "\nc2=" << c2.get_balance() << "\n";
}