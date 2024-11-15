#include <iostream>
#include "student.h"
#include "librarian.h"

#pragma once

class library : public student, librarian 
{
    public:

    void borrow(string stud_id, string bookname, string date)
    {       
        if (SearchAssignedList(stud_id))
        {
            cout << "Student already have a book !!"<<"\n";
            cout << "No new can be provided until you already have a book ";
            return;
        }
        else
        {
            if(SearchBookslist(bookname))
            {
                cout <<"Book is available !"<<"\n";
                cout << bookname <<" is assigned to student with student Id " << stud_id;
                AddStudent(stud_id, bookname /*we should write here book id*/, date);
                removeBook(bookname);
            }
        }
    }

    double fineCalculator(string stud_id)
    {

    }

    void deposit (string stud_id)
    {
        
    }
};