#include <iostream>
#include "student.h"
#include "librarian.h"
#include "csvReadAndWrite.h"

#pragma once

class Library : public Student, Librarian,csv
{
    static const int MAX_BOOKS = 100;   // Maximum number of books

    static const int MAX_LINE_LEN = 256; // Maximum length of a line in the file

    public:

    void borrow(string stud_id, string bookname, string date)
    {       
        if (SearchAssignedList(stud_id))
        {
            cout << "Student already have a book !!"<<"\n";
            cout << "No new can be provided until you already have a book"<<"\n";
            return;
        }
        else
        {
            if(SearchBookslist(bookname)) /*need change*/
            {
                cout <<"Book is available !"<<"\n";
                cout << bookname <<" is assigned to student with student Id " << stud_id;
                AddStudent(stud_id, bookname /*we should write here book id*/, date);
            }
        }
    }
    
    double fineCalculator(string stud_id)
    {
        /*to compare date from assinged */
        return 0;
    }

    void deposit(string stud_id, string date, string bookname) {
    string column_name_student = "Student_Id";
    string column_name_book = "Book_name";

    // Check if the book is in the assigned list for the student
    if (!csvSearch(filename3, stud_id, column_name_student)) {
        cout << "No book is assigned to this student with ID: " << stud_id << endl;
        return;
    }

    // Remove the row from assigned.csv
    csvRemove(filename3, 0, stud_id);
    cout << "Book \"" << bookname << "\" has been successfully returned by student with ID: " << stud_id << endl;

    // Update the availability in books.csv
    string tempFilename = "temp.csv";
    ifstream booksFile(filename2);
    ofstream tempFile(tempFilename);

    if (!booksFile.is_open() || !tempFile.is_open()) {
        cerr << "Error: Could not open the files for processing!" << endl;
        return;
    }

    string line;
    while (getline(booksFile, line)) {
        vector<string> row = parseCSVLine(line);
        if (row.size() >= 2 && row[1] == bookname) {
            // Update the availability to true
            tempFile << row[0] << "," << row[1] << ",true\n";
        } else {
            tempFile << line << "\n";
        }
    }

    booksFile.close();
    tempFile.close();

    // Replace books.csv with the updated file
    remove(filename2.c_str());
    rename(tempFilename.c_str(), filename2.c_str());
    cout << "Book \"" << bookname << "\" is now marked as available in books.csv." << endl;
}


};
