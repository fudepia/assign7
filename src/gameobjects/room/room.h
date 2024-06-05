#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>

#include "../../controller/enviroment.h"
#include "../../functions/position/position.h"
#include "../enemy/enemy.h"
#include "roomstate.h"

using namespace RoomState;

class Room {
    public:
        const int roomID;
        const std::string roomName;
        const std::string roomDescription;

        const Position playerInitialPosition;

    private:
        std::vector<Enemy *> enemies;

        RoomObject defaultRoomObjectMap[GAME_WINDOW_SIZE_Y][GAME_WINDOW_SIZE_X];

    public:
        Room(RoomData roomData);
        ~Room();

        bool walkable(Position position);

        void destroyEnemy(Enemy *enemy);

        const std::vector<Enemy *> & getEnemies();

        void render(Position position);
};

#endif
