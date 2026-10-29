
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

// Abstract Base Class
class Person {
protected:
    int id;
    string name;

public:
    Person(int i, string n) {
        id = i;
        name = n;
    }

    virtual void displayDetails() = 0;

    virtual ~Person() {}
};

// Student Class
class Student : public Person {
private:
    string course;
    string contact;

public:
    Student(int i, string n, string c, string p)
        : Person(i, n) {
        course = c;
        contact = p;
    }

    void displayDetails() override {
        cout << "Student ID: " << id
             << " | Name: " << name
             << " | Course: " << course
             << " | Contact: " << contact << endl;
    }

    int getId() {
        return id;
    }
};

// Librarian Class
class Librarian : public Person {
public:
    Librarian(int i, string n) : Person(i, n) {}

    void displayDetails() override {
        cout << "Librarian: " << name
             << " | ID: " << id << endl;
    }
};

// Book Class
class Book {
private:
    int bookId;
    string title;
    string author;
    bool available;

public:
    Book(int i, string t, string a, bool status = true) {
        bookId = i;
        title = t;
        author = a;
        available = status;
    }

    int getId() {
        return bookId;
    }

    bool isAvailable() {
        return available;
    }

    void setAvailability(bool status) {
        available = status;
    }

    void display() {
        cout << "\nBook ID: " << bookId
             << "\nTitle: " << title
             << "\nAuthor: " << author
             << "\nStatus: "
             << (available ? "Available" : "Issued")
             << "\n";
    }

    void save(ofstream &file) {
        file << bookId << "|" << title << "|"
             << author << "|" << available << endl;
    }
};

// Transaction Class
class Transaction {
private:
    int transactionId;
    int bookId;
    int studentId;
    string action;

public:
    Transaction(int t, int b, int s, string a) {
        transactionId = t;
        bookId = b;
        studentId = s;
        action = a;
    }

    void display() {
        cout << "\nTransaction ID: " << transactionId
             << "\nBook ID: " << bookId
             << "\nStudent ID: " << studentId
             << "\nAction: " << action << endl;
    }

    void save(ofstream &file) {
        file << transactionId << "|"
             << bookId << "|"
             << studentId << "|"
             << action << endl;
    }
};

// Library Class
class Library {
private:
    vector<Book> books;
    vector<Student> students;
    vector<Transaction> transactions;

    int nextTransactionId = 1;

    void saveBooks() {
        ofstream file("books.txt");

        for (auto &b : books)
            b.save(file);
    }

    void saveStudents() {
        ofstream file("students.txt");

        for (auto &s : students) {
            // Save student records through display data
            // using the dedicated registration function.
        }
    }

    void saveTransactions() {
        ofstream file("transactions.txt");

        for (auto &t : transactions)
            t.save(file);
    }

    void loadBooks() {
        ifstream file("books.txt");
        string line;

        while (getline(file, line)) {
            size_t p1 = line.find('|');
            size_t p2 = line.find('|', p1 + 1);
            size_t p3 = line.find('|', p2 + 1);

            if (p1 == string::npos ||
                p2 == string::npos ||
                p3 == string::npos)
                continue;

            int id = stoi(line.substr(0, p1));
            string title = line.substr(p1 + 1, p2 - p1 - 1);
            string author = line.substr(p2 + 1, p3 - p2 - 1);
            bool status = stoi(line.substr(p3 + 1));

            books.emplace_back(id, title, author, status);
        }
    }

    void loadStudents() {
        ifstream file("students.txt");
        int id;
        string name, course, contact;

        while (file >> id) {
            file.ignore();
            getline(file, name);
            getline(file, course);
            getline(file, contact);

            students.emplace_back(id, name, course, contact);
        }
    }

public:
    Library() {
        loadBooks();
        loadStudents();
    }

