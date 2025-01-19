#include <iostream>
#include <fstream>
#include <sstream>
#include "csvReadAndWrite.h"

#pragma once

class Person : public virtual csv
{
    public:
    string Name;
    string Id;
};