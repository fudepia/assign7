#include "enemy.h"

// add your code to implement the Enemy class here
Enemy::Enemy(Position initialPosition, int health, int attack, std::string name):GameObject(initialPosition, health, attack, name) {}
Enemy::Enemy(Position initialPosition, int health, int attack, std::string name, bool lastBoss):GameObject(initialPosition, health, attack, name), lastBoss(lastBoss) {}
Enemy::~Enemy()=default;
