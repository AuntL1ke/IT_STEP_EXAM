#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <iostream>

class Product {
protected:
    std::string name;
    std::string category;
    double price;
    int quantity;

public:
    Product(std::string n, std::string cat, double p, int q)
        : name(n), category(cat), price(p), quantity(q) {}

    virtual ~Product() {}

    std::string getName() const { return name; }
    std::string getCategory() const { return category; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }

    void setQuantity(int newQuantity) { quantity = newQuantity; }

    virtual void displayProduct() const = 0;
};

class GroceryProduct : public Product {
    std::string expirationDate;

public:
    GroceryProduct(std::string n, std::string expDate, std::string cat, double p, int q)
        : Product(n, cat, p, q), expirationDate(expDate) {}

    void displayProduct() const override {
        std::cout << "Name: " << name << ", Category: " << category << ", Price: " << price << ", Quantity: " << quantity << ", Expiration Date: " << expirationDate << std::endl;
    }
};

#endif // PRODUCT_H
#pragma once
