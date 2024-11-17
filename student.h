#include <iostream>
#include "person.h"
#pragma once

class student : public person
{
    private :
    string filename = "student.csv";

    public :

    void SignUp()
    {
        cout << "";
    }

    void SignUp(string Name, string Id) 
    {   
        csvWriteStudentList(filename, Name, Id);
        cout <<"\n"<<"Sign Up successful !!"<<"\n";
    }

    bool Login()
    {
        cout <<"";
    }

    bool Login(string studentId)
    {        
        string colnname = "Student_Id";
        if (csvSearch(filename , studentId, colnname))
        {
            cout << "Login successful " <<endl;
            return true;
        }

        else
        {
            cout <<"UserId not found !"<<"\n";
            cout <<"Enter valid Id 🙂"<<"\n";
        }
        return false;
    }


};

