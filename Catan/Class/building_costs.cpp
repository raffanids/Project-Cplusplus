#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <string>

using namespace std;

// Building 
class Building {
protected:
    int victoryPoints;
    std::string owner;

public:
    Building(const std::string& owner) : owner(owner) {}
    virtual ~Building() {}

    virtual int getVictoryPoints() const = 0;
    const std::string& getOwner() const { return owner; }
};

// ถนน
class Road : public Building {
public:
    Road(const std::string& owner) : Building(owner) {
        victoryPoints = 0; // ถนนมีค่าคะแนน=0
    }

    int getVictoryPoints() const override {
        return victoryPoints;
    }
};

// บ้าน
class Settlement : public Building {
public:
    Settlement(const std::string& owner) : Building(owner) {
        victoryPoints = 1; // บ้านมีค่าคะแนน=1
    }

    int getVictoryPoints() const override {
        return victoryPoints;
    }
};

// ตัวเมือง
class City : public Building {
public:
    City(const std::string& owner) : Building(owner) {
        victoryPoints = 2; // ตัวเมืองมีค่าคะแนน=2
    }

    int getVictoryPoints() const override {
        return victoryPoints;
    }
};

// ผู้เล่น
class Player {
private:
    std::string name;
    std::map<std::string, int> resources;
    std::vector<std::unique_ptr<Building>> buildings; 
    
public:
    Player(const std::string& playerName) : name(playerName) {
        // เริ่มต้นทรัพยากรที่มีค่าเป็นศูนย์
        resources["wood"] = 0;
        resources["brick"] = 0;
        resources["wool"] = 0;
        resources["grain"] = 0;
        resources["ore"] = 0;
    }

    void addResource(const std::string& resource, int amount) {
        resources[resource] += amount;
    }
    
    bool buildRoad() {
        // ตรวจสอบทรัพยากร
        if (resources["wood"] >= 1 && resources["brick"] >= 1) {
            buildings.push_back(std::make_unique<Settlement>(name));
            // ทรัพยาการในการสร้างถนน
            resources["wood"] -= 1;
            resources["brick"] -= 1;
            return true;
        }
        return false;
    }

    bool buildSettlement() {
        // ตรวจสอบทรัพยากร
        if (resources["wood"] >= 1 && resources["brick"] >= 1 && resources["wool"] >= 1 && resources["grain"] >= 1) {
            buildings.push_back(std::make_unique<Settlement>(name));
            // ทรัพยาการในการสร้างบ้าน
            resources["wood"] -= 1;
            resources["brick"] -= 1;
            resources["wool"] -= 1;
            resources["grain"] -= 1;
            return true;
        }
        return false;
    }

    bool buildCity() {
        // ตรวจสอบทรัพยากร
        if (resources["grain"] >= 2 && resources["ore"] >= 3) {
            buildings.push_back(std::make_unique<City>(name));
            // ทรัพยาการในการสร้างเมือง
            resources["grain"] -= 2;
            resources["ore"] -= 3;
            return true;
        }
        return false;
    }

    int calculateVictoryPoints() {
        int points = 0;
        for (const auto& building : buildings) {
            points += building->getVictoryPoints();
        }
        return points;
    }
    
    // เก็บคะแนนผู้เล่น
    void displayStatus() {
        std::cout << "Player: " << name << "\nResources:\n";
        for (const auto& resource : resources) {
            std::cout << resource.first << ": " << resource.second << "\n";
        }
        std::cout << "Victory Points: " << calculateVictoryPoints() << "\n\n";
    }
};

