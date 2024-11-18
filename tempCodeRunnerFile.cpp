
        } else {
            cout << "Invalid date format! Please enter the date in DD-MM-YYYY format.\n";
        }
    } 

    string options[] = {"Librarian", "Student"};
    int x = selection(options, 2);
 
    //Librarian Section
    if (x == 1)