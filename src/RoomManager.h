#ifndef _MAZEMADEMAGE_ROOMMANAGER_H_
#define _MAZEMADEMAGE_ROOMMANAGER_H_
#include "ofMain.h"
#include "Player.h"
#include "Monster.h"
#include "Projectile.h"
#include "Room.h"
class CRoomManager {
	enum class direction {RIGHT, UP, LEFT, DOWN, NONE = -1};
public:
	CRoomManager();
	~CRoomManager();

	void drawRoom();
	void drawObjects();

	void processObjects();

	CPlayer& getPlayer();

	void keyboardInput(int input);
	void mouseInput(float dx, float dy);
	void mouseClicked();
	ofVec2f getRoomCoord();

protected:
	void drawWall(ofVec3f position, float angle);
	void drawTop();
	void drawFloor();
	void drawDoor(ofVec3f position, float angle);
	void drawDoorLock(ofVec3f position, float angle);
	
	void changeRoom(int x, int y);

	direction checkPlayerNearRoom();

private:
	int roomWidth;
	int roomHeight;
	int playerTall;

	int currentX;
	int currentY;
	Room currentRoom;

	CPlayer m_player;

	vector<CMonster> monsters;
	vector<CProjectile> projectiles;
};

#endif