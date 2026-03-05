// Mehir Usakli 32617

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cctype>
using namespace std;


void trim(string& s) {
    while (!s.empty() && isspace((unsigned char)s.back())) s.pop_back();
    while (!s.empty() && isspace((unsigned char)s.front())) s.erase(s.begin());
    if (!s.empty() && s.back() == ',') s.pop_back();
}

int Choice() {
    int choice;
    while (true) {
        cout << "\nMenu\n"
            << "1. Add Book to the Cart\n"
            << "2. Edit Book's Quantity in the Cart\n"
            << "3. Delete Books from the Cart\n"
            << "4. Display Cart\n"
            << "5. Exit\n"
            << "Enter your choice: " << endl;

        if (cin >> choice) {
            if (choice >= 1 && choice <= 5) return choice;
            cout << "Invalid input." << endl;
        }
        else {
            cout << "Invalid input." << endl;
            cin.clear();
            string trash; cin >> trash;
        }
    }
}

int create_array(string filename,
    string isbn_arr[], string title_arr[], double price_arr[],
    double available_arr[], double quantities[], double vowelCount_arr[])
{
    ifstream file(filename);
    int bookCount = 0;

    if (!file.is_open()) {
        cout << "Error: Unable to open file " << filename << endl;
        return 0;
    }

    string isbn_str, title_str, price_str, qty_str;

    while (bookCount < 50 && getline(file, isbn_str, ',')) {
        getline(file, title_str, ',');
        getline(file, price_str, ',');
        getline(file, qty_str);

        trim(isbn_str);
        trim(title_str);
        trim(price_str);
        trim(qty_str);

        isbn_arr[bookCount] = isbn_str;
        title_arr[bookCount] = title_str;

        {
            stringstream ss(price_str);
            ss >> price_arr[bookCount];
        }
        {
            stringstream ss(qty_str);
            ss >> available_arr[bookCount];
        }

        quantities[bookCount] = 0.0;

        int vowels = 0;
        for (char c : title_arr[bookCount]) {
            char lower = static_cast<char>(tolower(static_cast<unsigned char>(c)));
            if (lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u')
                vowels++;
        }
        vowelCount_arr[bookCount] = vowels;

        bookCount++;
    }

    return bookCount;
}

void Catalog(int bookCount,
    string isbn_arr[], string title_arr[], double price_arr[],
    double available_arr[], double vowelCount_arr[])
{
    cout << endl << "=== Catalog Loaded ===" << endl;
    cout << fixed << setprecision(2);

    for (int i = 0; i < bookCount; i++) {
        cout << "ISBN: " << isbn_arr[i]
            << " | Title: " << title_arr[i]
            << " | Price: $" << price_arr[i]
            << " | Available Quantity: " << available_arr[i]
            << " | Vowels in Title: " << vowelCount_arr[i]
            << endl;
    }

    cout << "======================" << endl;
}

int main() {
    int choice;
    string filename;
    cout << "Welcome to the Library Checkout System!" << endl;
    cout << "Enter the name of the file containing books data:" << endl;
    cin >> filename;

    ifstream testFile(filename);
    while (!testFile.is_open()) {
        cout << "Error: Unable to open file " << filename << endl;
        cout << "Please re-enter a valid filename." << endl;
        cin >> filename;
        testFile.clear();
        testFile.open(filename);
    }
    testFile.close();

    string isbn_arr[50];
    string title_arr[50];
    double price_arr[50];
    double available_arr[50];
    double quantities[50];
    double vowelCount_arr[50];

    int bookCount = create_array(filename, isbn_arr, title_arr, price_arr,
        available_arr, quantities, vowelCount_arr);

    Catalog(bookCount, isbn_arr, title_arr, price_arr,
        available_arr, vowelCount_arr);

    string ISBN;
    while (true) {
        choice = Choice();

        if (choice == 1) {
            cout << "Enter ISBN no:" << endl;
            cin >> ISBN;

            int idx = -1;
            for (int i = 0; i < bookCount; i++) {
                if (isbn_arr[i] == ISBN) { idx = i; break; }
            }

            if (idx == -1) {
                cout << "The Book with this ISBN no is not found in the Catalog." << endl;
            }
            else {
                cout << "Enter quantity to add:" << endl;
                double req;
                if (!(cin >> req)) {
                    cout << "Invalid input." << endl;
                    cin.clear();
                    string trash; cin >> trash;
                    continue;
                }
                if (req <= 0) {
                    cout << "Invalid input." << endl;
                    continue;
                }

                cout << fixed << setprecision(2);

                if (available_arr[idx] <= 0.0) {
                    cout << "Only " << 0.00 << " available." << endl;
                }
                else if (req > available_arr[idx]) {
                    cout << "Only " << available_arr[idx] << " available." << endl;
                }
                else {
                    quantities[idx] += req;
                    available_arr[idx] -= req;
                    cout << "Added " << req << " copies of \""
                        << title_arr[idx] << "\"." << endl;
                }
            }
        }
        else if (choice == 2) {
            bool cartEmpty = true;
            for (int i = 0; i < bookCount; i++) {
                if (quantities[i] > 0) { cartEmpty = false; break; }
            }
            if (cartEmpty) {
                cout << "Cart is empty. Nothing to edit." << endl;
            }
            else {
                cout << "Enter ISBN no:" << endl;
                string inIsbn;
                cin >> inIsbn;

                int idx = -1;
                for (int i = 0; i < bookCount; i++) {
                    if (isbn_arr[i] == inIsbn) { idx = i; break; }
                }

                if (idx == -1 || quantities[idx] == 0) {
                    cout << "The Book with this ISBN no is not in the Cart." << endl;
                }
                else {
                    cout << "Current quantity in Cart: " << (double)quantities[idx] << endl;
                    cout << "Remaining in store (not in your cart yet): " << (double)available_arr[idx] << endl;

                    cout << "Enter new quantity (>= 0):" << endl;
                    double newQty;
                    if (!(cin >> newQty)) {
                        cout << "Invalid input." << endl;
                        cin.clear();
                        string trash; cin >> trash;
                        continue;
                    }
                    if (newQty < 0) {
                        cout << "Invalid input." << endl;
                        continue;
                    }

                    double totalAvailable = quantities[idx] + available_arr[idx];

                    if (newQty > totalAvailable) {
                        cout << "Only " << (double)totalAvailable
                            << " available in total (store + cart)." << endl;
                    }
                    else {
                        double delta = newQty - quantities[idx];
                        quantities[idx] = newQty;
                        available_arr[idx] -= delta;
                        cout << "Quantity updated." << endl;
                    }
                }
            }
        }
        else if (choice == 3) {
            bool cartEmpty = true;
            for (int i = 0; i < bookCount; i++) {
                if (quantities[i] > 0) { cartEmpty = false; break; }
            }
            if (cartEmpty) {
                cout << "Cart is empty. Nothing to delete." << endl;
            }
            else {
                cout << "Enter ISBN no:" << endl;
                string inIsbn;
                cin >> inIsbn;

                int idx = -1;
                for (int i = 0; i < bookCount; i++) {
                    if (isbn_arr[i] == inIsbn) { idx = i; break; }
                }

                if (idx == -1 || quantities[idx] == 0) {
                    cout << "There is no such a book with this ISBN in your cart." << endl;
                }
                else {
                    available_arr[idx] += quantities[idx];
                    quantities[idx] = 0;
                    cout << "Item removed from cart." << endl;
                }
            }
        }
        else if (choice == 4) {

            bool cartEmpty = true;
            for (int i = 0; i < bookCount; i++) {
                if (quantities[i] > 0) { cartEmpty = false; break; }
            }

            if (cartEmpty) {
                cout << "Cart is empty." << endl;
            }
            else {
                cout << "Cart (Items Added):" << endl;

                int lineNo = 1;
                for (int i = 0; i < bookCount; i++) {
                    if (quantities[i] > 0) {
                        double lineTotal = quantities[i] * price_arr[i];
                        cout << lineNo << ". ISBN: " << isbn_arr[i]
                            << " | " << title_arr[i] << "  "
                            << (double)quantities[i] << " x $" << price_arr[i]
                            << " = $" << lineTotal << endl;
                        lineNo++;
                    }
                }
            }

            cout << "Do you want to exit (checkout) or continue? Enter E to exit, or any other key to continue:" << endl;
            string ans;
            cin >> ans;

            if (ans == "E" || ans == "e") {
                double subtotal = 0.0;
                for (int i = 0; i < bookCount; i++) {
                    if (quantities[i] > 0) {
                        subtotal += quantities[i] * price_arr[i];
                    }
                }
                double serviceFee = (subtotal > 0.0) ? 4.99 : 0.00;
                double total = subtotal + serviceFee;

                cout << "Subtotal: $" << subtotal << endl;
                cout << "Service fee: $" << serviceFee << endl;
                cout << "Total price: $" << total << endl;
                cout << "Goodbye!" << endl;
                break;
            }
            else {
                cout << "Continuing..." << endl;
            }
        }
        else if (choice == 5) {
            cout << "Goodbye!" << endl;
            break;
        }
    }
    return 0;
}
