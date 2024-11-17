#include <iostream>
using namespace std;
#include "library.h"

int main()
{
    string date;
    cout << "Enter date (DD-MM-YYYY) : ";
    cin >> date; 
    int x;
    cout << "Enter : 5 for librarian and 10 for student "<<"\n";
    cout << "Enter your choice : ";
    cin >> x;


    //Librarian Section
    if (x == 5) /*Need Change by Harsh*/
    {       
        cout << "Welcome to Librarian Section !!"<<"\n";
        cout << "For accessing your actions you need to login !!"<<"\n";

        librarian l1; /*Need Change */

        int count = 0;
        while(count < 3) /*Need Change*/
        {
            string name, password;
            cout <<"Enter username : ";
            cin >> name;
            cout <<"Enter password : ";
            cin >> password;
            if(l1.Login(name, password) && count < 3)
            {               
                cout << "Enter 1 : Read Student list"<<"\n"<< "Enter 2 : Read Books list"<<"\n"<<"Enter 3 : Add New Book "<<"\n"<<"Enter 4 : Remove Unavailable Book "<<"\n";
                int choice;
                cout << "Enter choice : ";
                cin >> choice;
                    
                switch (choice)
                {
                    case 1:
                    {
                        cout << "Reading Student list "<<"\n";                
                        l1.ReadStudentList(); 
                        return 0;
                    }
                    case 2:
                    {
                        cout << "Reading Books list "<<"\n";
                        l1.ReadBooksList();
                        return 0;
                    }
                    case 3:
                    {
                        string bookname, book_Id;
                        cout << "Enter Book name : ";
                        cin >> bookname;
                        cout << "Enter Book Id : ";
                        cin >> book_Id;

                        l1.AddBook(bookname, book_Id);
                        return 0;                       
                    }
                    case 4:
                    {
                        string bookname;
                        cout << "Enter Book name : ";
                        cin >> bookname;
                        l1.removeBook(bookname); //Needed Changes//
                        return 0;
                    }
                }
            }
            else
            {
                count++;
            }           
        }
        cout << "Max limit reached !!"<<"\n";
    }   
    
    // Student Section
    else if(x == 10)
    {
        int choice;
        cout << "For SignUp : 1"<<"\n"<<"For Login : 2"<<"\n";
        cout << "Enter your choice : ";
        cin >> choice;

        student s1;
        library a1;

        if(choice == 1)
        {
            int count = 0;           
            string Name, Id;
            cout <<"Enter your name : ";
            cin >> Name;
            cout << "Enter your Enrollment no : ";
            cin >> Id;
            s1.SignUp(Name, Id);

            cout << "Enter 1 : Deposit"<<"\n"<< "Enter 2 : Borrow"<<"\n"; /*Only Borrow*/
            int choice;
            cout << "Enter choice : ";
            cin >> choice;
       
            switch (choice)
            {
                case 1:  
                {                   
                    a1.deposit(Id, date);
                    break;
                    return 0;
                }
                case 2:
                {                    
                    string bookname;
                    cout <<"\n"<< "Enter bookname : ";
                    cin >> bookname;
                    a1.borrow(Id, bookname, date); 
                    return 0; 
                }             
            } 
        }

        else if (choice == 2)
        {            
            int count = 0;
            while (count < 3) /*Need Change*/
            {
                string studentId;
                cout << "Enter Student Id : ";
                cin >> studentId;
               if(s1.Login(studentId) && count < 3)
                {
                    /*code for borrow and deposit */
                    cout << "Enter 1 : Deposit"<<"\n"<< "Enter 2 : Borrow"<<"\n";
                    int choice;
                    cout << "Enter choice : ";
                    cin >> choice;
                            
                    switch (choice)
                    {
                        case 1: 
                        {
                            a1.deposit(studentId, date);
                            return 0;
                        }
                        case 2:
                        {
                            a1.borrow(studentId, "", date);
                            return 0;
                        }              
                    }
                }
                else
                {
                    count ++;
                    cout << "Invalid Id !!"<<"\n";
                }
            }
            cout << "Max limit reached !!"<<"\n";         
        }      
    }
    else
    {
        cout << "Invalid Choice !!";
    }
  
}