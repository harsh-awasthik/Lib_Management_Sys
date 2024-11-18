#include <iostream>
#include "student.h"
#include "librarian.h"

#pragma once

class Library : public Student, Librarian 
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

    // Function to check if a student ID exists in the assigned list

    bool searchAssignedList(const char* stud_id) {

        ifstream file("assigned.csv");

        if (!file) {
            cout << "Error: Unable to open assigned.csv.\n";
            return false;
        }



        char line[MAX_LINE_LEN];
        while (file.getline(line, MAX_LINE_LEN)) {
            if (strstr(line, stud_id)) { // Check if the line contains the student ID
                file.close();
                return true;
            }
        }

        file.close();
        return false;

    }

    // Function to update the book’s availability in the books.csv file

    void updateBookAvailability(const char* book_id, const char* bookname) {

        fstream file("books.csv", ios::in | ios::out);

        if (!file) {
            cout << "Error: Unable to open books.csv for updating availability.\n";
            return;
        }



        char line[MAX_LINE_LEN];

        long pos;

        while (file.getline(line, MAX_LINE_LEN)) {

            if (strstr(line, book_id)) { // Check if the line contains the book ID

                pos = file.tellg();     // Get the current position

                file.seekp(pos - strlen(line) - 1); // Seek to the beginning of the line



                // Create the updated line

                char updated_line[MAX_LINE_LEN];

                snprintf(updated_line, MAX_LINE_LEN, "%s,\"%s\",true", book_id, bookname);

                file << updated_line << endl; // Write the updated line

                break;

            }

        }



        file.close();

    }



    // Function to remove a student record from assigned.csv

    void csvRemove(const char* filename, const char* key) {

        ifstream file(filename);

        ofstream temp("temp.csv");

        if (!file || !temp) {

            cout << "Error: Unable to open files for modification.\n";

            return;

        }



        char line[MAX_LINE_LEN];

        while (file.getline(line, MAX_LINE_LEN)) {

            if (!strstr(line, key)) { // Copy all lines except the one with the key

                temp << line << endl;

            }

        }



        file.close();

        temp.close();



        // Replace the original file with the temporary file

        remove(filename);

        rename("temp.csv", filename);

    }



public:

    void deposit(const char* stud_id, const char* date, const char* bookname) {

        // Step 1: Check if the student ID exists in the assigned list

        if (!searchAssignedList(stud_id)) {

            cout << "Error: No record found for student ID: " << stud_id 

                 << " in the assigned list.\n";

            return;

        }



        // Step 2: Retrieve the book ID corresponding to the book name

        ifstream booksFile("books.csv");

        if (!booksFile) {

            cout << "Error: Unable to open books.csv.\n";

            return;

        }



        char book_id[50] = "";

        char line[MAX_LINE_LEN];

        while (booksFile.getline(line, MAX_LINE_LEN)) {

            if (strstr(line, bookname)) { // Check if the line contains the book name

                sscanf(line, "%[^,]", book_id); // Extract the book ID from the line

                break;

            }

        }



        booksFile.close();



        if (strlen(book_id) == 0) {

            cout << "Error: Book name \"" << bookname << "\" not found in the books list.\n";

            return;

        }



        // Step 3: Update the book’s availability in the books list

        updateBookAvailability(book_id, bookname);



        // Step 4: Remove the student record from assigned.csv

        csvRemove("assigned.csv", stud_id);



        // Step 5: Log the successful deposit

        cout << "Book \"" << bookname << "\" has been returned by student ID: " 

             << stud_id << " on " << date << ". Availability of the book is now set to true.\n";

    }

};
