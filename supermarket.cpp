#include "header.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <limits>
#include <algorithm>
#include <map>

using namespace std;

void displayMenu() {
    cout << "\nМеню управління продуктами:" << endl;
    cout << "1. Додати продукт" << endl;
    cout << "2. Показати всі продукти" << endl;
    cout << "3. Зберегти продукти у файл" << endl;
    cout << "4. Завантажити продукти з файлу" << endl;
    cout << "5. Показати продукти за категоріями" << endl;
    cout << "6. Пошук продукту" << endl;
    cout << "7. Видалити продукт" << endl;
    cout << "8. Продати продукт" << endl;
    cout << "9. Вийти" << endl;
    cout << "Ваш вибір: ";
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

    cout << "Введіть назву продукту: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Чистимо буфер
    getline(cin, name);

    if (productExists(products, name)) {
        cout << "Продукт з такою назвою вже існує." << endl;
        return;
    }

    cout << "Введіть категорію продукту: ";
    getline(cin, category);

    cout << "Введіть термін споживання продукту: ";
    getline(cin, expirationDate);

    cout << "Введіть ціну продукту: ";
    cin >> price;

    cout << "Введіть кількість продукту: ";
    cin >> quantity;

    products.push_back(new GroceryProduct(name, expirationDate, category, price, quantity));
    cout << "Продукт додано успішно!" << endl;
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
        cout << "Категорія: " << pair.first << endl;
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
        cout << "Продукт з назвою '" << searchName << "' не знайдено." << endl;
    }
}

void deleteProduct(vector<Product*>& products, const string& nameToDelete) {
    auto found = find_if(products.begin(), products.end(), [&nameToDelete](const Product* product) {
        return product->getName() == nameToDelete;
        });

    if (found != products.end()) {
        delete* found;
        products.erase(found);
        cout << "Продукт '" << nameToDelete << "' видалено." << endl;
    }
    else {
        cout << "Продукт з назвою '" << nameToDelete << "' не знайдено." << endl;
    }
}

void sellProduct(vector<Product*>& products, const string& name, int quantity) {
    auto found = find_if(products.begin(), products.end(), [&name](const Product* product) {
        return product->getName() == name;
        });

    if (found != products.end()) {
        if ((*found)->getQuantity() >= quantity) {
            (*found)->setQuantity((*found)->getQuantity() - quantity);
            cout << "Продукт продано." << endl;
            cout << "Ви купили " << name << " на суму " << (*found)->getPrice() * quantity << endl;
        }
        else {
            cout << "Недостатня кількість на складі." << endl;
        }
    }
    else {
        cout << "Продукт з назвою '" << name << "' не знайдено." << endl;
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
            cout << "Продукти збережено у файл." << endl;
            break;
        case 4:
            loadProductsFromFile(products, "products.txt");
            cout << "Продукти завантажено з файлу." << endl;
            break;
        case 5:
            displayProductsByCategory(products);
            break;
        case 6:
        {
            cout << "Введіть назву продукту для пошуку: ";
            string searchName;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, searchName);
            searchProduct(products, searchName);
        }
        break;
        case 7:
        {
            cout << "Введіть назву продукту для видалення: ";
            string nameToDelete;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, nameToDelete);
            deleteProduct(products, nameToDelete);
        }
        break;
        case 8:
        {
            cout << "Введіть назву продукту для продажу: ";
            string name;
            int quantity;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, name);
            cout << "Введіть кількість для продажу: ";
            cin >> quantity;
            sellProduct(products, name, quantity);
        }
        break;
        case 9:
            goto exit_loop;
        default:
            cout << "Неправильний вибір. Спробуйте ще раз." << endl;
        }
    }
exit_loop:

    // Очищення виділеної пам'яті
    for (auto& product : products) {
        delete product;
    }
    products.clear();

    return 0;
}
