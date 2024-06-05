#include "position.h"
#include "../../controller/enviroment.h"

// Add your code to implement the Position class here.
Position::Position(int iPx, int iPy):positionX(iPx), positionY(iPy) {}
Position::Position():Position(0,0) {}
Position::~Position()=default;
bool Position::operator==(const Position &other) const { return positionX==other.getX() && positionY==other.getY(); }
int Position::getX() const { return positionX; }
int Position::getY() const { return positionY; }
int Position::incrX() { if(positionX<34) ++positionX; return positionX; }//else return positionX=0; }
int Position::incrY() { if(positionY<19) ++positionY; return positionY; }//else return positionY=0; }
int Position::decrX() { if(positionX>0) --positionX; return positionX; }//else return positionX=34; }
int Position::decrY() { if(positionY>0) --positionY; return positionY; }//else return positionY=19; }
