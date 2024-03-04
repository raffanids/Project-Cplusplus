#pragma once
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


#ifndef	FACILITY_HPP
#define	FACILITY_HPP

class Facility
{
public:
    int road = 0;
    int settlement = 0;
    int city = 0;

    void addFacility(const std::string facility, int amount);

    // for deductFacility in bank
    void deductFacility(const std::string facility, int amount);
        

    
};





#endif
