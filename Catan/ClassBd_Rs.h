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

using namespace std;

class Building {
    protected:
        int victoryPoints;
        string owner;
    public:
        Building(const string& owner) : owner(owner) {}
        virtual ~Building() {}

        virtual int getVictoryPoints() const = 0;
        const string& getOwner() const { return owner; }
};

class Road : public Building {
    public:
        Road(const string& owner) : Building(owner) {
            victoryPoints = 0;
        }

    int getVictoryPoints() const override {
        return victoryPoints;
    }
};

class Settlement : public Building {
    public:
        Settlement(const string& owner) : Building(owner) {
            victoryPoints = 1;
    }

    int getVictoryPoints() const override {
        return victoryPoints;
    }
};

class City : public Building {
    public:
        City(const string& owner) : Building(owner) {
            victoryPoints = 2;
    }

    int getVictoryPoints() const override {
        return victoryPoints;
    }
};

class Resource {
    public:
        int wood;
        int grain;
        int brick;
        int ore;
        int sheep;
};

class Bank {
    public:
        map<string, int> resources;
        int roads;
        int settlements;
        int cities;
        int blockCards;
        int stealCards;

    Bank() {
        resources["wood"] = 19;
        resources["brick"] = 19;
        resources["sheep"] = 19;
        resources["grain"] = 19;
        resources["ore"] = 19;

        roads = 15;
        settlements = 5;
        cities = 4;

        blockCards = 5;
        stealCards = 5;
    }
};