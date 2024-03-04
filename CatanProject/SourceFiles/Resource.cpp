#include "Resource.h"

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


    

void resource::addResource(const std::string resource, int amount = 1) 
{
        if (resource == "wood") 
            wood += amount;
        if (resource == "brick")
            brick += amount;
        if (resource == "wool")
            wool += amount;
        if (resource == "grain")
            grain += amount;
        if (resource == "ore")
            ore += amount;
}


void resource::deductResource(const std::string resource, int amount = 1)
{
    if (resource == "wood")
    {
        if (wood >= amount)
            wood -= amount;
        else if (wood < amount)
            wood = 0;
    }
    if (resource == "brick")
    {
        if (brick >= amount)
            brick -= amount;
        else if (brick < amount)
            brick = 0;
    }
    if (resource == "wool")
    {
        if (wool >= amount)
            wool -= amount;
        else if (wool < amount)
            wool = 0;
    }
    if (resource == "grain")
    {
        if (grain >= amount)
            grain -= amount;
        else if (grain < amount)
            grain = 0;
    }
    if (resource == "ore")
    {
        if (ore >= amount)
            ore -= amount;
        else if (ore < amount)
            ore = 0;
    }
    
}

    
