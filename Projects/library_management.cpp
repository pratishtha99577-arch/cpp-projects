#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class Book {
public:
    int bookId;
    string title;
    string author;
    bool isIssued;
};

vector<Book> books;

/* Load books from file */
void loadFromFile() {
    ifstream file("books.txt");
    Book b;
    while (file >> b.bookId >> b.title >> b.author >> b.isIssued) {
        books.push_back(b);
    }
    file.close();
}

/* Save books to file */
void saveToFile() {
    ofstream file("books.txt");
    for (auto &b : books) {
        file << b.bookId << " "
             << b.title << " "
             << b.author << " "
             << b.isIssued << endl;
    }
    file.close();
}

/* Add a new book */
void addBook() {
    Book b;
    cout << "Enter Book ID: ";
    cin >> b.bookId;
    cout << "Enter Book Title: ";
    cin >> b.title;
    cout << "Enter Author Name: ";
    cin >> b.author;
    b.isIssued = false;

    books.push_back(b);
    saveToFile();
    cout << "Book added successfully!\n";
}

/* Display all books */
void displayBooks() {
    cout << "\n-------------------------------------------------------------\n";
    cout << left << setw(10) << "ID"
         << setw(15) << "Title"
         << setw(15) << "Author"
         << "Status\n";
    cout << "-------------------------------------------------------------\n";

    for (auto &b : books) {
        cout << left << setw(10) << b.bookId
             << setw(15) << b.title
             << setw(15) << b.author
             << (b.isIssued ? "Issued" : "Available") << endl;
    }
}

/* Issue a book */
void issueBook() {
    int id;
    cout << "Enter Book ID to issue: ";
    cin >> id;

    for (auto &b : books) {
        if (b.bookId == id) {
            if (!b.isIssued) {
                b.isIssued = true;
                saveToFile();
                cout << "Book issued successfully!\n";
            } else {
                cout << "Book is already issued!\n";
            }
            return;
        }
    }
    cout << "Book not found!\n";
}

/* Return a book */
void returnBook() {
    int id;
    cout << "Enter Book ID to return: ";
    cin >> id;

    for (auto &b : books) {
        if (b.bookId == id) {
            if (b.isIssued) {
                b.isIssued = false;
                saveToFile();
                cout << "Book returned successfully!\n";
            } else {
                cout << "Book was not issued!\n";
            }
            return;
        }
    }
    cout << "Book not found!\n";
}

/* Main menu */
int main() {
    loadFromFile();
    int choice;

    do {
        cout << "\n===== Library Management System =====\n";
        cout << "1. Add Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Issue Book\n";
        cout << "4. Return Book\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addBook();
            break;
        case 2:
            displayBooks();
            break;
        case 3:
            issueBook();
            break;
        case 4:
            returnBook();
            break;
        case 5:
            cout << "Exiting Library System...\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
