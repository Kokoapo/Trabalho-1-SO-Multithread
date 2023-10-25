#include <mutex>
class bank_account
{
public:
    virtual float get_balance()=0;
    virtual void deposit(float amount)=0;
    virtual void withdraw(float amount)=0;
};
class bank_account_safe: public bank_account
{
private:
    float balance;
    std::mutex account_mutex;

public:
    bank_account(float balance = 0) : balance(balance) {}
    ~bank_account_safe()
    {
        delete this;
    }
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

class bank_account_not_safe: public bank_account
{
private:
    float balance;

public:
~bank_account_not_safe()
{
    delete this;
}
    bank_account_not_safe(float balance = 0) : balance(balance) {}
    float get_balance()
    {
        return balance;
    }
    void withdraw(float amount)
    {
        if (amount > 0) // just in case
            balance -= amount;
    }
    void deposit(float amount)
    {
        if (amount > 0) // just in case
            balance += amount;
    }
};
void transfer(bank_account &c1, bank_account &c2, float amount)
{
    c1.withdraw(amount);
    c2.deposit(amount);
}
bank_account &create_safe_account(float initial_amount=0.0)
{
    return &(new bank_account_safe(float initial_amount));
}
bank_account &create_not_safe_account(float initial_amount=0.0)
{
    return &(new bank_account_not_safe(float initial_amount));
}