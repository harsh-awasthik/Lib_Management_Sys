#include <iostream>
#include "person.h"
#pragma once

class Librarian : public Person,public virtual csv
{
private:
    string pass = "a";
    string Id = "a";
    int bookId;
    string bookName;
    bool availability;

protected:
    string filename1 = "student.csv";   
    string filename2 = "books.csv";
    string filename3 = "assigned.csv";

public:
    Librarian(){} // default constructor 
    // Constructor
    Librarian(int id, string name, bool avail = true) : bookId(id), bookName(name), availability(avail) {}

    vector<Librarian> books; // In-memory list of books
    int lastBookId = 0; // Tracks the last book ID

    void SignUp()
    {
        cout <<"Librarian not require sign up";
    }

    bool Login () 
    {
        string username, password;
        int i = 0;
        
        while (i < 3)
        {
            cout <<"Enter username : ";
            cin >> username;
            cout <<"Enter password : ";
            cin >> password;

            if (password == pass && username == Id)
            {
                cout << "Login Successful  "<<"\n";
                return true;
            }
            else
            {               
                cout << "Invalid USername or password!!"<<"\n";
                i++;
                cout << "Try again... (Attempt/s left " << 3-i << ")" << endl;
                       
            }         
        }
        cout << "Maximum Attempts Reached!" <<endl;
        return false;
    }
    

    void ReadStudentList()
    {
        //Reading students.csv
        csvRead(filename1);
    }

    void ReadBooksList()
    {
        //Reading books.csv
        csvRead(filename2);
    }

    bool SearchAssignedList(string stud_id)
    {
        string colnname = "Student_Id";
        if(csvSearch(filename3, stud_id, colnname))
        {
            return true;
        }
        return false;
    }

    bool SearchBookslist(string bookname)
    {
        string colmname = "Book_name";
        if(csvSearch(filename2, bookname, colmname))
        {
            return true;          
        }
        return false;
    }

    
    void removeBook(string bookname)
    {
        csvRemove(filename2, 1, bookname);
    }

    

    void removeStudent(string Stud_Id)
    {
        //Removing student from assigned list
        csvRemove(filename3, 0, Stud_Id);
        cout << "Student with student id " << Stud_Id << " is removed 🥳"<<"\n";
    }

    void AddStudent(string stud_Id , string book_id, string date)
    {
        //Adding student book and date into assigned list
        csvWriteAssignedList(filename3, stud_Id, book_id, date);
        cout << "Student with student id " << stud_Id << " is added "<<"\n";
    }

    void AddBook(string bookname)
    {
        int newBookId = ++lastBookId;

        // Create a new Book object and add it to the list
        books.emplace_back(newBookId, bookname, true);
        
        ofstream outfile("books.csv", ios::app); // Open in append mode
    if (outfile.is_open()) {
        outfile << newBookId << ",\"" << bookname << "\",true\n";
        outfile.close();

        cout << "Book \"" << bookname << "\" with Book ID " << newBookId
             << " is added successfully with availability set to true.\n";
    } else {
        cerr << "Error: Unable to open books.csv for writing.\n";
    }

    }

};
