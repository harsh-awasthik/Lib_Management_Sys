#include <iostream>
#include "person.h"
#pragma once

class Student : public Person
{
private:
    string filename = "student.csv";

public:
    string studentId;
    bool isValidStudentId(const string &id)
    {
        regex idPattern("G[A-Z]\\d{4}"); // Pattern: G followed by any uppercase letter and 4 digits
        return regex_match(id, idPattern);
    }

    string SignUp(const string &studentId)
    {
        string Name;
        cout << "Enter your name : ";
        cin >> Name;
        csvWriteStudentList(filename, Name, studentId);
        cout << "\n"
             << "Sign Up successful !!" << "\n";
        return studentId;
    }

    string Login(const string &studentId)
    {
        string colnname = "Student_Id";
        if (csvSearch(filename, studentId, colnname))
        {
            cout << "Login successful " << endl;
            return studentId;
        }
        else
        {
            cout << "No match found for '" << studentId << "' in column 'Student_Id'." << endl;
            return "";
        }
    }
};
