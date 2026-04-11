#include <iostream>
#include <vector>
#include <stdexcept> // for standard exceptions
using namespace std;

// ---------- Function Template ----------
template <typename T>
T safeDivide(T a, T b) {
    if (b == 0) {
        throw runtime_error("Error: Division by zero!");
    }
    return a / b;
}

// ---------- Class Template ----------
template <typename T>
class DataProcessor {
private:
    vector<T> data;  // STL container

public:
    // Add data with validation
    void addData(T value) {
        if (value < 0) {
            throw invalid_argument("Error: Negative values not allowed!");
        }
        data.push_back(value);
    }

    // Process data (divide all elements by a number)
    void processData(T divisor) {
        try {
            for (size_t i = 0; i < data.size(); i++) {
                data[i] = safeDivide(data[i], divisor); // may throw
            }
        }
        catch (...) {
            // Exception propagation
            throw;
        }
    }

    // Display data
    void display() {
        cout << "Processed Data: ";
        for (T val : data) {
            cout << val << " ";
        }
        cout << endl;
    }
};

// ---------- Main Function ----------
int main() {
    DataProcessor<float> dp;

    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    try {
        if (n <= 0) {
            throw invalid_argument("Error: Size must be positive!");
        }

        float value;
        cout << "Enter elements:\n";
        for (int i = 0; i < n; i++) {
            cin >> value;
            dp.addData(value); // may throw
        }

        float divisor;
        cout << "Enter divisor: ";
        cin >> divisor;

        dp.processData(divisor); // may throw

        dp.display();
    }

    // ---------- Multiple Catch Blocks ----------
    catch (invalid_argument &e) {
        cout << e.what() << endl;
    }
    catch (runtime_error &e) {
        cout << e.what() << endl;
    }
    catch (exception &e) {  // standard exception
        cout << "Standard Exception: " << e.what() << endl;
    }
    catch (...) {
        cout << "Unknown error occurred!" << endl;
    }

    return 0;
}
