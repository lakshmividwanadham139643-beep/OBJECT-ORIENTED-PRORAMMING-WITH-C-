#include <iostream>
using namespace std;
#define SQUARE(x) ((x)*(x))

inline int cube(int x) { return x*x*x; }

class MathTool {

public:

    int factorial(int n);
    int power(int base, int exp = 2);
    bool isPrime(int n) const;
    int digitSum(int n);

    int add(int a, int b);
    float add(float a, float b);

    void swapNum(int &a, int &b);
};

int MathTool::factorial(int n) {
    int fact = 1;
    for(int i=1; i<=n; i++)
        fact *= i;
    return fact;
}

int MathTool::power(int base, int exp) {
    int result = 1;
    for(int i=1; i<=exp; i++)
        result *= base;
    return result;
}

bool MathTool::isPrime(int n) const {
    if(n<=1) return false;
    for(int i=2; i<=n/2; i++)
        if(n%i==0) return false;
    return true;
}

int MathTool::digitSum(int n) {
    int sum = 0;
    while(n>0) {
        sum += n%10;
        n/=10;
    }
    return sum;
}

int MathTool::add(int a, int b) {
    return a+b;
}

float MathTool::add(float a, float b) {
    return a+b;
}

void MathTool::swapNum(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}


int main() {
    MathTool obj;
    int choice, n, a, b;

    do {
        cout << "\n--- MATH TOOLKIT MENU ---\n";
        cout << "1. Factorial\n";
        cout << "2. Power\n";
        cout << "3. Prime Check\n";
        cout << "4. Digit Sum\n";
        cout << "5. Add \n";
        cout << "6. Swap \n";
        cout << "7. Square&cube\n";
        cout << "8. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter number: ";
                cin >> n;
                cout << "Factorial = " << obj.factorial(n);
                break;

            case 2:
                cout << "Enter base and exponent: ";
                cin >> a >> b;
                cout << "Power = " << obj.power(a,b);
                break;

            case 3:
                cout << "Enter number: ";
                cin >> n;
                cout << (obj.isPrime(n) ? "Prime" : "Not Prime");
                break;

            case 4:
                cout << "Enter number: ";
                cin >> n;
                cout << "Digit Sum = " << obj.digitSum(n);
                break;

            case 5:
                cout << "Enter two integers: ";
                cin >> a >> b;
                cout << "Sum (int) = " << obj.add(a,b);
                break;

            case 6:
                cout << "Enter two numbers: ";
                cin >> a >> b;
                obj.swapNum(a,b);
                cout << "After Swap: " << a << " " << b;
                break;

            case 7:
                cout << "Enter number: ";
                cin >> n;
                cout << "Square (Macro) = " << SQUARE(n) << endl;
                cout << "Cube (Inline) = " << cube(n);
                break;
            case 8:
                cout << "program Ended.\n";
                break;
            default:
                cout<< "Invalid choice!";
        }

    } while(choice !=8);

    return 0;
}
