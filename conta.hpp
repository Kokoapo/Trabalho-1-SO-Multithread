#include <mutex>
class bank_account
{
private:
    float balance;
    std::mutex account_mutex;

public:
    bank_account(float balance = 0) : balance(balance) {}
    float get_balance()
    {
        account_mutex.lock(); // evitar leitura de valores inconsistentes
        float final = balance;
        account_mutex.unlock(); // liberando o mutex para outros threads
        return final;
    }
    void withdraw(float amount)
    {
        if (amount > 0) // just in case
        {
            account_mutex.lock();
            balance -= amount;
            account_mutex.unlock();
        }
    }
    void deposit(float amount)
    {
        if (amount > 0) // just in case
        {
            account_mutex.lock();
            balance += amount;
            account_mutex.unlock();
        }
    }
};