#include <iostream>
using namespace std;

class Employee {
public:
    string name;
    float salary;

    Employee(string n, float s) {
        name = n;
        salary = s;
    }

    float calculateSalary() {
        return salary;
    }
};

// Manager Class
class Manager : public Employee {
public:
    float bonus;

    Manager(string n, float s, float b) : Employee(n, s) {
        bonus = b;
    }

    float totalSalary() {
        return salary + bonus;
    }
};

// Worker Class
class Worker : public Employee {
public:
    float overtime;

    Worker(string n, float s, float o) : Employee(n, s) {
        overtime = o;
    }

    float totalSalary() {
        return salary + overtime;
    }
};

int main() {
    int choice;

    do {
        cout << "\n1. Manager\n2. Worker\n3. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        if(choice == 1) {
            string name;
            float salary, bonus;

            cout << "Enter Name: ";
            cin >> name;
            cout << "Enter Salary: ";
            cin >> salary;
            cout << "Enter Bonus: ";
            cin >> bonus;

            Manager m(name, salary, bonus);
            cout << "Total Salary: " << m.totalSalary();
        }

        else if(choice == 2) {
            string name;
            float salary, overtime;

            cout << "Enter Name: ";
            cin >> name;
            cout << "Enter Salary: ";
            cin >> salary;
            cout << "Enter Overtime: ";
            cin >> overtime;

            Worker w(name, salary, overtime);
            cout << "Total Salary: " << w.totalSalary();
        }

        else if(choice != 3) {
            cout << "Invalid choice!";
        }

    } while(choice != 3);

    return 0;
}
