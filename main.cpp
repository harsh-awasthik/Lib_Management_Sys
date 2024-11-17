#include <iostream>
using namespace std;
#include "library.h"
#include "functions.h"

int main()
{
    int choice;
    string date;
    cout << "Enter date (DD-MM-YYYY) : ";
    cin >> date; 

    string options[] = {"Librarian", "Student"};
    int x = selection(options, 2);
 
    //Librarian Section
    if (x == 1)
    {       
        cout << "Welcome to Librarian Section !!"<<"\n";
        cout << "For accessing your actions you need to login!!"<<"\n";

        Librarian librarian;

        bool foo = librarian.Login();

        if(foo)
        {               
            string options[] = {"Read Student list", "Read Books list", "Add New Book", "Remove Unavailable Book"};
            choice = selection(options, 4);
                
            switch (choice)
            {
                case 1:
                {
                    cout << "Reading Student list "<<"\n";                
                    librarian.ReadStudentList(); 
                    return 0;
                }
                case 2:
                {
                    cout << "Reading Books list "<<"\n";
                    librarian.ReadBooksList();
                    return 0;
                }
                case 3:
                {
                    string bookname, book_Id;
                    cout << "Enter Book name : ";
                    cin >> bookname;
                    cout << "Enter Book Id : ";
                    cin >> book_Id;

                    librarian.AddBook(bookname, book_Id);
                    return 0;                       
                }
                case 4:
                {
                    string bookname;
                    cout << "Enter Book name : ";
                    cin >> bookname;
                    librarian.removeBook(bookname); //Needed Changes//
                    return 0;
                }
            }
        }
        else
        {
            return 0;
        }
    }   
    
    // Student Section
    else
    {
        string options2[] = {"Signup", "Login"};
        choice = selection(options2, 2);

        Student student;
        Library library;

        string studentId;
        if(choice == 1)
        {         
            
            studentId = student.SignUp();
        }

        else
        {            
            studentId = student.Login();
        }

        /*code for borrow and deposit */
        string options1[] = {"Deposit", "Borrow"};
        choice = selection(options1, 2);
                
        switch (choice)
        {
            case 1: 
            {
                library.deposit(studentId, date);
                return 0;
            }
            case 2:
            {
                library.borrow(studentId, "", date);
                return 0;
            }              
        }     
    }
}