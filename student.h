#include <iostream>
#include "person.h"
#pragma once

class Student : public Person
{
    private :
    string filename = "student.csv";

    public :

    string SignUp() 
    {   
        string Name, Id;
        cout <<"Enter your name : ";
        cin >> Name;
        cout << "Enter your Enrollment no : ";
        cin >> Id;
        csvWriteStudentList(filename, Name, Id);
        cout <<"\n"<<"Sign Up successful !!"<<"\n";
        return Id;
    }

    string Login()
    { 
        int attempts = 3;
        while (attempts > 0)
        {
            string studentId;
            cout << "Enter Student Id : ";
            cin >> studentId;

            string colnname = "Student_Id";
            if (csvSearch(filename , studentId, colnname))
            {
                cout << "Login successful " <<endl;
                return studentId;
            }

            else
            {
                cout <<"UserId not found !"<<"\n";
                cout <<"Enter valid Id 🙂"<<"\n";
                attempts--;
            }
        }
        cout << "Maximum attempts reached..." << endl;
        return "None";
    }


};

