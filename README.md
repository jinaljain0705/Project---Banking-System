# BankingSystem
Program: BankingSystem

code:
```cpp
  // Banking System

#include <iostream>
#include <string>
using namespace std;

const int MAX = 100;

class Account {
protected:
    int accNo;
    string holder;
    float balance;

public:
    virtual void create(int accNo, string holder, float balance) {
        this->accNo = accNo;
        this->holder = holder;
        this->balance = balance;
        cout << "Deposited $" << balance << " successfully." << endl;
    }

    virtual void deposit(float amount) {
        balance += amount;
        cout << "Deposited $" << amount << " successfully." << endl;
        cout << "Current Balance $" << balance << " successfully." << endl;
    }

    virtual void withdraw(float amount) {
        if (amount <= balance) {
            balance -= amount;
            cout << "Withdrew $" << amount << " successfully." << endl;
            cout << "Current Balance $" << balance << " successfully." << endl;
        } else {
            cout << "Insufficient Balance!" << endl;
        }
    }

    virtual void display() {
        cout << "Account Number: " << accNo << endl;
        cout << "Account Holder: " << holder << endl;
        cout << "Current Balance: $" << balance << endl;
    }

    virtual void calculateInterest() {
        cout << "Interest not applicable for this account." << endl;
    }

    int getAccNo() {
        return accNo;
    }

    virtual ~Account() {}
};

class SavingsAccount : public Account {
    float interestRate;

public:
    void create(int accNo, string holder, float balance, float rate) {
        Account::create(accNo, holder, balance);
        interestRate = rate;
        cout << "Savings Account created successfully." << endl;
    }

    void calculateInterest() {
        float interest = balance * interestRate / 100;
        balance += interest;
        cout << "Interest $" << interest << " added. New Balance: $" << balance << endl;
    }

    void display() {
        Account::display();
        cout << "Interest Rate: " << interestRate << "%" << endl;
    }
};

class CheckingAccount : public Account {
    float overdraft;

public:
    void create(int accNo, string holder, float balance, float limit) {
        Account::create(accNo, holder, balance);
        overdraft = limit;
        cout << "Checking Account created successfully." << endl;
    }

    void withdraw(float amount) {
        if (amount <= balance) {
            balance -= amount;
            cout << "Withdrew $" << amount << " successfully." << endl;
            cout << "Current Balance $" << balance << " successfully." << endl;
        } else if (amount <= balance + overdraft) {
            float usedOD = amount - balance;
            balance = 0;
            cout << "Withdrew $" << amount << " successfully." << endl;
            cout << "Overdraft used: $" << usedOD << endl;
        } else {
            cout << "Overdraft limit exceeded!" << endl;
        }
    }

    void display() {
        Account::display();
        cout << "Overdraft Limit: $" << overdraft << endl;
    }
};

class FixedDepositAccount : public Account {
    int months;

public:
    void create(int accNo, string holder, float balance, int term) {
        Account::create(accNo, holder, balance);
        months = term;
        cout << "Fixed Deposit Account created successfully." << endl;
    }

    void display() {
        Account::display();
        cout << "Term Duration: " << months << " months" << endl;
    }
};

int main() {
    Account* accounts[MAX];
    int count = 0;
    int choice;

    do {
        cout << "=== BANKING SYSTEM MENU ===" << endl;
        cout << "1. Create Savings Account" << endl;
        cout <<" 2. Create Checking Account" << endl;
        cout << "3. Create Fixed Deposit Account" << endl;
        cout << "4. Deposit" << endl;
        cout << "5. Withdraw" << endl;
        cout << "6. Display All Accounts" << endl;
        cout << "7. Calculate Interest" << endl;
        cout << "8. Display Balance" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: " << endl;
        cin >> choice;

        if (choice == 1 && count < MAX) {
            int acc;
            float bal, rate;
            string name;
            cout << "Enter Account Number: " << endl; 
            cin >> acc;
            cout << "Enter Account Holder Name: " << endl; 
            cin >> name;
            cout << "Enter Initial Balance: " << endl; 
            cin >> bal;
            cout << "Enter Interest Rate (%): " << endl; 
            cin >> rate;

            SavingsAccount* sa = new SavingsAccount();
            sa->create(acc, name, bal, rate);
            accounts[count++] = sa;

        } else if (choice == 2 && count < MAX) {
            int acc;
            float bal, limit;
            string name;
            cout << "Enter Account Number: " << endl; 
            cin >> acc;
            cout << "Enter Account Holder Name: " << endl; 
            cin >> name;
            cout << "Enter Initial Balance: " << endl; 
            cin >> bal;
            cout << "Enter Overdraft Limit: " << endl; 
            cin >> limit;

            CheckingAccount* ca = new CheckingAccount();
            ca->create(acc, name, bal, limit);
            accounts[count++] = ca;

        } else if (choice == 3 && count < MAX) {
            int acc, term;
            float bal;
            string name;
            cout << "Enter Account Number: " << endl; 
            cin >> acc;
            cout << "Enter Account Holder Name: " << endl; 
            cin >> name;
            cout << "Enter Initial Balance: " << endl; 
            cin >> bal;
            cout << "Enter Term Duration (months): " << endl; 
            cin >> term;

            FixedDepositAccount* fa = new FixedDepositAccount();
            fa->create(acc, name, bal, term);
            accounts[count++] = fa;

        } else if (choice == 4) {
            int acc;
            float amt;
            cout << "Enter Account Number: " << endl; 
            cin >> acc;
            bool found = false;
            for (int i = 0; i < count; i++) {
                if (accounts[i]->getAccNo() == acc) {
                    cout << "Enter Amount to Deposit: " << endl; 
                    cin >> amt;
                    accounts[i]->deposit(amt);
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Account not found." << endl;

        } else if (choice == 5) {
            int acc;
            float amt;
            cout << "Enter Account Number: " << endl; 
            cin >> acc;
            bool found = false;
            for (int i = 0; i < count; i++) {
                if (accounts[i]->getAccNo() == acc) {
                    cout << "Enter Amount to Withdraw: " << endl; 
                    cin >> amt;
                    accounts[i]->withdraw(amt);
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Account not found." << endl;

        } else if (choice == 6) {
            for (int i = 0; i < count; i++) {
                cout << "\n--- Account [" << i << "] ---" << endl;
                accounts[i]->display();
            }

        } else if (choice == 7) {
            for (int i = 0; i < count; i++) {
                accounts[i]->calculateInterest();
            }

        } else if (choice == 8) {
            for (int i = 0; i < count; i++) {
                cout << "Account [" << i << "] Balance: ";
                accounts[i]->display();
            }

        } else if (choice == 9) {
            cout << "Thank you for using the Banking System.";
        } else {
            cout << "Invalid choice or limit reached!" << endl;
        }

    } while (choice != 9);

    for (int i = 0; i < count; i++) {
        delete accounts[i];
    }

    return 0;
}
```
Output:
![BankingSystem](https://github.com/jinaljain0705/DSA-with-C--/blob/Project---6/Project%20-%20Banking%20System/Output/Output-1.png)
![BankingSystem](https://github.com/jinaljain0705/DSA-with-C--/blob/Project---6/Project%20-%20Banking%20System/Output/Output-2.png)
![BankingSystem](https://github.com/jinaljain0705/DSA-with-C--/blob/Project---6/Project%20-%20Banking%20System/Output/Output-3.png)
![BankingSystem](https://github.com/jinaljain0705/DSA-with-C--/blob/Project---6/Project%20-%20Banking%20System/Output/Output-4.png)
![BankingSystem](https://github.com/jinaljain0705/DSA-with-C--/blob/Project---6/Project%20-%20Banking%20System/Output/Output-5.png)
