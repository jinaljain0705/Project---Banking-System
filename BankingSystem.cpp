// Banking System

#include <iostream>
#include <string>
using namespace std;

const int MAX_ACCOUNTS = 100;

class Account
{
protected:
    int accNo;
    string name;
    float balance;

public:
    string type;

    void createAccount(string t, int number, string holder, float initial)
    {
        type = t;
        accNo = number;
        name = holder;
        balance = initial;
        cout << "Deposited $" << balance << "successfully." << endl;
    }

    virtual void display()
    {
        cout << "Account Number: " << accNo << endl;
        cout << "Account Holder: " << name << endl;
        cout << "Current Balance: $" << balance << endl;
    }

    void deposit(float amount)
    {
        balance += amount;
        cout << "Deposited $" << amount << "successfully." << endl;
        cout << "Current Balance $" << balance << "successfully." << endl;
    }

    virtual void withdraw(float amount)
    {
        if (balance >= amount)
        {
            balance -= amount;
            cout << "Withdrew $" << amount << "successfully." << endl;
            cout << "Current Balance $" << balance << "successfully." << endl;
        }
        else
        {
            cout << "Insufficient balance." << endl;
        }
    }

    virtual void calculateInterest() {}
    void displayBalance()
    {
        cout << "Current Balance: $" << balance << endl;
    }

    int getAccNo()
    {
        return accNo;
    }

    float &getBalance()
    {
        return balance;
    }
};

class SavingsAccount : public Account
{
    float interestRate;

public:
    void create(int number, string holder, float initial, float rate)
    {
        createAccount("Savings", number, holder, initial);
        interestRate = rate;
        cout << "Savings Account created successfully." << endl;
    }

    void display() override
    {
        Account::display();
        cout << "Interest Rate: " << interestRate << "%" << endl;
    }

    void calculateInterest() override
    {
        float interest = balance * interestRate / 100;
        balance += interest;
        cout << "Interest of $" << interest << " added. New Balance: $" << balance << endl;
    }
};

class CheckingAccount : public Account
{
    float overdraft;

public:
    void create(int number, string holder, float initial, float od)
    {
        createAccount("Checking", number, holder, initial);
        overdraft = od;
        cout << "Checking Account created successfully." << endl;
    }

    void display() override
    {
        Account::display();
        cout << "Overdraft Limit: $" << overdraft << endl;
    }

    void withdraw(float amount) override
    {
        if (balance >= amount)
        {
            balance -= amount;
            cout << "Withdrew $" << amount << " successfully." << endl;
            cout << "Current Balance $" << balance << " successfully." << endl;
        }
        else if (balance + overdraft >= amount)
        {
            float od_used = amount - balance;
            balance = 0;
            cout << "Withdrew $" << amount << " successfully." << endl;
            cout << "Overdraft used: $" << od_used << endl;
        }
        else
        {
            cout << "Withdrawal exceeds overdraft limit!" << endl;
        }
    }
};

class FixedDepositAccount : public Account
{
    int duration;

public:
    void create(int number, string holder, float initial, int months)
    {
        createAccount("Fixed", number, holder, initial);
        duration = months;
        cout << "Fixed Deposit Account created successfully." << endl;
    }

    void display() override
    {
        Account::display();
        cout << "Term Duration: " << duration << " months" << endl;
    }
};

int main()
{
    SavingsAccount savings[MAX_ACCOUNTS];
    CheckingAccount checking[MAX_ACCOUNTS];
    FixedDepositAccount fixed[MAX_ACCOUNTS];
    Account *all[MAX_ACCOUNTS];

    int choice, total = 0;

    do
    {
        cout << "=== BANKING SYSTEM MENU ===" << endl;
        cout << "1. Create Savings Account " << endl;
        cout << "2. Create Checking Account" << endl;
        cout << "3. Create Fixed Deposit Account" << endl;
        cout << "4. Deposit" << endl;
        cout << "5. Withdraw" << endl;
        cout << "6. Display All Accounts" << endl;
        cout << "7. Calculate Interest" << endl;
        cout << "8. Display Balance" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: " << endl;
        cin >> choice;

        if (choice == 1)
        {
            int no;
            float bal, rate;
            string name;
            cout << "Enter Account Number: " << endl;
            cin >> no;
            cout << "Enter Account Holder Name: " << endl;
            cin >> name;
            cout << "Enter Initial Balance: " << endl;
            cin >> bal;
            cout << "Enter Interest Rate (%): " << endl;
            cin >> rate;
            savings[total].create(no, name, bal, rate);
            all[total] = &savings[total];
            total++;
        }
        else if (choice == 2)
        {
            int no;
            float bal, od;
            string name;
            cout << "Enter Account Number: " << endl;
            cin >> no;
            cout << "Enter Account Holder Name: " << endl;
            cin >> name;
            cout << "Enter Initial Balance: " << endl;
            cin >> bal;
            cout << "Enter Overdraft Limit: " << endl;
            cin >> od;
            checking[total].create(no, name, bal, od);
            all[total] = &checking[total];
            total++;
        }
        else if (choice == 3)
        {
            int no, duration;
            float bal;
            string name;
            cout << "Enter Account Number: " << endl;
            cin >> no;
            cout << "Enter Account Holder Name: " << endl;
            cin >> name;
            cout << "Enter Initial Balance: " << endl;
            cin >> bal;
            cout << "Enter Term Duration (months): " << endl;
            cin >> duration;
            fixed[total].create(no, name, bal, duration);
            all[total] = &fixed[total];
            total++;
        }
        else if (choice == 4)
        {
            int no;
            float amt;
            cout << "Enter Account Number: " << endl;
            cin >> no;
            bool found = false;
            for (int i = 0; i < total; i++)
            {
                if (all[i]->getAccNo() == no)
                {
                    cout << "Enter Amount to Deposit: " << endl;
                    cin >> amt;
                    all[i]->deposit(amt);
                    found = true;
                    break;
                }
            }
            if (!found)
                cout << "Account not found." << endl;
        }
        else if (choice == 5)
        {
            int no;
            float amt;
            cout << "Enter Account Number: " << endl;
            cin >> no;
            bool found = false;
            for (int i = 0; i < total; i++)
            {
                if (all[i]->getAccNo() == no)
                {
                    cout << "Enter Amount to Withdraw: " << endl;
                    cin >> amt;
                    all[i]->withdraw(amt);
                    found = true;
                    break;
                }
            }
            if (!found)
                cout << "Account not found." << endl;
        }
        else if (choice == 6)
        {
            for (int i = 0; i < total; i++)
            {
                cout << "--- Account [" << i << "] ---" << endl;
                all[i]->display();
            }
        }
        else if (choice == 7)
        {
            for (int i = 0; i < total; i++)
            {
                all[i]->display();
                all[i]->calculateInterest();

            }
        }
        else if (choice == 8)
        {
            for (int i = 0; i < total; i++)
            {
                all[i]->displayBalance();
            }
        }
        else if (choice == 9)
        {
            cout << "Thank you for using the Banking System." << endl;
        }
        else
        {
            cout << "Invalid choice!" << endl;
        }

    } while (choice != 9);

    return 0;
}
