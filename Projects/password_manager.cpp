#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Credential {
public:
    string website;
    string username;
    string password;
};

vector<Credential> credentials;

/* Simple encryption (Caesar cipher style) */
string encryptDecrypt(string text) {
    for (char &c : text) {
        c = c + 3;   // shift characters
    }
    return text;
}

/* Load credentials from file */
void loadFromFile() {
    ifstream file("passwords.txt");
    Credential c;
    while (file >> c.website >> c.username >> c.password) {
        c.password = encryptDecrypt(c.password); // decrypt while loading
        credentials.push_back(c);
    }
    file.close();
}

/* Save credentials to file */
void saveToFile() {
    ofstream file("passwords.txt");
    for (auto &c : credentials) {
        file << c.website << " "
             << c.username << " "
             << encryptDecrypt(c.password) << endl; // encrypt before saving
    }
    file.close();
}

/* Add new credential */
void addCredential() {
    Credential c;
    cout << "Enter Website: ";
    cin >> c.website;
    cout << "Enter Username: ";
    cin >> c.username;
    cout << "Enter Password: ";
    cin >> c.password;

    credentials.push_back(c);
    saveToFile();
    cout << "Password saved securely!\n";
}

/* View all credentials */
void viewCredentials() {
    cout << "\nStored Credentials:\n";
    for (auto &c : credentials) {
        cout << "Website: " << c.website
             << " | Username: " << c.username
             << " | Password: " << c.password << endl;
    }
}

/* Search credential */
void searchCredential() {
    string site;
    cout << "Enter Website to search: ";
    cin >> site;

    for (auto &c : credentials) {
        if (c.website == site) {
            cout << "Username: " << c.username << endl;
            cout << "Password: " << c.password << endl;
            return;
        }
    }
    cout << "No credentials found!\n";
}

/* Main menu */
int main() {
    loadFromFile();
    int choice;

    do {
        cout << "\n===== Password Manager =====\n";
        cout << "1. Add Password\n";
        cout << "2. View All Passwords\n";
        cout << "3. Search Password\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addCredential();
            break;
        case 2:
            viewCredentials();
            break;
        case 3:
            searchCredential();
            break;
        case 4:
            cout << "Exiting Password Manager...\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
