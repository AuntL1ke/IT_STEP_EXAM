#include "header.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <limits>
#include <algorithm>
#include <map>

using namespace std;

void displayMenu() {
    cout << "\n���� ��������� ����������:" << endl;
    cout << "1. ������ �������" << endl;
    cout << "2. �������� �� ��������" << endl;
    cout << "3. �������� �������� � ����" << endl;
    cout << "4. ����������� �������� � �����" << endl;
    cout << "5. �������� �������� �� ����������" << endl;
    cout << "6. ����� ��������" << endl;
    cout << "7. �������� �������" << endl;
    cout << "8. ������� �������" << endl;
    cout << "9. �����" << endl;
    cout << "��� ����: ";
}

bool productExists(const vector<Product*>& products, const string& name) {
    return any_of(products.begin(), products.end(), [&name](const Product* product) {
        return product->getName() == name;
        });
}

void addProduct(vector<Product*>& products) {
    string name, category, expirationDate;
    double price;
    int quantity;

    cout << "������ ����� ��������: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ������� �����
    getline(cin, name);

    if (productExists(products, name)) {
        cout << "������� � ����� ������ ��� ����." << endl;
        return;
    }

    cout << "������ �������� ��������: ";
    getline(cin, category);

    cout << "������ ����� ���������� ��������: ";
    getline(cin, expirationDate);

    cout << "������ ���� ��������: ";
    cin >> price;

    cout << "������ ������� ��������: ";
    cin >> quantity;

    products.push_back(new GroceryProduct(name, expirationDate, category, price, quantity));
    cout << "������� ������ ������!" << endl;
}

void displayAllProducts(const vector<Product*>& products) {
    for (const auto& product : products) {
        product->displayProduct();
    }
}

void saveProductsToFile(const vector<Product*>& products, const string& filename) {
    ofstream outFile(filename);
    for (const auto& product : products) {
        if (outFile.is_open()) {
            outFile << product->getName() << ", " << product->getCategory() << ", " << product->getPrice() << ", " << product->getQuantity() << endl;
        }
    }
    outFile.close();
}

void loadProductsFromFile(vector<Product*>& products, const string& filename) {
    ifstream inFile(filename);
    string name, category, expirationDate;
    double price;
    int quantity;

    while (getline(inFile, name, ',')) {
        getline(inFile, category, ',');
        getline(inFile, expirationDate, ',');
        inFile >> price;
        inFile.ignore(numeric_limits<streamsize>::max(), ',');
        inFile >> quantity;
        inFile.ignore(numeric_limits<streamsize>::max(), '\n');

        products.push_back(new GroceryProduct(name, expirationDate, category, price, quantity));
    }
    inFile.close();
}

void displayProductsByCategory(const vector<Product*>& products) {
    map<string, vector<Product*>> categorizedProducts;
    for (const auto& product : products) {
        categorizedProducts[product->getCategory()].push_back(product);
    }

    for (const auto& pair : categorizedProducts) {
        cout << "��������: " << pair.first << endl;
        for (const auto& product : pair.second) {
            product->displayProduct();
        }
    }
}

void searchProduct(const vector<Product*>& products, const string& searchName) {
    auto found = find_if(products.begin(), products.end(), [&searchName](const Product* product) {
        return product->getName() == searchName;
        });

    if (found != products.end()) {
        (*found)->displayProduct();
    }
    else {
        cout << "������� � ������ '" << searchName << "' �� ��������." << endl;
    }
}

void deleteProduct(vector<Product*>& products, const string& nameToDelete) {
    auto found = find_if(products.begin(), products.end(), [&nameToDelete](const Product* product) {
        return product->getName() == nameToDelete;
        });

    if (found != products.end()) {
        delete* found;
        products.erase(found);
        cout << "������� '" << nameToDelete << "' ��������." << endl;
    }
    else {
        cout << "������� � ������ '" << nameToDelete << "' �� ��������." << endl;
    }
}

void sellProduct(vector<Product*>& products, const string& name, int quantity) {
    auto found = find_if(products.begin(), products.end(), [&name](const Product* product) {
        return product->getName() == name;
        });

    if (found != products.end()) {
        if ((*found)->getQuantity() >= quantity) {
            (*found)->setQuantity((*found)->getQuantity() - quantity);
            cout << "������� �������." << endl;
            cout << "�� ������ " << name << " �� ���� " << (*found)->getPrice() * quantity << endl;
        }
        else {
            cout << "���������� ������� �� �����." << endl;
        }
    }
    else {
        cout << "������� � ������ '" << name << "' �� ��������." << endl;
    }
}

int main() {
    vector<Product*> products;
    int choice;
    setlocale(LC_ALL, "ru");
    while (1) {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            addProduct(products);
            break;
        case 2:
            displayAllProducts(products);
            break;
        case 3:
            saveProductsToFile(products, "products.txt");
            cout << "�������� ��������� � ����." << endl;
            break;
        case 4:
            loadProductsFromFile(products, "products.txt");
            cout << "�������� ����������� � �����." << endl;
            break;
        case 5:
            displayProductsByCategory(products);
            break;
        case 6:
        {
            cout << "������ ����� �������� ��� ������: ";
            string searchName;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, searchName);
            searchProduct(products, searchName);
        }
        break;
        case 7:
        {
            cout << "������ ����� �������� ��� ���������: ";
            string nameToDelete;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, nameToDelete);
            deleteProduct(products, nameToDelete);
        }
        break;
        case 8:
        {
            cout << "������ ����� �������� ��� �������: ";
            string name;
            int quantity;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, name);
            cout << "������ ������� ��� �������: ";
            cin >> quantity;
            sellProduct(products, name, quantity);
        }
        break;
        case 9:
            goto exit_loop;
        default:
            cout << "������������ ����. ��������� �� ���." << endl;
        }
    }
exit_loop:

    // �������� ������� ���'��
    for (auto& product : products) {
        delete product;
    }
    products.clear();

    return 0;
}
