#include <iostream>
#include <string>
#include "student.h"
#include "librarian.h"
#include "csvReadAndWrite.h"

#pragma once

class Library : public Student, Librarian
{
    static const int MAX_BOOKS = 100; // Maximum number of books

    static const int MAX_LINE_LEN = 256; // Maximum length of a line in the file

public:
    void borrow(string stud_id, string bookname, string date)
    {
        if (SearchAssignedList(stud_id))
        {
            cout << "Student already have a book !!" << "\n";
            cout << "No new can be provided until you already have a book" << "\n";
            return;
        }
        else
        {
            // Now, you need to find the book_id based on the student id by reading the assigned file.
            string book_id = "";
            ifstream assignedFile("assigned.csv"); // Open the assigned file
            string line;
            bool bookFound = false;
            while (getline(assignedFile, line)) // Read the file line by line
            {
                vector<string> row = parseCSVLine(line); // Use the existing parseCSVLine function

                if (row.size() >= 2 && row[0] == stud_id) // If student ID matches, assign the book_id
                {
                    book_id = row[1]; // Assuming book_id is the second column (index 1)
                    bookFound = true;
                    break;
                }
            }

            if (SearchBookslist(book_id)) // searching through book id
            {
                cout << "Book is available !" << "\n";
                AddStudent(stud_id, book_id, date);
                cout << "Book ID " << book_id << " successfully assigned to Student ID " << stud_id << ".\n";
            }

            else
            {
                cout << "Book ID not found or unavailable.\n";
            }
        }
    }

    void deposit(string stud_id, string date, string bookname) // book is removed from assigned.csv but does not get added to book.csv for avaliabilty 
    {
        string column_name_student = "Student_Id";
        string column_name_book = "Book_name";

        // Check if the book is in the assigned list for the student
        if (!csvSearch(filename3, stud_id, column_name_student))
        {
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

        if (!booksFile.is_open() || !tempFile.is_open())
        {
            cerr << "Error: Could not open the files for processing!" << endl;
            return;
        }

        string line;
        while (getline(booksFile, line))
        {
            vector<string> row = parseCSVLine(line);
            if (row.size() >= 2 && row[1] == bookname)
            {
                // Update the availability to true
                tempFile << row[0] << "," << row[1] << ",true\n";
            }
            else
            {
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

    void parseDate(const string &date, int &day, int &month, int &year)
    {
        stringstream ss(date);
        char delimiter;

        ss >> day >> delimiter >> month >> delimiter >> year;
    }

    // Function to calculate the total days since year 0 (simplified)
    int calculateDays(int day, int month, int year)
    {
        static int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        // Adjust for leap years
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        {
            daysInMonth[1] = 29;
        }
        else
        {
            daysInMonth[1] = 28;
        }

        // Calculate total days
        int totalDays = year * 365 + day;
        for (int i = 0; i < month - 1; i++)
        {
            totalDays += daysInMonth[i];
        }
        totalDays += year / 4 - year / 100 + year / 400; // Account for leap years
        return totalDays;
    }

    // Function to calculate the fine
    int calculateFine(const string &userDate, const string &assignedDate)
    {
        int userDay, userMonth, userYear;
        int assignedDay, assignedMonth, assignedYear;

        // Parse the dates
        parseDate(userDate, userDay, userMonth, userYear);
        parseDate(assignedDate, assignedDay, assignedMonth, assignedYear);

        // Calculate days since year 0
        int userTotalDays = calculateDays(userDay, userMonth, userYear);
        int assignedTotalDays = calculateDays(assignedDay, assignedMonth, assignedYear);

        // Calculate the difference in days
        int daysDiff = abs(userTotalDays - assignedTotalDays);

        // Calculate the fine
        if (daysDiff <= 7)
        {
            return 0; // No fine for returning within 7 days
        }
        else
        {
            return (daysDiff - 7) * 8; // Rs. 8 fine per extra day
        }
    }

    // Function to fetch assigned date using student ID
    string getAssignedDate(const string &studentId, const string &csvFile)
    {
        ifstream file(csvFile);
        if (!file.is_open())
        {
            cerr << "Error opening file: " << csvFile << endl;
            return "";
        }

        string line, assignedDate;
        while (getline(file, line))
        {
            vector<string> row = parseCSVLine(line); // Use the function from csvReadAndWrite.h
            if (row.size() >= 4 && row[0] == studentId)
            {
                assignedDate = row[3]; // Assuming the assigned date is in the 4th column
                break;
            }
        }

        file.close();
        return assignedDate;
    }
};
