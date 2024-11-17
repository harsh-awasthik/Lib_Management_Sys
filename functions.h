#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
#pragma once
using namespace std;

string toLowerCase(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

int selection(string* options, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << i+1 << ". " << options[i] << endl;
        options[i] = toLowerCase(options[i]);
    }



    while (true)
    {
        string input;
        cout << "Enter your Choice: ";
        cin >> input;
        for (int i = 0; i < size; i++)
        {
            if (input == to_string(i+1) || input == options[i])
            {   
                return i + 1;
            }
        }
        cout << "Incorrect Selection, Try again..." << endl;
    }
}