//used
#include <string>
#include <map>

class Player {
public:
    std::string name;
    std::map<std::string, int> resources;

    Player(const std::string& name) : name(name) {
        resources = {{"wood", 0}, {"brick", 0}, {"wool", 0}, {"grain", 0}, {"ore", 0}};
    }

    void addResource(const std::string& resource, int amount) {
        resources[resource] += amount;
    }
};
