#include <iostream> 
#include <regex> 
using namespace std;
#include "library.h"
#include "functions.h"

bool isValidDate(const string& date) {
    // Regex pattern for DD-MM-YYYY format
    regex datePattern("^(0[1-9]|[12][0-9]|3[01])-(0[1-9]|1[0-2])-[0-9]{4}$");
    return regex_match(date, datePattern);
}

int main()
{
    int choice;
    string date;
    
    while(true){
        cout << "Enter date (DD-MM-YYYY) : ";
        cin >> date;
        if (isValidDate(date)) {
            break; // Exit loop if date is valid
        } else {
            cout << "Invalid date format! Please enter the date in DD-MM-YYYY format.\n";
        }
    } 

    string options[] = {"Librarian", "Student"};
    int x = selection(options, 2);
 
    //Librarian Section
    if (x == 1)
    {  
        cout << "----------------------------------" << endl;     
        cout << "Welcome to Librarian Section !!"<<"\n";
        cout << "For accessing your actions you need to login!!"<<"\n";

        Librarian librarian;

        bool foo = librarian.Login();

        if(foo)
        {                
            while (true)
            {
                cout << "----------------------------------" << endl;
                string options[] = {"Read Student list", "Read Books list", "Add New Book", "Remove Unavailable Book", "Exit"};
                choice = selection(options, 5);
                switch (choice)
                {
                    case 1:
                    {
                        cout << "Reading Student list "<<"\n";                
                        librarian.ReadStudentList(); 
                        break;
                    }
                    case 2:
                    {
                        cout << "Reading Books list "<<"\n";
                        librarian.ReadBooksList();
                        break;
                    }
                    case 3:
                    {
                        string bookname, book_Id;
                        cout << "Enter Book name : ";
                        cin >> bookname;
                        cout << "Enter Book Id : ";
                        cin >> book_Id;

                        librarian.AddBook(bookname, book_Id); 
                        break;                     
                    }
                    case 4:
                    {
                        string bookname;
                        cout << "Enter Book name : ";
                        cin >> bookname;
                        librarian.removeBook(bookname); //Needed Changes//
                        break;
                    }
                    case 5:
                    {
                        cout << "Exiting Document...." << endl;
                        return 0;
                    }
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
        cout << "----------------------------------" << endl;
        cout << "Welcome to Student Section !!"<<"\n";


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