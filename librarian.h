#include <iostream>
#include "person.h"
#pragma once

class librarian : public person
{
private:
    string password = "Lib@2024";
    string Id = "Ashraf_Sir";
protected:
    string filename1 = "student.csv";   
    string filename2 = "books.csv";
    string filename3 = "assigned.csv";

public:

    void SignUp()
    {
        cout <<"Librarian not require sign up";
    }
    bool Login()
    {
        cout <<"Default ";
    }

    

    bool Login (string username, string password) 
    {
        int count = 0;
        while(count < 3) 
        {
            if (password == "Lib@2024" && username == "Ashraf_Sir" && count < 3)
            {
                cout << "Login Successful 🥳🥳 "<<"\n";
                return true;
            }
            else
            {               
                if(count < 3)
                {
                    cout << "Invalid USername or password !!"<<"\n"; 
                    count++; 
                }    
                else 
                {
                    cout << "Max Limit reached !!"<<"\n";
                }    
            }
            return false;
        }
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
        if(csvSearch(filename3, stud_id, 0))
        {
            return true;
        }
        return false;
    }

    bool SearchBookslist(string bookname)
    {
        if(csvSearch(filename2, bookname, 1))
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
        cout << "Student with student id " << stud_Id << " is added 🥳"<<"\n";
    }

    
};
//  cout <<""<<endl;
//         int z;
//         cin >>z
//         void list( z)
//         {
//             switch (x)
//             {
//             case 1:
//                 cout << "Read Student   list ";
//                 //filename = student.csv
//                 csvRead(filename1);
//                 break;
//             case 2:
//                 cout << " Update Student list ";
//                 // Update
//                 int y;
//                 cout << "For add press 1" << "\n"
//                     << "For remove press 2" << "\n";
//                 cin >> y;
//                 if (y == 1)
//                 {
//                     //filename = assigned.csv
//                     csvWrite(filename2, Name, Id);
//                 }
//                 else if (y == 2)
//                 {
//                     //csvRemove();
//                 }
//                 else
//                 {
//                     cout <<"Invalid Input 😥";
//                 }
//                 break;

//             case 3:
//                 cout << "Read Books list ";
//                 //filename = book.csv
//                 csvRead(filename3);
//                 break;
//             case 4:
//                 cout << "Update Student and Books list ";
//                 // Update
//                 int y;
//                 cout << "For add press 1" << "\n"
//                     << "For remove press 2" << "\n";
//                 cin >> y;
//                 if (y == 1)
//                 {
//                     //filename = assigned.csv
//                     csvWrite(filename2, Name, Id);
//                 }
//                 else if (y == 2)
//                 {
//                     //csvRemove();
//                 }
//                 else
//                 {
//                     cout <<"Invalid Input 😥";
//                 }
                
//                 default:
//                     break;
//             }
//         }