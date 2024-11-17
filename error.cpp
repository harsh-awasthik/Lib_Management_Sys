// #include <iostream>
// #include <fstream>
// #include <sstream>
// #include <string>
// #include <vector>
// using namespace std; 

// vector<string> parseCSVLine(const string& line);

// bool csvSearch(const string& filename, const string& search_item, int column)
//     {
//         ifstream file(filename);
//         if (!file.is_open())
//         {
//             cerr <<"File not opened correctly !"<<"\n";
//             return false;
//         }

//         string line;
//         vector<string> row = parseCSVLine(line);
        
//         if (column < row.size() && row[column] == search_item)
//         {
//             return true;
//         }
        
//         file.close();
//     }

// vector<string> parseCSVLine(const string& line)
//     {
//         vector<string> row;
//         stringstream ss(line);
//         string cell;

//         while(getline(ss, cell, ','))
//         {
//             row.push_back(cell);
//         }

//         return row;
//     }

// int main()
// {
//     string filename = "student.csv";
//     string searchItem = "GM7106";

//     cout <<csvSearch(filename, searchItem, 1);
// }

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

bool searchInColumn(const string& filename, const string& searchTerm, const string& columnName) {
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

int main() {
    string filename = "student.csv";
    string st = "GM7106";
    string colmName = "Student_Id";
    
    cout << searchInColumn(filename, st, colmName);

    return 0;
}
