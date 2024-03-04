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



#ifndef RESOURCE_HPP
#define RESOURCE_HPP

class resource
{
public:
    int wood = 0;
    int brick = 0;
    int wool = 0;
    int grain = 0;
    int ore = 0;

    void addResource(const std::string resource, int amount);
    void deductResource(const std::string resource, int amount);

};

#endif

