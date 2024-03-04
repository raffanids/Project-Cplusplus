
class Player {
private:
    string name;
    map<string, int> resources;
    vector<unique_ptr<Building>> buildings;
    vector<string> specialcard;
    bool blocked;

public:
    Player(const string& playerName) : name(playerName), blocked(false) {
        resources["wood"] = 0;
        resources["brick"] = 0;
        resources["sheep"] = 0;
        resources["grain"] = 0;
        resources["ore"] = 0;
    }

    string getName() const {
        return name;
    }
    
    map<string, int>& getResources() {
        return resources;
    }

    void initializeResources() {
        resources["wood"] = 0;
        resources["brick"] = 0;
        resources["sheep"] = 0;
        resources["grain"] = 0;
        resources["ore"] = 0;
    }

    vector<string> getSpecialCard() const {
        return specialcard;
    }

    bool isBlocked() const {
        return blocked;
    }

    void setBlocked(bool isBlocked) {
        blocked = isBlocked;
    }
    
    void addResource(string resource,int amount) {
        transform(resource.begin(), resource.end(), resource.begin(), ::tolower);
        resources[resource] += amount;
    }
    
    bool deductResource(const string& resource, int amount) {
        if (resources[resource] >= amount) {
            resources[resource] -= amount;
            return true;
        }
    return false;
    }
    
    void removeSpecialCard(const string& cardName) {
        specialcard.erase(remove(specialcard.begin(), specialcard.end(), cardName), specialcard.end());
    }
    
    bool tradeWithBank(Bank& bank, const string& offerResource, int offerAmount, const string& requestResource, int requestAmount) {
        if (resources[offerResource] >= offerAmount && bank.resources[requestResource] >= requestAmount) {
            resources[offerResource] -= offerAmount;
            resources[requestResource] += requestAmount;
            bank.resources[requestResource] -= requestAmount;
            bank.resources[offerResource] += offerAmount;
            cout << "Trade successful: " << offerAmount << " " << offerResource << " for " << requestAmount << " " << requestResource << endl;
            return true;
        } else {
            cout << "Trade failed due to insufficient resources." << endl;
            return false;
        }
    }

    bool tradeWithPlayer(Player& player, const string& offerResource, int offerAmount, const string& requestResource, int requestAmount) {
        if (resources[offerResource] >= offerAmount && player.getResources()[requestResource] >= requestAmount) {
            deductResource(offerResource, offerAmount);
            player.addResource(offerResource, offerAmount);
            player.deductResource(requestResource, requestAmount);
            addResource(requestResource, requestAmount);
            cout << "Trade successful between " << name << " and " << player.getName() << endl;
            return true;
        } else {
            cout << "Trade failed due to insufficient resources." << endl;
            return false;
        }
    }
    
    void drawSpecialCard(Bank& bank) {
        int card = rand() % 2 + 1;
        if (card == 1) {
            if (bank.stealCards > 0) {
                specialcard.push_back("stealcard");
                bank.stealCards--;
                cout << "You drew a special card (steal). Now have " << bank.stealCards << " steal card(s) left in the bank." << endl;
            } else {
                cout << "No steal cards left in the bank." << endl;
            }
                } else if (card == 2) {
                    if (bank.blockCards > 0) {
                    specialcard.push_back("blockcard"); 
                    bank.blockCards--;
                    cout << "You drew a special card (block). Now have " << bank.blockCards << " block card(s) left in the bank." << endl;
                } else {
                    cout << "No block cards left in the bank." << endl;
                }
            }
    }

    void stealResource(Player& targetPlayer, map<string, int>& targetResources, const string& resourceType, int amount = 1) {
        if (targetResources[resourceType] >= amount) {
            targetResources[resourceType] -= amount;
            resources[resourceType] += amount;
        } else {
            cout << "Cannot steal the specified resource from the target. Only stole what was available." << endl;
        }
    }

    void displayStatus() {
        cout << "----------------------------------------------" << endl;
        cout << "Player " << name << " Resources :\n";
        for (const auto& resource : resources) {
            cout << resource.first << ": " << resource.second << "\n";
        }
        cout << "Victory Points: " << calculateVictoryPoints() << "\n";
        cout << "----------------------------------------------\n";
    }

    int calculateVictoryPoints() {
        int points = 0;
        for (const auto& building : buildings) {
            points += building->getVictoryPoints();
        }
        return points;
    }

    bool buildRoad() {
        if (resources["wood"] >= 1 && resources["brick"] >= 1) {
            buildings.push_back(make_unique<Road>(name));
            resources["wood"] -= 1;
            resources["brick"] -= 1;
            return true;
        }
        return false;
    }

    bool buildSettlement() {
        if (resources["wood"] >= 1 && resources["brick"] >= 1 && resources["sheep"] >= 1 && resources["grain"] >= 1) {
            buildings.push_back(make_unique<Settlement>(name));
            resources["wood"] -= 1;
            resources["brick"] -= 1;
            resources["sheep"] -= 1;
            resources["grain"] -= 1;
            return true;
        }
        return false;
    }

    bool buildCity() {
        if (resources["grain"] >= 2 && resources["ore"] >= 3) {
            buildings.push_back(make_unique<City>(name));
            resources["grain"] -= 2;
            resources["ore"] -= 3;
            return true;
        }
        return false;
    }
};