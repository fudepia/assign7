#ifndef POSITION_H
#define POSITION_H

class Position {
private:
    int positionX;
    int positionY;
public:
    Position(int initialPositionX, int initialPositionY);
    Position();
    ~Position();

    int getX() const;
    int getY() const;
    int incrX();
    int incrY();
    int decrX();
    int decrY();
    
    // add functions what you need

    bool operator==(const Position &other) const;








};

#endif
