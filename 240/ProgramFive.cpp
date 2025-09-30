/***************************************************************
CSCI 240         Program 5     Fall 2023

Programmer: Collen Larsen

Section:0001

Date Due: 10/13/23

Purpose: Make a simplified D&D game
***************************************************************/
#include <iostream>
#include <iomanip>

#include <cstdlib>   //for random numbers

const int GOBLIN = 0;
const int OGRE = 1;
const int DRAGON = 2;

const int MIN_PLAYER_HP = 50;
const int MAX_PLAYER_HP = 150;
const int MIN_PLAYER_AC = 1;
const int MAX_PLAYER_AC = 4;

int main()
 {
//Declare values

double player_health;
double armor_class;

srand(14); //seeds the RNG

//Generate the PC's maximum HP value (50-150)
int player_health = rand() % (MAX_PLAYER_HP - MIN_PLAYER_HP + 1) + MIN_PLAYER_HP;


//Generate the PC's AC (1-4)
int armor_class = rand() % (MAX_PLAYER_AC - MIN_PLAYER_AC + 1) + MIN_PLAYER_AC;

//Gnerate a random number (0-2) to select monster
int monsterType = rand() % 3;  // Generate a random number (0, 1, or 2)

int monster_max_hp, monster_ac;
switch (monsterType) {
    case GOBLIN:
        monster_max_hp = rand() % (45 - 30 + 1) + 30;
        monster_ac = rand() % 2 + 1;  // Goblin's AC is 1 or 2
        std::cout << "You encounter a meager goblin. This should be easy enough!\n";
        break;
    case OGRE:
        monster_max_hp = rand() % (100 - 75 + 1) + 75;
        monster_ac = rand() % 3 + 2;  // Ogre's AC is 2, 3, or 4
        std::cout << "You encounter a towering ogre. Hope you brought health potions!\n";
        break;
    case DRAGON:
        monster_max_hp = rand() % (500 - 345 + 1) + 345;
        monster_ac = rand() % 2 + 5;  // Dragon's AC is 5 or 6
        std::cout << "You encounter a dragon the size of a modest castle. Ruination has come!\n";
        break;
}

return 0;
}
