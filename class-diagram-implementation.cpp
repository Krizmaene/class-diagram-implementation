#include <iostream>
#include <string>
using namespace std;

class Product {
public: 
    string productId;
    string productName;
    double productPrice;

    Product(): productId(""), productName(""), productPrice(0.0) {} //Default constructor

    Product (string id, string name, double price)
    : productId(id), productName(name), productPrice(price) {} //Parameterized constructor

};

void displayProducts(Product products[], int size) {
        cout << "\nAvailable Products: " << endl;
        cout << "Product ID\tName\t\tPrice" << endl;
        for (int i = 0; i < size; i++) {
        cout << products[i].productId << "\t\t" << products[i].productName << "\t" << products[i].productPrice << endl;
        } 
    }

class ShoppingCart {
private: 
    Product items[10];
    int quantities[10];
    int itemCount;
    double totalAmount;

public: 
    ShoppingCart(): itemCount(0), totalAmount(0.0) {} //Constructor

    void addItem(Product product, int quantity) {
        if (itemCount < 10) {
            items[itemCount] = product;
            quantities[itemCount] = quantity;
            totalAmount += product.productPrice * quantity;
            itemCount++;
        } else {
            cout << "CART IS FULL! Cannot add more items." << endl;
        }
    }

    void viewCart() {
        cout << "\nShopping Cart Items: " << endl;
        cout << "Product ID\tName\t\tPrice\t\tQuantity" << endl;
        for (int i = 0; i < itemCount; i++) {
            cout << items[i].productId << "\t\t" << items[i].productName << "\t\t" << items[i].productPrice << "\t\t" << quantities[i] << endl;
        }
        cout << "\nTotal Amount: P" << totalAmount << endl;
    }
    bool isEmpty() {
        return itemCount == 0;
    }
    double getTotalAmount () {
        return totalAmount;
    }
    void clearCart() {
        itemCount = 0;
        totalAmount = 0.0;
    }
    int getItemCount() {
        return itemCount;
    }
    Product getItem(int index) {
        return items[index];
    }
    int getQuantity(int index) {
        return quantities[index];
    }
};

class Order {
private:
    string orderId;
    double totalAmount;
    Product orderedItems[10];
    int orderedQuantities[10];
    int orderedItemCount;

public:
    Order(string id, double total, ShoppingCart &cart) : orderId(id), totalAmount(total), orderedItemCount(cart.getItemCount()) {
        // Save the cart's items and quantities into the order before clearing the cart
        for (int i = 0; i < orderedItemCount; i++) {
            orderedItems[i] = cart.getItem(i);
            orderedQuantities[i] = cart.getQuantity(i);
        }
    }

    void orderDetails(ShoppingCart &cart) {
        cout << "Order ID: " << orderId << endl;
        cout << "Total Amount: P" << totalAmount << endl;
        cout << "Order Details: " << endl;
        cout << "Product ID\tName\t\tPrice\t\tQuantity" << endl;
        for (int i = 0; i < orderedItemCount; i++) {
            cout << orderedItems[i].productId << "\t\t" << orderedItems[i].productName << "\t\t" << orderedItems[i].productPrice << "\t\t" << orderedQuantities[i] << endl;
        }
    }
};

int main() {
    Product products[5] {
        Product("ABC", "Powerbank", 700),
        Product("DEF", "Speaker", 2500),
        Product("GHI", "Headphones", 3000),
        Product("JKL", "Keyboard", 2000),
        Product("MNO", "Mouse", 1500)
    };
    
    ShoppingCart cart;
    Order *order = nullptr;
    int choice, productIndex, quantity;
    string productId, continueAdding, checkoutChoice, orderId;

    do{ 
        cout << "\nM E N U: " << endl;
        cout << "1. View Products" << endl;
        cout << "2. View Shopping Cart" << endl;
        cout << "3. View Order" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: " ;
        cin >> choice;

        switch (choice) {
            case 1: {
                displayProducts(products, 5);

                do {
                    cout << "\nEnter the Product ID of the item to add to the cart: ";
                    cin >> productId;

                    productIndex = -1;
                    for (int i = 0; i < 5; i++) {
                        if (products[i].productId == productId) {
                            productIndex = i;
                            break;
                        }
                    }

                    if (productIndex != -1) {
                        cout << "Enter quantity: ";
                        cin >> quantity;
                        cart.addItem(products[productIndex], quantity);
                    } else {
                        cout << "Invalid Product ID!" << endl;
                    }

                    cout << "\nDo you want to add another product? (Y/N): ";
                    cin >> continueAdding;
                } while (continueAdding == "Y" || continueAdding == "y");
                break;
            }

            case 2: {
                if (cart.isEmpty()) {
                    cout << "Your shopping cart is empty." << endl;
                } else {
                    cart.viewCart();

                    cout << "\nDo you want to checkout? (Y/N): ";
                    cin >> checkoutChoice;

                    if (checkoutChoice == "Y" || checkoutChoice == "y") {
                        cout << "\nEnter Order ID: ";
                        cin >> orderId;
                        order = new Order(orderId, cart.getTotalAmount(), cart);
                        order->orderDetails(cart);
                        cart.clearCart();
                    }
                }
                break;
            }

            case 3: {
                if (order != nullptr) {
                    order->orderDetails(cart);
                } else {
                    cout << "No orders have been placed yet." << endl;
                }
                break;
            }

            case 4: {
                cout << "Exiting..." << endl;
                break;
            }

            default: 
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}