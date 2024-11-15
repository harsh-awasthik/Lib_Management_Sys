#include <iostream>
#include <fstream>
#include <sstream>
#include "csvReadAndWrite.h"

using namespace std;

#pragma once

class person : public csv
{
    public:
    string Name;
    string Id;
    
    virtual bool Login() = 0;
    virtual void SignUp() = 0;

};