#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include<string>
using namespace std;

class Student {
public:
    int rollNo;
    string name;
    float marks;

    char calculateGrade() const {
        if (marks >= 90) return 'A';
        else if (marks >= 75) return 'B';
        else if (marks >= 60) return 'C';
        else if (marks >= 40) return 'D';
        else return 'F';
    }
};

vector<Student> students;

/* Load data from file */
void loadFromFile() {
    ifstream file("students.txt");
    Student s;
    while (file >> s.rollNo >> s.name >> s.marks) {
        students.push_back(s);
    }
    file.close();
}

/* Save data to file */
void saveToFile() {
    ofstream file("students.txt");
    for (const auto &s : students) {
        file << s.rollNo << " " << s.name << " " << s.marks << endl;
    }
    file.close();
}

/* Add student */
void addStudent() {
    Student s;
    cout << "Enter Roll Number: ";
    cin >> s.rollNo;
    cout << "Enter Name: ";
    cin >> s.name;
    cout << "Enter Marks: ";
    cin >> s.marks;

    students.push_back(s);
    saveToFile();
    cout << "✅ Student added successfully!\n";
}

/* Display all students */
void displayStudents() {
    cout << "\n--------------------------------------------------\n";
    cout << left << setw(10) << "Roll"
         << setw(15) << "Name"
         << setw(10) << "Marks"
         << "Grade\n";
    cout << "--------------------------------------------------\n";

    for (const auto &s : students) {
        cout << left << setw(10) << s.rollNo
             << setw(15) << s.name
             << setw(10) << s.marks
             << s.calculateGrade() << endl;
    }
}

/* Search student */
void searchStudent() {
    int roll;
    cout << "Enter Roll Number to search: ";
    cin >> roll;

    for (const auto &s : students) {
        if (s.rollNo == roll) {
            cout << "\nStudent Found:\n";
            cout << "Name: " << s.name << endl;
            cout << "Marks: " << s.marks << endl;
            cout << "Grade: " << s.calculateGrade() << endl;
            return;
        }
    }
    cout << "❌ Student not found!\n";
}

/* Delete student */
void deleteStudent() {
    int roll;
    cout << "Enter Roll Number to delete: ";
    cin >> roll;

    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->rollNo == roll) {
            students.erase(it);
            saveToFile();
            cout << "🗑️ Student deleted successfully!\n";
            return;
        }
    }
    cout << "❌ Student not found!\n";
}

int main() {
    loadFromFile();

    int choice;
    do {
        cout << "\n===== Smart Student Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addStudent();
            break;
        case 2:
            displayStudents();
            break;
        case 3:
            searchStudent();
            break;
        case 4:
            deleteStudent();
            break;
        case 5:
            cout << "👋 Exiting program...\n";
            break;
        default:
            cout << "⚠ Invalid choice! Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
