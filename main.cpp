#include <iostream>
using namespace std;
#include "librarian.h"
#include "library.h"



int main()
{
    int x;
    cout << "Enter : 5 for librarian and 10 for student "<<"\n";
    cout << "Enter your choice : ";
    cin >> x;

    //Librarian Section
    if (x == 5)
    {       
        cout << "Welcome to Librarian Section !!"<<"\n";
        cout << "For accessing your actions you need to login !!"<<"\n";

        librarian l1;

        
        int count = 0;
        while(count < 3)
        {
            string name, password;
            cout <<"Enter username : ";
            cin >> name;
            cout <<"Enter password : ";
            cin >> password;
            if(l1.Login(name, password))
            {
                cout << "Enter 1 : Read Student list"<<"\n"<< "Enter 2 : Read Books list"<<"\n"<< "Enter 3 : Update Student and Books list"<<"\n";
                int choice;
                cout << "Enter choice : ";
                cin >> choice;
                    
                switch (choice)
                {
                    case 1:
                        cout << "Reading Student list "<<"\n";                
                        l1.ReadStudentList();
                        break;
                    case 2:
                        cout << "Reading Books list "<<"\n";
                        l1.ReadBooksList();
                        break;               
                }
            }
           
        }
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
            string Name, Id;
            cout <<"Enter your name : ";
            cin >> Name;
            
            cout << "Enter your Enrollment no : ";
            cin >> Id;
            s1.SignUp(Name, Id);
        }

        else if (choice == 2)
        {
            string studentId;
            cout << "Enter Student Id : "<<"\n";
            cin >> studentId;

            bool signin =  s1.Login(studentId);

            if(signin == true)
            {
                
            }
            else
            {
                cout << "Invalid Id !!";
            }
        }
        
    }

    else
    {
        cout << "Invalid Choice !!";
    }

    return 0;
    
}