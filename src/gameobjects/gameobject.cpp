#include "gameobject.h"



// Add your code to implement the GameObject class here.

GameObject::GameObject(Position iP, int mH, int atk, std::string n): position(iP), maxHealth(mH), name(n), attack(atk) {}
GameObject::~GameObject() = default;

Position GameObject::getPosition() { return position; }
void GameObject::setPosition(Position p) { position=p; }

int GameObject::getMaxHealth() { return maxHealth; }
int GameObject::getHealth() { return health; }

std::string GameObject::getName() { return name; }
