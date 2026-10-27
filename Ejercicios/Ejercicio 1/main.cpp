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

    void deposit(double amount) {
        lock_guard<mutex> lock(mtx);
        balance += amount;
    }

    void withdraw(double amount) {
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

    void deposit(Account* account, double amount) {
        if (account) {
            account->deposit(amount);
        }
    }

    void withdraw(Account* account, double amount) {
        if (account) {
            account->withdraw(amount);
        }
    }
};