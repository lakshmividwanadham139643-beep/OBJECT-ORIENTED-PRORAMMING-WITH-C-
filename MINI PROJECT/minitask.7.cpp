#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Product {
public:
    int id;
    char name[50];
    int quantity;
    float price;

    void input() {
        cout << "Enter Product ID: ";
        cin >> id;
        cout << "Enter Product Name: ";
        cin.ignore();
        cin.getline(name, 50);
        cout << "Enter Quantity: ";
        cin >> quantity;
        cout << "Enter Price: ";
        cin >> price;
    }

    void display() {
        cout << "\nID: " << id;
        cout << "\nName: " << name;
        cout << "\nQuantity: " << quantity;
        cout << "\nPrice: " << price << endl;
    }
};

// Function to add product
void addProduct() {
    ofstream file("inventory.dat", ios::binary | ios::app);

    if (!file) {
        cout << "Error opening file!\n";
        return;
    }

    Product p;
    p.input();

    file.write((char*)&p, sizeof(p));
    file.close();

    cout << "Product added successfully!\n";
}

// Function to display products
void displayProducts() {
    ifstream file("inventory.dat", ios::binary);

    if (!file) {
        cout << "Error opening file!\n";
        return;
    }

    Product p;
    cout << "\n--- Product List ---\n";

    while (file.read((char*)&p, sizeof(p))) {
        p.display();
        cout << "-------------------\n";
    }

    file.close();
}

// Function to update product
void updateProduct() {
    fstream file("inventory.dat", ios::binary | ios::in | ios::out);

    if (!file) {
        cout << "Error opening file!\n";
        return;
    }

    int searchId;
    cout << "Enter Product ID to update: ";
    cin >> searchId;

    Product p;
    bool found = false;

    while (file.read((char*)&p, sizeof(p))) {
        if (p.id == searchId) {
            cout << "Product found!\n";
            p.display();

            cout << "\nEnter new details:\n";
            p.input();

            int pos = -1 * sizeof(p);
            file.seekp(pos, ios::cur);
            file.write((char*)&p, sizeof(p));

            cout << "Product updated successfully!\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Product not found!\n";
    }

    file.close();
}

// Main menu
int main() {
    int choice;

    do {
        cout << "\n--- Inventory File System ---\n";
        cout << "1. Add Product\n";
        cout << "2. Display Products\n";
        cout << "3. Update Product\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addProduct();
            break;
        case 2:
            displayProducts();
            break;
        case 3:
            updateProduct();
            break;
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 4);

    return 0;
}
