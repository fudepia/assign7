#include "dragon.h"
#include <stdlib.h>

#include "../../../functions/AnsiPrint/AnsiPrint.h"

Dragon::Dragon(Position initialPosition, bool isLastboss): Enemy(initialPosition,30, 3, "Dragon", isLastboss) {}
Dragon::~Dragon()=default;

// add your code to implement the Dragon class here

Position Dragon::nextPosition() {
    return getPosition();
}










// render function

void Dragon::render() {
    AnsiPrint("Dn", black, red);
}
