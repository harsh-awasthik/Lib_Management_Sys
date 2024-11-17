#include <iostream>
#include <fstream>
#include <sstream>
#include "csvReadAndWrite.h"

using namespace std;

#pragma once

class Person : public csv
{
    public:
    string Name;
    string Id;
};