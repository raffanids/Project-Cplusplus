
class SquareCatanBoard {
    vector<vector<tuple<bool, string, int, int, int>>> board;
    vector<Player> players;
    int currentPlayerIndex;

    public:
    SquareCatanBoard(int numPlayers) : currentPlayerIndex(0) {
        initializeBoard();
        players.reserve(numPlayers);
        for (int i = 0; i < numPlayers; ++i) {
            players.emplace_back("Player " + to_string(i + 1));
        }
    }
    
    void initializeBoard() {
        vector<string> resources = {"Sheep", "Wood", "Brick", "Grain", "Ore", "Sheep", "Grain", "Ore", "Brick", "Wood", "Sheep", "Grain", "Wood"};

        vector<int> numbers = {2, 3, 4, 5, 6, 8, 9, 10, 11, 12 ,5, 6};
        shuffle(numbers.begin(), numbers.end(),default_random_engine(static_cast<unsigned>(std::time(nullptr))));
        numbers.insert(numbers.begin() + 9, 0);

        vector<int> layout = {1, 3, 5, 3, 1};
        int resourceIndex = 0, numberIndex = 0;
        for (int rowSize : layout) {
            vector<tuple<bool, string, int, int, int>> row;
            for (int j = 0; j < rowSize; ++j) {
                row.emplace_back(true, resources[resourceIndex++], numbers[numberIndex++], 0, 0);
            }
            board.push_back(row);
        }
    }

    void displayBoard() const {
        cout << "----------------------------------------------" << endl;
        cout << "Catan Board Layout:\n\n";
        vector<string> resources;
        vector<int> numbers;
        for (const auto& row : board) {
            for (const auto& tile : row) {
                string resource = get<1>(tile);
                int number = get<2>(tile);
                cout << resource << " (" << number << ") ";
                
            }
            cout << "\n";
        }
        cout << "\n----------------------------------------------";
    }

    int rollDice() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1, 6);
        return dis(gen) + dis(gen);
    }

    void produceResources(vector<Player*>& players, int roll, Player* a) {
        cout << "Dice Roll: " << roll << "\n";
        for (const auto& row : board) {
            for (const auto& tile : row) {
                if (get<2>(tile) == roll && get<1>(tile) != "Desert") {
                    int houses = rand()%2+1;
                    string resource = get<1>(tile);
                    a->addResource(resource,houses);
                    cout << houses << " " << resource << "(s) produced for Player " << a->getName() << "\n";
                }
            }
        }
    }

    void nextTurn(Player* a,vector<Player*>& players) {
        cout << "\n----------------------------------------------\n";
        cout << "Player " << a->getName() << "'s turn:\n";
        int roll = rollDice();
        produceResources(players, roll, a);
        cout << "----------------------------------------------\n";
        a->displayStatus();
    }
    
    void incresenextTurn(Player* a,vector<Player*>& players) {
        cout << "\nPlayer " << a->getName() << "'s turn:\n";
        int roll = rollDice();
        produceResources(players, roll, a);
        cout << endl;
    }
};