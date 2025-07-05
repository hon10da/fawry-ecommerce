#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Product {
public:
    string name;
    double price;
    int quantity;
    bool isExpired;
    bool needsShipping;
    double weight;

    Product(string n, double p, int q, bool expired, bool shipping, double w)
        : name(n), price(p), quantity(q), isExpired(expired), needsShipping(shipping), weight(w) {}
};

class CartItem {
public:
    Product* product;
    int quantity;

    CartItem(Product* p, int q) : product(p), quantity(q) {}
};

class Cart {
private:
    vector<CartItem> items;

public:
    void addItem(Product* p, int qty) {
        if (p->isExpired || p->quantity < qty) {
            cout << "Error: Product unavailable or expired: " << p->name << endl;
        } else {
            items.push_back(CartItem(p, qty));
            p->quantity -= qty; // Reduce from stock directly
        }
    }

    bool isEmpty() {
        return items.empty();
    }

    void checkout(double& customerBalance) {
        if (isEmpty()) {
            cout << "Cart is empty!\n";
            return;
        }

        double subtotal = 0;
        double shipping = 0;
        double totalWeight = 0;

        for (CartItem item : items) {
            subtotal += item.product->price * item.quantity;
            if (item.product->needsShipping) {
                shipping += 10 * item.quantity;
                totalWeight += item.product->weight * item.quantity;
            }
        }

        double total = subtotal + shipping;

        if (customerBalance < total) {
            cout << "Insufficient balance!\n";
            return;
        }

        customerBalance -= total;

        if (shipping > 0) {
            cout << "** Shipping Details **\n";
            for (CartItem item : items) {
                if (item.product->needsShipping) {
                    cout << item.quantity << "x " << item.product->name
                         << " " << int(item.product->weight * 1000) << "g\n";
                }
            }
            cout << "Total package weight: " << totalWeight << "kg\n\n";
        }

        cout << "** Checkout Receipt **\n";
        for (CartItem item : items) {
            double totalPrice = item.product->price * item.quantity;
            cout << item.quantity << "x " << item.product->name
                 << "\t" << totalPrice << "\n";
        }
        cout << "----------------------\n";
        cout << "Subtotal\t" << subtotal << "\n";
        cout << "Shipping\t" << shipping << "\n";
        cout << "Total\t\t" << total << "\n";
        cout << "Remaining Balance\t" << customerBalance << "\n";
    }
};

int main() {
    // Predefined product list
    vector<Product> products = {
        Product("Cheese", 100, 10, false, true, 0.2),
        Product("Biscuits", 150, 5, false, true, 0.7),
        Product("ScratchCard", 50, 100, false, false, 0),
        Product("TV", 300, 4, false, true, 5),
        Product("Mobile", 500, 8, false, false, 0),
        Product("Milk", 70, 3, true, true, 1.0) // expired
    };

    double customerBalance;
    cout << "Enter customer balance: ";
    cin >> customerBalance;
    cin.ignore();

    Cart cart;
    int option;
    cout << "\nChoose input mode:\n1. Manual user input\n2. Run predefined test case\nChoice: ";
    cin >> option;
    cin.ignore();

    if (option == 1) {
        int cartItems;
        cout << "\nHow many products do you want to add to the cart? ";
        cin >> cartItems;
        cin.ignore();

        for (int i = 0; i < cartItems; i++) {
            string name;
            int qty;

            cout << "\nEnter product name: ";
            getline(cin, name);

            auto it = find_if(products.begin(), products.end(), [&](Product& p) {
                return p.name == name;
            });

            if (it == products.end()) {
                cout << "Product not found!\n";
                continue;
            }

            cout << "Enter quantity: ";
            cin >> qty;
            cin.ignore();

            cart.addItem(&(*it), qty);
        }
    } else {
        // Predefined test case from PDF
        cart.addItem(&products[0], 2); // Cheese
        cart.addItem(&products[3], 3); // TV
        cart.addItem(&products[2], 1); // ScratchCard
    }

    cout << "\n\n--- Final Receipt ---\n";
    cart.checkout(customerBalance);

    return 0;
}
