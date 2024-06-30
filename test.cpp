// #include <bits/stdc++.h>
// using namespace std;

// bool compareFiles(const string &outputFilename, const string &pregen_outputFilename)
// {
//     ifstream output(outputFilename);
//     ifstream pregen_output(pregen_outputFilename);

//     if (!output.is_open() || !pregen_output.is_open())
//     {
//         cerr << "Error opening files: " << outputFilename << " or " << outputFilename << endl;
//         return false;
//     }

//     string line1, line2;
//     while (getline(output, line1) && getline(pregen_output, line2))
//     {
//         if (line1 != line2)
//         {
//             cerr << "Mismatch in line: " << output.tellg() + (long long int)2 << endl;
//             return false;
//         }
//     }

//     // Check if any lines are left in either file
//     if (output.eof() != pregen_output.eof())
//     {
//         cerr << "Files have different line count." << endl;
//         return false;
//     }

//     return true;
// }

// class Node
// {
// public:
//     int data;
//     Node *left;
//     Node *right;
//     Node(int d)
//     {
//         data = d;
//         left = NULL;
//         right = NULL;
//     }
// };

// class Solution
// {
// public:
//     Node *insert(Node *root, int data)
//     {
//         if (root == NULL)
//         {
//             return new Node(data);
//         }
//         else
//         {
//             Node *cur;
//             if (data <= root->data)
//             {
//                 cur = insert(root->left, data);
//                 root->left = cur;
//             }
//             else
//             {
//                 cur = insert(root->right, data);
//                 root->right = cur;
//             }

//             return root;
//         }
//     }
//     /*The tree node has data, left child and right child
//     class Node {
//         int data;
//         Node* left;
//         Node* right;
//     };

//     */
//     int height(Node *root)
//     {
//         if (root == nullptr)
//         {
//             return 0;
//         }
//         else
//         {
//             int l_depth = height(root->left);
//             int r_depth = height(root->right);

//             if (l_depth > r_depth)
//                 return l_depth + 1;
//             else
//                 return r_depth + 1;
//         }
//     }

// }; // End of Solution

// int main()
// {
//     int check = 0, cases = 10;
//     for (int i = 1; i <= cases; ++i)
//     {

//         ofstream output("t_output" + to_string(i) + ".txt");
//         ifstream input("input" + to_string(i) + ".txt");

//         Solution myTree;
//         Node *root = NULL;
//         int t;
//         int data;
//         input >> t;
//         while (t-- > 0)
//         {
//             input >> data;
//             root = myTree.insert(root, data);
//         }
//         int height = myTree.height(root);
//         output << height;

//         output.close();
//         input.close();

//         if (compareFiles("t_output" + to_string(i) + ".txt", "output" + to_string(i) + ".txt"))
//         {
//             cout << "Test case " << i << " passed." << endl;
//             check++;
//         }
//         else
//         {
//             cout << "Test case " << i << " failed." << endl;
//         }
//     }
//     cout << check << "/" << cases << " cases passed." << endl;
//     return 0;
// }

// #include <iostream>
// #define N 100
// using namespace std;

// int main() {
//     char input[N], cmp[N];
//     cin.getline(input, N);
//     cin.getline(cmp, N);

//     char *p1 = input, *p2 = cmp;
//     int size1 = 0, size2 = 0;
//     while (*p1 != '\0') {
//         size1++;
//         p1++;
//     }
//     while (*p2 != '\0') {
//         size2++;
//         p2++;
//     }
//     p1 = input, p2 = cmp;

//     bool isEqual = true;
//     bool firstHalf = false;
//     bool lastHalf = false;

//     while (lastHalf == false) {
//         cout << "checking '" << *p1 << "' and '" << *p2 << "': ";
//         if (*p2 == '*') {
//             cout << "wildcard!\n";
//             if (firstHalf)
//                 lastHalf = true;
//             if (!firstHalf)
//                 firstHalf = true;

//             p1 = input + size1;
//             p2 = cmp + size2;
//         } else if (*p2 != *p1) {
//             cout << "not equal!\n";
//             isEqual = false;
//             break;
//         } else {
//             cout << "equal!\n";
//         }

//         if (!firstHalf) {
//             p1++;
//             p2++;
//         } else {
//             p1--;
//             p2--;
//         }

//         if(*p1 == '\0' && *p2 == '\0') {
//             isEqual = true;
//             break;
//         }
//     }

//     cout << isEqual;
//     return 0;
// }

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Missile {
public:
    string id;
    string name;
    int damage;
    int usageCount;

    Missile(string id, string name, int damage, int usageCount)
        : id(id), name(name), damage(damage), usageCount(usageCount) {}

    bool operator==(const Missile &other) const {
        return id == other.id;
    }
};

class Meteor {
public:
    string id;

    Meteor(string id) : id(id) {}

    virtual void collide() = 0;
    virtual int getDamage() = 0;
};

