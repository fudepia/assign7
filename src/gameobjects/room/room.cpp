#include "room.h"
#include "roomdata.h"
#include "../../functions/AnsiPrint/AnsiPrint.h"

// read data to the Room class
Room::Room(RoomData data):roomID(data.id), roomName(data.name), roomDescription(data.description), playerInitialPosition(data.playerInitialPosition), enemies(std::move(data.enemies)) {
	//memcpy(&defaultRoomObjectMap[0][0],
	//		&data.defaultRoomObjectMap[0][0],
	//		GAME_WINDOW_SIZE_Y*GAME_WINDOW_SIZE_X*sizeof(data.defaultRoomObjectMap[0][0]));
    for(auto enemy : data.enemies) {
        this->enemies.push_back(enemy);
    }

    for (int y = 0; y < GAME_WINDOW_SIZE_Y; y++) {
        for (int x = 0; x < GAME_WINDOW_SIZE_X; x++) {
            this->defaultRoomObjectMap[y][x] = RoomObject(data.defaultRoomObjectMap[y][x]);
        }
    }
}
Room::~Room() {
    for(auto &i:enemies) delete i;
}
// add your code to implement the Room class here


bool Room::walkable(Position p) {
	switch(defaultRoomObjectMap[p.getY()][p.getX()]) {
		case OBJECT_NONE:
		case OBJECT_DOOR:
		case OBJECT_GRASS:
			return true;
		case OBJECT_WALL:
		case OBJECT_ROCK:
		case OBJECT_WATER:
			return false;
	}
	return true;
}

const std::vector<Enemy*>& Room::getEnemies() { return enemies; }















// render
void Room::render(Position position) {
    switch(this->defaultRoomObjectMap[position.getY()][position.getX()]) {
        case OBJECT_NONE:
            AnsiPrint("  ", black, black);
            break;
        case OBJECT_DOOR:
            AnsiPrint("DR", yellow, black);
            break;
        case OBJECT_WALL:
            AnsiPrint("██", white, black);
            break;
        case OBJECT_GRASS:
            AnsiPrint("WW", green, black);
            break;
        case OBJECT_ROCK:
            AnsiPrint("▲▲", yellow, black);
            break;
        case OBJECT_WATER:
            if(rand() % 2 == 0) {
                AnsiPrint("~~", cyan, blue);
            } else {
                AnsiPrint("……", cyan, blue);
            }
            break;
    }
}
