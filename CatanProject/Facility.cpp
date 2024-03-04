#include "Facility.h"

#include <iostream>
#include <algorithm>
#include <random>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <ctime>
#include <tuple>
#include <iomanip>



void Facility::addFacility(const std::string facility, int amount)
{
    if (facility == "settlement")
        settlement += amount;

    if (facility == "road")
        road += amount;
    
    if (facility == "city")
        city += amount;
}

// for deductFacility in bank
void Facility::deductFacility(const std::string facility, int amount)
{
    if (facility == "settlement")
    {
        if (settlement >= amount)
            settlement -= amount;
        else if (settlement < amount)
            settlement = 0;
    }
    if (facility == "road")
    {
        if (road >= amount)
            road -= amount;
        else if (road < amount)
            road = 0;
    }
    if (facility == "city")
    {
        if (city >= amount)
            city -= amount;
        else if (city < amount)
            city = 0;
    }
}