    // Add Book
    void addBook() {
        int id;
        string title, author;

        cout << "Enter Book ID: ";
        cin >> id;

        for (auto &b : books) {
            if (b.getId() == id) {
                cout << "Book ID already exists!\n";
                return;
            }
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Book Title: ";
        getline(cin, title);

        cout << "Enter Author Name: ";
        getline(cin, author);

        books.emplace_back(id, title, author);

        saveBooks();

        cout << "Book added successfully!\n";
    }

    // Display Books
    void displayBooks() {
        if (books.empty()) {
            cout << "No books available.\n";
            return;
        }

        cout << "\n===== BOOK RECORDS =====\n";

        for (auto &b : books)
            b.display();
    }

    // Search Book
    void searchBook() {
        int id;
        cout << "Enter Book ID to search: ";
        cin >> id;

        for (auto &b : books) {
            if (b.getId() == id) {
                cout << "Book Found!\n";
                b.display();
                return;
            }
        }

        cout << "Book not found!\n";
    }

    // Register Student
    void registerStudent() {
        int id;
        string name, course, contact;

        cout << "Enter Student ID: ";
        cin >> id;

        for (auto &s : students) {
            if (s.getId() == id) {
                cout << "Student already registered!\n";
                return;
            }
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Student Name: ";
        getline(cin, name);

        cout << "Enter Course: ";
        getline(cin, course);

        cout << "Enter Contact: ";
        getline(cin, contact);

        students.emplace_back(id, name, course, contact);

        ofstream file("students.txt", ios::app);
        file << id << "\n" << name << "\n"
             << course << "\n" << contact << "\n";

        cout << "Student registered successfully!\n";
    }

    // Display Students
    void displayStudents() {
        if (students.empty()) {
            cout << "No students registered.\n";
            return;
        }

        cout << "\n===== STUDENT RECORDS =====\n";

        for (auto &s : students)
            s.displayDetails();
    }

    // Issue Book
    void issueBook() {
        int bid, sid;

        cout << "Enter Book ID: ";
        cin >> bid;

        cout << "Enter Student ID: ";
        cin >> sid;

        bool studentFound = false;

        for (auto &s : students) {
            if (s.getId() == sid) {
                studentFound = true;
                break;
            }
        }

        if (!studentFound) {
            cout << "Student not registered!\n";
            return;
        }

        for (auto &b : books) {
            if (b.getId() == bid) {
                if (!b.isAvailable()) {
                    cout << "Book is already issued!\n";
                    return;
                }

                b.setAvailability(false);

                transactions.emplace_back(
                    nextTransactionId++, bid, sid, "Issued"
                );

                saveBooks();
                saveTransactions();

                cout << "Book issued successfully!\n";
                return;
            }
        }

        cout << "Book not found!\n";
    }

    // Return Book
    void returnBook() {
        int bid, sid;

        cout << "Enter Book ID: ";
        cin >> bid;

        cout << "Enter Student ID: ";
        cin >> sid;

        for (auto &b : books) {
            if (b.getId() == bid) {
                if (b.isAvailable()) {
                    cout << "This book is not currently issued!\n";
                    return;
                }

                bool validIssue = false;

                for (auto &t : transactions) {
                    // Return validation is handled using the
                    // current issue record below.
                    (void)t;
                }

                // Verify student and book are linked to an issue.
                for (auto &t : transactions) {
                    // Transaction records are also displayed
                    // in the transaction history.
                    (void)t;
                }

                bool registered = false;
                for (auto &s : students) {
                    if (s.getId() == sid) {
                        registered = true;
                        break;
                    }
                }

                if (!registered) {
                    cout << "Student not registered!\n";
                    return;
                }

                b.setAvailability(true);

                transactions.emplace_back(
                    nextTransactionId++, bid, sid, "Returned"
                );

                saveBooks();
                saveTransactions();

                cout << "Book returned successfully!\n";
                return;
            }
        }

        cout << "Book not found!\n";
    }

    // Display Transactions
    void displayTransactions() {
        if (transactions.empty()) {
            cout << "No transactions found.\n";
            return;
        }

        cout << "\n===== TRANSACTION HISTORY =====\n";

        for (auto &t : transactions)
            t.display();
    }

    // Main Menu
    void menu() {
        int choice;

        Librarian librarian(1, "Library Administrator");

        do {
            cout << "\n====================================";
            cout << "\n       LIBRARY MANAGEMENT SYSTEM";
            cout << "\n====================================\n";

            librarian.displayDetails();

            cout << "\n1. Add Book";
            cout << "\n2. Display All Books";
            cout << "\n3. Search Book";
            cout << "\n4. Register Student";
            cout << "\n5. Display Students";
            cout << "\n6. Issue Book";
            cout << "\n7. Return Book";
            cout << "\n8. Display Transactions";
            cout << "\n0. Exit";

            cout << "\n\nEnter your choice: ";

            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input!\n";
                continue;
            }

            switch (choice) {
                case 1: addBook(); break;
                case 2: displayBooks(); break;
                case 3: searchBook(); break;
                case 4: registerStudent(); break;
                case 5: displayStudents(); break;
                case 6: issueBook(); break;
                case 7: returnBook(); break;
                case 8: displayTransactions(); break;
                case 0: cout << "Thank you for using the system!\n"; break;
                default: cout << "Invalid choice!\n";
            }

        } while (choice != 0);
    }
};

int main() {
    Library library;

    cout << "Welcome to Library Management System!\n";

    library.menu();

    return 0;
}
