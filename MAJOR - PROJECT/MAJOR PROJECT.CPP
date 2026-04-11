#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cctype>
#include <algorithm>
using namespace std;

// ---------- Date Validation ----------
bool isValidDate(string date) {
    if (date.length() != 10) return false;

    if (!isdigit(date[0]) || !isdigit(date[1]) || date[2] != '-' ||
        !isdigit(date[3]) || !isdigit(date[4]) || date[5] != '-' ||
        !isdigit(date[6]) || !isdigit(date[7]) ||
        !isdigit(date[8]) || !isdigit(date[9]))
        return false;

    int d = stoi(date.substr(0,2));
    int m = stoi(date.substr(3,2));

    return (d >= 1 && d <= 31 && m >= 1 && m <= 12);
}

// ---------- Inline ----------
inline float calculateBalance(float income, float expense) {
    return income - expense;
}

// ---------- Base Class ----------
class Transaction {
protected:
    float amount;
    string date;

public:
    Transaction(float amt = 0, string d = "") {
        amount = amt;
        date = d;
    }

    virtual void display() = 0;
    virtual string getType() = 0;
    virtual string getCategory() = 0;

    float getAmount() { return amount; }
    string getDate() { return date; }

    virtual ~Transaction() {}
};

// ---------- Income ----------
class Income : public Transaction {
    string source;

public:
    Income(float amt, string d, string src)
        : Transaction(amt, d), source(src) {}

    void display() {
        cout << left << setw(10) << "Income"
             << setw(15) << date
             << setw(20) << source
             << right << setw(10) << fixed << setprecision(2) << amount << endl;
    }

    string getType() { return "Income"; }
    string getCategory() { return source; }
};

// ---------- Expense ----------
class Expense : public Transaction {
    string category;

public:
    Expense(float amt, string d, string cat)
        : Transaction(amt, d), category(cat) {}

    void display() {
        cout << left << setw(10) << "Expense" << setw(15) << date << setw(20) << category << right << setw(10) << fixed << setprecision(2) << amount << endl;
    }

    string getType() { return "Expense"; }
    string getCategory() { return category; }
};

// ---------- Finance Manager ----------
class FinanceManager {
    vector<Transaction*> records;
    float budget = 0;

public:

    void setBudget() {
        cout << "Enter Monthly Budget: ";
        cin >> budget;
        cout << "Budget Set!\n";
    }

    void addIncome() {
        float amt;
        string date, source;

        cout << "Enter Amount: ";
        cin >> amt;
        if (amt < 0) throw invalid_argument("Invalid amount!");

        cout << "Enter Date (DD-MM-YYYY): ";
        cin >> date;
        if (!isValidDate(date))
            throw invalid_argument("Invalid date!");

        cin.ignore();
        cout << "Enter Source: ";
        getline(cin, source);

        records.push_back(new Income(amt, date, source));
    }

    void addExpense() {
        if (budget == 0)
            cout << "Please set budget first!\n";

        float amt;
        string date, category;

        cout << "Enter Amount: ";
        cin >> amt;
        if (amt < 0) throw invalid_argument("Invalid amount!");

        cout << "Enter Date (DD-MM-YYYY): ";
        cin >> date;
        if (!isValidDate(date))
            throw invalid_argument("Invalid date!");

        cin.ignore();
        cout << "Enter Category: ";
        getline(cin, category);

        records.push_back(new Expense(amt, date, category));
    }

    void showAll() {
        cout << "\n===================== TRANSACTIONS ====================\n";

        cout << left << setw(10) << "Type" << setw(15) << "Date" << setw(20) << "Category" << right << setw(10) << "Amount" << endl;

        cout << "---------------------------------------------------------\n";

        for (auto t : records)
            t->display();
    }

    void showDailyReport() {
        string inputDate;
        float income = 0, expense = 0;

        cout << "Enter Date (DD-MM-YYYY): ";
        cin >> inputDate;

        if (!isValidDate(inputDate))
            throw invalid_argument("Invalid date!");

        for (auto t : records) {
            if (t->getDate() == inputDate) {
                if (t->getType() == "Income")
                    income += t->getAmount();
                else
                    expense += t->getAmount();
            }
        }

        cout << "\n========== DAILY REPORT ==========\n";
        cout << "Income  : " << income << endl;
        cout << "Expense : " << expense << endl;
        cout << "Balance : " << income - expense << endl;

        if (expense > income)
            cout << "Overspending!\n";
        else
            cout << "Balanced\n";
    }

    void showWeeklyReport() {
        float income[6] = {0}, expense[6] = {0};

        for (auto t : records) {
            int day = stoi(t->getDate().substr(0,2));
            int week = (day - 1) / 7 + 1;

            if (t->getType() == "Income")
                income[week] += t->getAmount();
            else
                expense[week] += t->getAmount();
        }

        cout << "\n=========== WEEKLY REPORT ===========\n";

        for (int i = 1; i <= 5; i++) {
            if (income[i] == 0 && expense[i] == 0)
                continue;

            cout << "Week " << i << " -> Income: " << income[i]
                 << " Expense: " << expense[i]
                 << " Balance: " << income[i] - expense[i] << endl;

            if (expense[i] > income[i])
                cout << " Overspending!\n";
            else
                cout << " Balanced\n";
        }
    }

