#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Book {
protected:
    string isbn;
    string title;
    int year;
public:
    Book(string isbn, string title, int year) : isbn(isbn), title(title), year(year) {}
    virtual void display() const {
        cout << "ISBN: " << isbn << ", Title: " << title << ", Year: " << year << endl;
    }
    virtual void buy() const = 0;
    int getYear() const { return year; }
};

class PaperBook : public Book {
    string address;
public:
    PaperBook(string isbn, string title, int year, string address)
        : Book(isbn, title, year), address(address) {}
    void buy() const override {
        cout << "Sent 1 paper book to: " << address << endl;
    }
};

class EBook : public Book {
    string email;
public:
    EBook(string isbn, string title, int year, string email)
        : Book(isbn, title, year), email(email) {}
    void buy() const override {
        cout << "Sent 1 ebook to email: " << email << endl;
    }
};

class ShowcaseBook : public Book {
public:
    ShowcaseBook(string isbn, string title, int year)
        : Book(isbn, title, year) {}
    void buy() const override {
        cout << "This book is not for sale." << endl;
    }
};

void showMenu() {
    cout << "\n=== Bookstore Menu ===\n";
    cout << "1. Add Book\n";
    cout << "2. Buy Book\n";
    cout << "3. Remove Old Books\n";
    cout << "4. Show All Books\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    vector<Book*> books;

    // إضافة بعض الكتب تلقائيًا
    books.push_back(new PaperBook("111", "C++ Primer", 2012, "Giza"));
    books.push_back(new EBook("222", "Python Basics", 2020, "mail@example.com"));
    books.push_back(new ShowcaseBook("333", "History of AI", 1998));

    int choice;
    while (true) {
        showMenu();
        cin >> choice;

        if (choice == 0)
            break;

        if (choice == 1) {
            int type;
            cout << "Enter book type (1: PaperBook, 2: EBook, 3: Showcase): ";
            cin >> type;

            string isbn, title;
            int year;
            cout << "ISBN: "; cin >> isbn;
            cin.ignore();
            cout << "Title: "; getline(cin, title);
            cout << "Year: "; cin >> year;

            if (type == 1) {
                string address;
                cin.ignore();
                cout << "Address: "; getline(cin, address);
                books.push_back(new PaperBook(isbn, title, year, address));
            } else if (type == 2) {
                string email;
                cin.ignore();
                cout << "Email: "; getline(cin, email);
                books.push_back(new EBook(isbn, title, year, email));
            } else if (type == 3) {
                books.push_back(new ShowcaseBook(isbn, title, year));
            }
        } else if (choice == 2) {
            int index;
            cout << "Enter book index to buy (starting from 0): ";
            cin >> index;
            if (index >= 0 && index < books.size()) {
                books[index]->buy();
            } else {
                cout << "Invalid index." << endl;
            }
        } else if (choice == 3) {
            int currentYear;
            cout << "Enter current year: ";
            cin >> currentYear;
            for (int i = 0; i < books.size(); ++i) {
                if (books[i]->getYear() < currentYear - 10) {
                    delete books[i];
                    books.erase(books.begin() + i);
                    --i;
                }
            }
            cout << "Old books removed.\n";
        } else if (choice == 4) {
            for (int i = 0; i < books.size(); ++i) {
                cout << i << ". ";
                books[i]->display();
            }
        }
    }

    for (Book* book : books) {
        delete book;
    }
    return 0;
}
