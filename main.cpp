#include <iostream> 
#include <sstream> 
#include <regex> 
#include "library.h"
#include "functions.h"
using namespace std;

bool isValidDate(const string& date) {
    // Regex pattern -> DD-MM-YYYY 
    regex datePattern("^(0[1-9]|[12][0-9]|3[01])-(0[1-9]|1[0-2])-[0-9]{4}$");
    return regex_match(date, datePattern);
}

string studentId;
    bool isValidStudentId(const string &id)
    {
        regex idPattern("G[A-Z]\\d{4}"); // Pattern: G followed by any uppercase letter and 4 digits
        return regex_match(id, idPattern);
    }

int main()
{
    int choice;
    string date;
    string bookName; // add bookname by kp
    
    while(true){
        cout << "Enter date (DD-MM-YYYY) : ";
        cin >> date;
        if (isValidDate(date)) {
            break;
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
        cout << "For accessing your actions you need to cd !!"<<"\n";

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
                        librarian.AddBook(bookname); 
                        break;                     
                    }
                    case 4:
                    {
                        
                        cout << "Enter Book name : ";
                        cin >> bookName;
                        librarian.removeBook(bookName); //Needed Changes//
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

        if(choice == 1)
        {         
            while (true){
                cout << "create your student_id (Format: G<AnyLetter>1234): ";
                cin >> studentId;
                if (isValidStudentId(studentId)) {
                break;  
                } else {
                    cout << "Invalid student_id . Please enter in this correct format.\n";
                }
            }
            student.SignUp(studentId);
        }
        else
        {           
            while (true){
                cout << "Enter your student_id (Format: G<AnyLetter>1234): ";
                cin >> studentId;
                if (isValidStudentId(studentId)) {
                break;  
                } else {
                    cout << "Invalid student_id . Please enter the correct format.\n";
                }
            }
            student.Login(studentId);
        }

        /*code for borrow and deposit */
        string options1[] = {"Deposit", "Borrow"};
        choice = selection(options1, 2);

                
        switch (choice)
        {
            case 1: 
            {
                string assignedDate = library.getAssignedDate(studentId, "assigned.csv");
                if (assignedDate.empty()) {
                    cout << "No assigned date found for the student.\n";
                } else {
                    cout << "Assigned Date: " << assignedDate << endl;

                    int fine = library.calculateFine(date,assignedDate);
                    cout << "Fine: Rs. " << fine << endl;
                    library.deposit(studentId,date,bookName);
                }
                break;
            }
            case 2:
            {
                cout << "Enter Book name: "; // Asking for book name for borrowing
                cin >> bookName;
                library.borrow(studentId, bookName, date); // Borrow method updated to pass bookName
                break; 
            }              
        }     
    }
}