    void monthlySummary() {
        float income = 0, expense = 0;

        for (auto t : records) {
            if (t->getType() == "Income")
                income += t->getAmount();
            else
                expense += t->getAmount();
        }

        cout << "\n=========== MONTHLY SUMMARY ===========\n";
        cout << "Income  : " << income << endl;
        cout << "Expense : " << expense << endl;
        cout << "Balance : " << calculateBalance(income, expense) << endl;

        if (expense > income)
            cout << "Overspending!\n";
        else
            cout << "Balanced\n";
    }

    void categoryReport() {
        vector<string> categories;
        vector<float> totals;

        for (auto t : records) {
            if (t->getType() == "Expense") {
                string cat = t->getCategory();
                bool found = false;

                for (int i = 0; i < categories.size(); i++) {
                    if (categories[i] == cat) {
                        totals[i] += t->getAmount();
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    categories.push_back(cat);
                    totals.push_back(t->getAmount());
                }
            }
        }

        cout << "\n======= CATEGORY REPORT =======\n";
        for (int i = 0; i < categories.size(); i++) {
            cout << categories[i] << " : " << totals[i] << endl;
        }
    }

    void showMonthWiseReport() {
        int option;
        cout << "\n1. All Months\n2. Specific Month\nEnter option: ";
        cin >> option;

        float income[13] = {0}, expense[13] = {0};

        string months[] = {"", "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};

        for (auto t : records) {
            int m = stoi(t->getDate().substr(3,2));

            if (t->getType() == "Income")
                income[m] += t->getAmount();
            else
                expense[m] += t->getAmount();
        }

        if (option == 1) {
            cout << "\n=========== ALL MONTH REPORT ===========\n";

            for (int i = 1; i <= 12; i++) {
                if (income[i] == 0 && expense[i] == 0) continue;

                cout << months[i] << " -> Income: " << income[i] << " Expense: " << expense[i] << " Balance: " << income[i] - expense[i] << endl;

                if (expense[i] > income[i])
                    cout << " Overspending!\n";
                else
                    cout << " Balanced\n";
            }
        }
        else if (option == 2) {
            string input;
            cout << "Enter Month (Jan/Feb/...): ";
            cin >> input;

            transform(input.begin(), input.end(), input.begin(), ::tolower);

            int found = -1;

            for (int i = 1; i <= 12; i++) {
                string m = months[i];
                transform(m.begin(), m.end(), m.begin(), ::tolower);

                if (m == input) {
                    found = i;
                    break;
                }
            }

            if (found == -1) {
                cout << "Invalid month!\n";
                return;
            }

            cout << "\n====== " << months[found] << " REPORT ======\n";
            cout << "Income  : " << income[found] << endl;
            cout << "Expense : " << expense[found] << endl;
            cout << "Balance : " << income[found] - expense[found] << endl;

            if (expense[found] > income[found])
                cout << "Overspending!\n";
            else
                cout << "Balanced\n";
        }
        else {
            cout << "Invalid option!\n";
        }
    }

    void saveToFile() {
        ofstream file("finance.txt");

        for (auto t : records) {
            file << t->getType() << " "
                 << t->getDate() << " "
                 << t->getCategory() << " "
                 << t->getAmount() << endl;
        }

        file.close();
        cout << "Saved!\n";
    }

    ~FinanceManager() {
        for (auto t : records)
            delete t;
    }
};

// ---------- MAIN ----------
int main() {
    FinanceManager fm;
    int choice;

    do {
        cout << "\n========= MENU =========\n";
        cout << "1. Set Budget\n";
        cout << "2. Add Income\n";
        cout << "3. Add Expense\n";
        cout << "4. Show Transactions\n";
        cout << "5. Daily Report\n";
        cout << "6. Weekly Report\n";
        cout << "7. Monthly Summary\n";
        cout << "8. Category Report\n";
        cout << "9. Month-wise Report\n";
        cout << "10. Save to File\n";
        cout << "11. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        try {
            switch (choice) {
                case 1: fm.setBudget(); break;
                case 2: fm.addIncome(); break;
                case 3: fm.addExpense(); break;
                case 4: fm.showAll(); break;
                case 5: fm.showDailyReport(); break;
                case 6: fm.showWeeklyReport(); break;
                case 7: fm.monthlySummary(); break;
                case 8: fm.categoryReport(); break;
                case 9: fm.showMonthWiseReport(); break;
                case 10: fm.saveToFile(); break;
                case 11: cout << "Exiting...\n"; break;
                default: cout << "Invalid choice!\n";
            }
        }
        catch (exception &e) {
            cout << "Error: " << e.what() << endl;
        }

    } while (choice != 11);

    return 0;
}
