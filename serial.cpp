#include "conta.hpp"
#include <iostream>

using namespace std;
void do_a_lot_of_transfers(bank_account &c1, bank_account &c2)
{
    for (int i = 0; i < 1000000; i++)
        transfer(c1, c2, 10);
}
int main()
{
    bank_account &c1 = create_safe_account(), &c2 = create_safe_account();
    do_a_lot_of_transfers(c1, c2);
    do_a_lot_of_transfers(c2, c1);
    cout << "resultado: conta1=" << c1.get_balance() << "\nc2=" << c2.get_balance() << "\n";
}