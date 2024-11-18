#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

// Define a structure to represent a Book
struct Book {
    int book_id;
    string book_name;
    bool availability;
};

// Define a structure to represent a Student
struct Student {
    string student_name;
    string student_id;
};

// Define a structure to represent Assigned Books
struct Assigned {
    string student_id;
    string student_name;
    int book_id;
    string date;
};

// Define a structure for Librarian
struct Librarian {
    vector<Book> books;
    vector<Student> students;
    vector<Assigned> assigned_books;

    string pass = "a";
    string Id = "a";

    // Function for login
    bool Login() {
        string username, password;
        int attempts = 0;

        while (attempts < 3) {
            cout << "Enter username : ";
            cin >> username;
            cout << "Enter password : ";
            cin >> password;

            if (password == pass && username == Id) {
                cout << "Login Successful!" << endl;
                return true;
            } else {
                cout << "Invalid username or password!" << endl;
                attempts++;
                cout << "Try again... (Attempts left: " << 3 - attempts << ")" << endl;
            }
        }
        cout << "Maximum attempts reached!" << endl;
        return false;
    }

    // Function to add a new book
    void AddBook(string bookname) {
        int newBookId = books.size() + 1; // Generate a new ID
        Book newBook = {newBookId, bookname, true};
        books.push_back(newBook);

        cout << bookname << " with book ID " << newBookId << " is added and available." << endl;
    }

    // Function to display all books
    void ReadBooksList() {
        cout << "Book ID\tBook Name\tAvailability" << endl;
        for (const auto& book : books) {
            cout << book.book_id << "\t" << book.book_name << "\t\t" << (book.availability ? "true" : "false") << endl;
        }
    }

    // Function to display all students
    void ReadStudentList() {
        cout << "Student ID\tStudent Name" << endl;
        for (const auto& student : students) {
            cout << student.student_id << "\t" << student.student_name << endl;
        }
    }

    // Function to search assigned books by student ID
    bool SearchAssignedList(string stud_id) {
        for (const auto& assign : assigned_books) {
            if (assign.student_id == stud_id) {
                cout << "Student ID: " << assign.student_id
                     << ", Name: " << assign.student_name
                     << ", Book ID: " << assign.book_id
                     << ", Date: " << assign.date << endl;
                return true;
            }
        }
        cout << "No records found for student ID: " << stud_id << endl;
        return false;
    }

    // Function to search for a book by name
    bool SearchBooksList(string bookname) {
        for (const auto& book : books) {
            if (book.book_name == bookname) {
                cout << "Book ID: " << book.book_id
                     << ", Name: " << book.book_name
                     << ", Available: " << (book.availability ? "true" : "false") << endl;
                return true;
            }
        }
        cout << "Book not found: " << bookname << endl;
        return false;
    }

    // Function to remove a student by ID
    void RemoveStudent(string stud_id) {
        for (auto it = assigned_books.begin(); it != assigned_books.end(); ++it) {
            if (it->student_id == stud_id) {
                assigned_books.erase(it);
                cout << "Student with ID " << stud_id << " has been removed from assigned list." << endl;
                return;
            }
        }
        cout << "Student with ID " << stud_id << " not found in assigned list!" << endl;
    }

    // Function to assign a book to a student
    void AddStudent(string stud_id, string book_id, string date) {
        for (auto& book : books) {
            if (to_string(book.book_id) == book_id && book.availability) {
                for (const auto& student : students) {
                    if (student.student_id == stud_id) {
                        Assigned newAssignment = {stud_id, student.student_name, book.book_id, date};
                        assigned_books.push_back(newAssignment);
                        book.availability = false; // Mark the book as unavailable
                        cout << "Assigned Book ID " << book.book_id << " to Student ID " << stud_id << " on " << date << "." << endl;
                        return;
                    }
                }
                cout << "Student ID " << stud_id << " not found in student list!" << endl;
                return;
            }
        }
        cout << "Book ID " << book_id << " is not available or does not exist!" << endl;
    }
};

// Populate initial data
void PopulateData(Librarian& librarian) {
    // Adding initial books
    librarian.books.push_back({1, "Ayush_goyal", true});
    librarian.books.push_back({2, "HarshAwasthi", true});
    librarian.books.push_back({3, "Pragati Jain", true});
    librarian.books.push_back({4, "Kunjal Varshney", true});

    // Adding initial students
    librarian.students.push_back({"Ayush Goyal", "GM7106"});
    librarian.students.push_back({"Harsh Awasthi", "GP5008"});
    librarian.students.push_back({"Kunjal Varshney", "GM8237"});
    librarian.students.push_back({"Pragati Jain", "GP4587"});

    // Adding initial assigned books
    librarian.assigned_books.push_back({"GM7106", "Ayush_goyal", 1, "2024-11-14"});
    librarian.assigned_books.push_back({"GM8237", "Kunjal Varshney", 2, "2024-11-14"});
    librarian.assigned_books.push_back({"GP4587", "Pragati Jain", 3, "2024-11-14"});
    librarian.assigned_books.push_back({"GP5008", "Harsh Awasthi", 4, "2024-11-14"});
}

int main() {
    Librarian librarian;
    PopulateData(librarian);

    // Login
    if (!librarian.Login()) {
        return 0;
    }

    // Example Usage
    librarian.ReadBooksList();
    librarian.ReadStudentList();

    librarian.SearchAssignedList("GM7106");
    librarian.SearchBooksList("HarshAwasthi");

    librarian.RemoveStudent("GM7106");
    librarian.AddStudent("GP4587", "3", "2024-11-18");

    librarian.ReadBooksList();
    return 0;
}
