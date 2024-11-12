/*LIBRARY MANAGEMENT SYSTEM

Write a program that manage books, borrowers, and transactions in a library.
Book Database: Store book information (title, author, ISBN) in a database.
Book Search: Allow users to search for books based on title, author, or ISBN.
Book Checkout: Enable librarians to check out books to borrowers.
Book Return: Record book returns and update availability status.
Fine Calculation: Implement a fine calculation system for overdue books.
User Interface: Design a user-friendly interface for easy interaction*/
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <map>

using namespace std;

// Book structure to store book information
struct Book {
    int id;
    string title;
    string author;
    bool isAvailable;
    string borrowerName;
    time_t dueDate;
};

// Global variables
map<int, Book> books;
int bookCounter = 0;

// Load books from a file
void loadBooks() {
    ifstream inFile("books.txt");
    if (inFile) {
        Book book;
        while (inFile >> book.id >> ws && getline(inFile, book.title) && getline(inFile, book.author) >> book.isAvailable >> ws && getline(inFile, book.borrowerName) >> book.dueDate) {
            books[book.id] = book;
            bookCounter = max(bookCounter, book.id);
        }
    }
    inFile.close();
}

// Save books to a file
void saveBooks() {
    ofstream outFile("books.txt");
    for (const auto& entry : books) {
        const Book& book = entry.second;
        outFile << book.id << '\n' << book.title << '\n' << book.author << '\n' << book.isAvailable << '\n' << book.borrowerName << '\n' << book.dueDate << '\n';
    }
    outFile.close();
}

// Add a new book
void addBook() {
    Book book;
    book.id = ++bookCounter;
    cout << "Enter title: ";
    cin.ignore();
    getline(cin, book.title);
    cout << "Enter author: ";
    getline(cin, book.author);
    book.isAvailable = true;
    books[book.id] = book;
    cout << "Book added with ID: " << book.id << endl;
}

// Search for a book by title or author
void searchBook() {
    cout << "Enter title or author to search: ";
    string query;
    cin.ignore();
    getline(cin, query);

    bool found = false;
    for (const auto& entry : books) {
        const Book& book = entry.second;
        if (book.title.find(query) != string::npos || book.author.find(query) != string::npos) {
            cout << "ID: " << book.id << ", Title: " << book.title << ", Author: " << book.author << ", Available: " << (book.isAvailable ? "Yes" : "No") << endl;
            found = true;
        }
    }
    if (!found) cout << "No matching books found." << endl;
}

// Check out a book
void checkoutBook() {
    int id;
    cout << "Enter book ID to check out: ";
    cin >> id;

    if (books.find(id) != books.end()) {
        Book& book = books[id];
        if (book.isAvailable) {
            cout << "Enter borrower name: ";
            cin.ignore();
            getline(cin, book.borrowerName);

            book.isAvailable = false;
            time_t now = time(0);
            book.dueDate = now + (7 * 24 * 60 * 60); // 1 week loan period
            cout << "Book checked out. Due date in one week." << endl;
        } else {
            cout << "Book is already checked out." << endl;
        }
    } else {
        cout << "Book ID not found." << endl;
    }
}

// Return a book and calculate fine if overdue
void returnBook() {
    int id;
    cout << "Enter book ID to return: ";
    cin >> id;

    if (books.find(id) != books.end()) {
        Book& book = books[id];
        if (!book.isAvailable) {
            time_t now = time(0);
            if (now > book.dueDate) {
                int daysLate = (now - book.dueDate) / (24 * 60 * 60);
                int fine = daysLate * 1; // $1 per day late fee
                cout << "Book is " << daysLate << " days late. Fine: $" << fine << endl;
            }
            book.isAvailable = true;
            book.borrowerName = "";
            book.dueDate = 0;
            cout << "Book returned successfully." << endl;
        } else {
            cout << "Book was not checked out." << endl;
        }
    } else {
        cout << "Book ID not found." << endl;
    }
}

// Display menu options
void showMenu() {
    cout << "\nLibrary Management System\n";
    cout << "1. Add Book\n";
    cout << "2. Search Book\n";
    cout << "3. Checkout Book\n";
    cout << "4. Return Book\n";
    cout << "5. Exit\n";
}

int main() {
    loadBooks();
    int choice;
    do {
        showMenu();
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addBook(); break;
            case 2: searchBook(); break;
            case 3: checkoutBook(); break;
            case 4: returnBook(); break;
            case 5: saveBooks(); cout << "Exiting...\n"; break;
            default: cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
