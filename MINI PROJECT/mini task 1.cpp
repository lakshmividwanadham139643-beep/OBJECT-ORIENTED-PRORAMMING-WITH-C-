#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int n, quantity, paymentChoice;
    float price, total = 0, gst, finalAmount;
    string itemName, paymentMode;

    cout << "==============================" << endl;
    cout << "      SMART BILLING SYSTEM    " << endl;
    cout << "==============================" << endl;

    cout << "Enter number of items: ";
    cin >> n;

    for(int i = 1; i <= n; i++) {
        cout << "\nItem " << i << endl;
        cout << "Enter item name: ";
        cin >> itemName;
        cout << "Enter price: ";
        cin >> price;
        cout << "Enter quantity: ";
        cin >> quantity;

        total = total + price * quantity;
    }

    cout << "\nSelect Payment Method" << endl;
    cout << "1. Cash" << endl;
    cout << "2. UPI" << endl;
    cout << "3. Card" << endl;
    cout << "Enter choice: ";
    cin >> paymentChoice;

    if(paymentChoice == 1)
        paymentMode = "Cash";
    else if(paymentChoice == 2)
        paymentMode = "UPI";
    else if(paymentChoice == 3)
        paymentMode = "Card";
    else
        paymentMode = "Invalid";


    gst = total * 0.18;
    finalAmount = total + gst;

    cout << fixed << setprecision(2);

    cout << "\n----------------------------------" << endl;
    cout <<"------------BILL------------------" << endl;
    cout << left << setw(15) << "Payment Mode" << ": " << paymentMode << endl;
    cout << left << setw(15) << "Total Amount" << ": Rs. " << total << endl;
    cout << left << setw(15) << "GST (18%)"    << ": Rs. " << gst << endl;
    cout << left << setw(15) << "Final Bill"   << ": Rs. " << finalAmount << endl;
    cout << "----------------------------------" << endl;

    cout << "\nThank you! Visit again " << endl;

    return 0;
}
