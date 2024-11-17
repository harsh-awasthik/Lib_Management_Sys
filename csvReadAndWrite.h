#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
#pragma once

class csv 
{
    private:
    vector<string> parseCSVLine(const string& line)
    {
        vector<string> row;
        stringstream ss(line);
        string cell;

        while(getline(ss, cell, ','))
        {
            row.push_back(cell);
        }

        return row;
    }

    public:
    void csvWriteStudentList(const string& filename, string option1, string option2)
    {
        ofstream file(filename, ios::app);
        if(!file.is_open())
        {
            cerr <<"File is not Opened properly !"<<"\n";
        }
        file << option1 << "," << option2 <<"\n";
        file.close();
    }

    void csvWriteAssignedList(const string& filename, string option1, string option2, string date)
    {
        ofstream file(filename, ios::app);
        if(!file.is_open())
        {
            cerr <<"File is not Opened properly !"<<"\n";
        }
        file << option1 << "," << option2 << "," <<date <<"\n";
        file.close();
    }



    bool csvSearch(const string& filename, const string& searchTerm, const string& columnName) 
    {
        ifstream file(filename);
        string line;

        if (!file.is_open()) {
            cerr << "Could not open the file!" << endl;
            return false;
        }

        // Read the header line to find the column index
        getline(file, line);
        stringstream headerStream(line);
        string column;
        int columnIndex = -1;
        int currentIndex = 0;

        while (getline(headerStream, column, ',')) {
            if (column == columnName) {
                columnIndex = currentIndex;
                break;
            }
            currentIndex++;
        }

        if (columnIndex == -1) {
            cerr << "Column '" << columnName << "' not found!" << endl;
            return false;
        }

        cout << "Searching for '" << searchTerm << "' in column '" << columnName << "'..." << endl;

        // Search in the specified column
        bool found = false;
        while (getline(file, line)) {
            stringstream ss(line);
            string field;
            int currentColumn = 0;

            // Extract the value from the specific column
            while (getline(ss, field, ',')) {
                if (currentColumn == columnIndex) {
                    if (field == searchTerm) {
                        cout << "Match found: " << line << endl;
                        found = true;
                    }
                    break; // No need to parse the remaining columns
                }
                currentColumn++;
            }
            
        }

        if (!found) {
            cout << "No match found for '" << searchTerm << "' in column '" << columnName << "'." << endl;
        }
        return found;

        file.close();
    }

    void csvRead(const string& filename) 
    {
        ifstream file(filename);  // Open the file for reading
        if (!file.is_open()) {
            cerr << "Could not open the file!" << endl;
            return;
        }

        string line;
        while (getline(file, line)) {  // Read file line by line
            vector<string> row = parseCSVLine(line);  // Parse each line
            for (const string& cell : row) {
                cout << cell << " ";  // Print each cell separated by space
            }
            cout << endl;
        }

        file.close();
    }

    void csvRemove(const string& filename, int column, const string& targetValue) {
        ifstream file(filename);  // Open the original file for reading
        if (!file.is_open()) {
            cerr << "Could not open the file!" << endl;
            return;
        }

        string tempFilename = "temp.csv";  // Temporary file to store modified data
        ofstream tempFile(tempFilename);   // Open temporary file for writing
        if (!tempFile.is_open()) {
            cerr << "Could not open the temporary file!" << endl;
            return;
        }

        string line;
        bool found = false;
        while (getline(file, line)) {
            vector<string> row = parseCSVLine(line);
            if (column < row.size() && row[column] == targetValue) {
                found = true;  // Found the target row to delete
                continue;      // Skip writing this row to the temp file
            }

            // Write the line to the temporary file
            tempFile << line << "\n";
        }

        file.close();
        tempFile.close();

        // Replace the original file with the modified file if the row was found
        if (found) {
            remove(filename.c_str());
            rename(tempFilename.c_str(), filename.c_str());
            cout << "Row with value '" << targetValue << "' in column " << column << " deleted successfully." << endl;
        } else {
            remove(tempFilename.c_str());  // Delete temp file if no row was deleted
            cout << "No matching row found to delete." << endl;
        }
    }    
};
