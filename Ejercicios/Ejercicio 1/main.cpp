#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;
class Account {
private:
    string id;
    double balance;
    mutable mutex mtx;

public:
    Account(const string& id, double initial_balance)
        : id(id), balance(initial_balance) {}

    void depositar(double amount) {
        lock_guard<mutex> lock(mtx);
        balance += amount;
    }

    void retirar(double amount) {
        lock_guard<mutex> lock(mtx);
        balance -= amount;
    }

    double getBalance() const {
        lock_guard<mutex> lock(mtx);
        return balance;
    }
};

class TransactionManager {
private:
    TransactionManager() = default;
    ~TransactionManager() = default;

public:
    TransactionManager(const TransactionManager&) = delete;
    TransactionManager& operator=(const TransactionManager&) = delete;

    static TransactionManager& getInstance() {
        static TransactionManager instance;
        return instance;
    }

    void depositar(Account* account, double amount) {
        if (account) {
            account->depositar(amount);
        }
    }

    void retirar(Account* account, double amount) {
        if (account) {
            account->retirar(amount);
        }
    }
};