class AlphaMeteor : public Meteor {
public:
    AlphaMeteor(string id) : Meteor(id) {}

    void collide() override {
        cout << "Alpha Alpha Bum" << endl;
    }

    int getDamage() override {
        return 2;
    }
};

class BetaMeteor : public Meteor {
public:
    BetaMeteor(string id) : Meteor(id) {}

    void collide() override {
        cout << "Beta beta" << endl;
    }

    int getDamage() override {
        return 3;
    }
};

class Spaceship {
public:
    string id;
    string name;

    Spaceship(string id, string name) : id(id), name(name) {}

    virtual void attack(Spaceship &target) = 0;
    virtual int getHealth() = 0;
    virtual void takeDamage(int damage) = 0;
};

class PlayerSpaceship : public Spaceship {
public:
    int health;
    vector<Missile> missiles;

    PlayerSpaceship(string id, string name, int health)
        : Spaceship(id, name), health(health) {}

    void attack(Spaceship &target) override {
        if (!missiles.empty()) {
            Missile &missile = *max_element(missiles.begin(), missiles.end(), [](const Missile &a, const Missile &b) {
                return a.damage < b.damage;
            });
            cout << "Player attacks with " << missile.name << " causing " << missile.damage << " damage." << endl;
            target.takeDamage(missile.damage);
            missile.usageCount--;
            if (missile.usageCount == 0) {
                missiles.erase(remove(missiles.begin(), missiles.end(), missile), missiles.end());
            }
        } else {
            cout << "Player has no missiles to attack!" << endl;
        }
    }

    int getHealth() override {
        return health;
    }

    void takeDamage(int damage) override {
        health -= damage;
        if (health < 0)
            health = 0;
        cout << "Player spaceship takes " << damage << " damage, health now " << health << endl;
    }
};

class SystemSpaceship : public Spaceship {
public:
    int attackPower;
    int health;

    SystemSpaceship(string id, string name, int attackPower, int health)
        : Spaceship(id, name), attackPower(attackPower), health(health) {}

    void attack(Spaceship &target) override {
        cout << "System spaceship attacks causing " << attackPower << " damage." << endl;
        target.takeDamage(attackPower);
    }

    int getHealth() override {
        return health;
    }

    void takeDamage(int damage) override {
        health -= damage;
        if (health < 0)
            health = 0;
        cout << "System spaceship takes " << damage << " damage, health now " << health << endl;
    }
};

class Game {
public:
    PlayerSpaceship player;
    vector<SystemSpaceship> systemSpaceships;
    vector<Meteor *> meteors;
    vector<Missile> mapMissiles;

    Game(PlayerSpaceship player) : player(player) {}

    void addSystemSpaceship(SystemSpaceship systemSpaceship) {
        systemSpaceships.push_back(systemSpaceship);
    }

    void addMeteor(Meteor *meteor) {
        meteors.push_back(meteor);
    }

    void addMapMissile(Missile missile) {
        mapMissiles.push_back(missile);
    }

    void simulateMeteorAttacks() {
        for (Meteor *meteor : meteors) {
            meteor->collide();
            player.takeDamage(meteor->getDamage());
        }
    }

    void simulateBattle() {
        if (systemSpaceships.empty()) {
            cout << "No system spaceships to battle with." << endl;
            return;
        }

        SystemSpaceship *strongestSystemSpaceship = &systemSpaceships[0];
        for (auto &ship : systemSpaceships) {
            if (ship.getHealth() > strongestSystemSpaceship->getHealth() ||
                (ship.getHealth() == strongestSystemSpaceship->getHealth() && ship.attackPower > strongestSystemSpaceship->attackPower)) {
                strongestSystemSpaceship = &ship;
            }
        }

        cout << "Player vs. System spaceship battle begins!" << endl;
        player.attack(*strongestSystemSpaceship);
        strongestSystemSpaceship->attack(player);

        if (player.getHealth() > strongestSystemSpaceship->getHealth()) {
            cout << "Player wins the battle!" << endl;
        } else {
            cout << "System spaceship wins the battle!" << endl;
        }
    }
};

int main() {
    PlayerSpaceship player("P1", "PlayerOne", 100);
    player.missiles.push_back(Missile("M1", "Strong Missile", 50, 1));

    SystemSpaceship system1("S1", "SystemOne", 3, 130);
    SystemSpaceship system2("S2", "SystemTwo", 4, 100);

    Game game(player);
    game.addSystemSpaceship(system1);
    game.addSystemSpaceship(system2);

    Meteor *alpha = new AlphaMeteor("A1");
    Meteor *beta = new BetaMeteor("B1");

    game.addMeteor(alpha);
    game.addMeteor(beta);

    cout << "Simulating meteor attacks:" << endl;
    game.simulateMeteorAttacks();

    cout << "Simulating battle:" << endl;
    game.simulateBattle();

    return 0;
}
