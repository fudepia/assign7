#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "../functions/position/position.h"
#include <string>

class GameObject {
private:
    Position position;

    int maxHealth;

    std::string name;

    int attack;
public:
    int health;
    GameObject(Position initialPosition, int maxHealth, int attack, std::string name);

    virtual ~GameObject();

    Position getPosition();

    void setPosition(Position position);

    int getHealth();

    int getMaxHealth();

    int getAttack();

    void hurt(int damage);

    std::string getName();

    virtual void render() = 0;
};

#endif
