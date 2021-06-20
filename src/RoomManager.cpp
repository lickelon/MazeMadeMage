#include "RoomManager.h"
#include "DrawManager.h"
#include "MazeManager.h"

CRoomManager::CRoomManager()
{
	roomHeight = 1200;
	roomWidth = 3000;
	playerTall = 300;
	m_mobCount = 0;
	m_projectileCount = 0;

	currentX = 0;
	currentY = 0;

	CMazeManager::getInstance()->getRoom(currentX, currentY).visit = 1;
	currentRoom = CMazeManager::getInstance()->getRoom(currentX, currentY);
}

CRoomManager::~CRoomManager()
{
	//필요한가?
}

void CRoomManager::drawRoom()
{
	ofVec3f position;
	position.set(0, 0, roomWidth / 2);
	drawWall(position, 0);
	position.set(-roomWidth / 2, 0, 0);
	drawWall(position, 90);
	position.set(0, 0, -roomWidth / 2);
	drawWall(position, 180);
	position.set(roomWidth / 2, 0, 0);
	drawWall(position, 270);

	drawTop();
	drawFloor();

	CMazeManager* mazeManager = CMazeManager::getInstance();
	int mob_count = mazeManager->getRoom(currentX, currentY).mob_count;
	if (currentRoom.right)
	{
		position.set(0, 0, roomWidth / 2);
		drawDoor(position, 0);
		if (mob_count)
		{
			drawDoorLock(position, 0);
		}
	}
	if (currentRoom.up)
	{
		position.set(-roomWidth / 2, 0, 0);
		drawDoor(position, 90);
		if (mob_count)
		{
			drawDoorLock(position, 90);
		}
	}
	if (currentRoom.left)
	{
		position.set(0, 0, -roomWidth / 2);
		drawDoor(position, 180);
		if (mob_count)
		{
			drawDoorLock(position, 180);
		}
	}
	if (currentRoom.down)
	{
		position.set(roomWidth / 2, 0, 0);
		drawDoor(position, 270);
		if (mob_count)
		{
			drawDoorLock(position, 270);
		}
	}
}

void CRoomManager::drawObjects()
{
	for (auto monster : monsters)
	{
		monster.drawSelf();
	}

	for (auto projectile : projectiles)
	{
		projectile.drawSelf();
	}
}
void CRoomManager::processObjects()
{
	for (auto& monster : monsters)
	{
		monster.update(m_player.getPosition());
	}
	for (auto& projectile : projectiles)
	{
		projectile.update();
	}

	for (int i = 0; i < projectiles.size(); i++)
	{
		int nearest_index = 0;
		float nearest_length = 3000;
		for (int j = 0; j < monsters.size(); j++)
		{
			ofVec3f distance = projectiles[i].getPosition()- monsters[j].getPosition();
			if (nearest_length > distance.length())
			{
				nearest_length = distance.length();
				nearest_index = j;
			}
		}
		if (nearest_length < 220)
		{
			monsters.erase(std::next(monsters.begin(), nearest_index));
			CMazeManager::getInstance()->getRoom(currentX, currentY).mob_count -= 1;
			projectiles.erase(std::next(projectiles.begin(), i));
			i--;
		}
	}

	for (int i = 0; i < projectiles.size(); i++)
	{
		ofVec3f position = projectiles[i].getPosition();
		if (position.x < -roomWidth / 2 || position.x > roomWidth / 2 ||
			position.z < -roomWidth / 2 || position.z > roomWidth / 2 ||
			position.y < -roomHeight + playerTall || position.y > playerTall)
		{
			projectiles.erase(next(projectiles.begin(), i));
			i--;
		}
	}
}

CPlayer& CRoomManager::getPlayer()
{
	return m_player;
}

void CRoomManager::keyboardInput(int input)
{
	m_player.keyboardInput(input);
	ofVec3f playerPosition = m_player.getPosition();
	if (playerPosition.x < -1450) playerPosition.x = -1450;
	if (playerPosition.x > 1450) playerPosition.x = 1450;
	if (playerPosition.z < -1450) playerPosition.z = -1450;
	if (playerPosition.z > 1450) playerPosition.z = 1450;

	m_player.setPosition(playerPosition);

	ofVec3f playerRotation;
	switch (checkPlayerNearRoom())
	{
	case direction::RIGHT:
		changeRoom(currentX + 1, currentY);
		playerPosition.set(0, 0, -1400);
		m_player.setPosition(playerPosition);
		//playerRotation.set(0, 0, 1);
		//m_player.setRotation(playerRotation);
		break;
	case direction::UP:
		changeRoom(currentX, currentY - 1);
		playerPosition.set(1400, 0, 0);
		m_player.setPosition(playerPosition);
		//playerRotation.set(-1, 0, 0);
		//m_player.setRotation(playerRotation);
		break;
	case direction::LEFT:
		changeRoom(currentX - 1, currentY);
		playerPosition.set(0, 0, 1400);
		m_player.setPosition(playerPosition);
		//playerRotation.set(0, 0, -1);
		//m_player.setRotation(playerRotation);
		break;
	case direction::DOWN:
		changeRoom(currentX, currentY + 1);
		playerPosition.set(-1400, 0, 0);
		m_player.setPosition(playerPosition);
		//playerRotation.set(1, 0, 0);
		//m_player.setRotation(playerRotation);
		break;
	case direction::NONE:
		break;
	}
}
void CRoomManager::mouseInput(float dx, float dy)
{
	m_player.mouseInput(dx, dy);
}
void CRoomManager::mouseClicked()
{
	CProjectile projectile(m_player.getPosition(), m_player.getRotation());
	projectiles.push_back(projectile);
}
ofVec2f CRoomManager::getRoomCoord()
{
	ofVec2f coord(currentX, currentY);
	return coord;
}

void CRoomManager::drawWall(ofVec3f position, float angle)
{
	CDrawManager* drawManager = CDrawManager::getInstance();

	ofVec3f vertex[4];
	ofColor color;

	int brickWidth = 100;
	int brickHeight = 40;

	vertex[0].set(-roomWidth / 2, -roomHeight + playerTall, 0);
	vertex[1].set(roomWidth / 2, -roomHeight + playerTall, 0);
	vertex[2].set(roomWidth / 2, playerTall, 0);
	vertex[3].set(-roomWidth / 2, playerTall, 0);

	drawManager->convertPoint(vertex, 4, position, angle);
	color.set(80);
	drawManager->fillBox(vertex, color);

	//color.set(137, 22, 22);
	//color.set(115, 51, 17);
	color.set(68, 25, 7);
	for (int i = 0; i < roomHeight / brickHeight; i++)
	{
		if (i % 2)
		{
			vertex[0].set(-roomWidth/2,
				          -roomHeight+playerTall + brickHeight*i,
				          0);
			vertex[1].set(-roomWidth/2 + (brickWidth/2-5),
				          -roomHeight+playerTall + brickHeight*i,
				          0);
			vertex[2].set(-roomWidth/2 + (brickWidth/2-5),
				          -roomHeight+playerTall + (brickHeight-5) + brickHeight*i,
				          0);
			vertex[3].set(-roomWidth/2,
				          -roomHeight+playerTall + (brickHeight-5) + brickHeight*i,
				          0);

			drawManager->convertPoint(vertex, 4, position, angle);
			drawManager->fillBox(vertex, color);
		}
		for (int j = 0; j < roomWidth / brickWidth - (i % 2); j++)
		{
			vertex[0].set(-roomWidth/2 + brickWidth*j + (i%2)*brickWidth/2,
				          -roomHeight+playerTall + brickHeight*i,
				          0);
			vertex[1].set(-roomWidth/2 + (brickWidth-5) + brickWidth*j + (i%2)*brickWidth/2,
				          -roomHeight+playerTall + brickHeight*i,
				          0);
			vertex[2].set(-roomWidth/2 + (brickWidth-5) + brickWidth*j + (i%2)*brickWidth/2,
				          -roomHeight+playerTall + (brickHeight-5) + brickHeight*i,
				          0);
			vertex[3].set(-roomWidth/2 + brickWidth*j + (i%2)*brickWidth/2,
				          -roomHeight+playerTall + (brickHeight-5) + brickHeight*i,
				          0);

			drawManager->convertPoint(vertex, 4, position, angle);
			drawManager->fillBox(vertex, color);
		}
		if (i % 2)
		{
			vertex[0].set(roomWidth/2 - (brickWidth/2),
				          -roomHeight+playerTall + brickHeight*i,
				          0);
			vertex[1].set(roomWidth/2 - 5,
				          -roomHeight + playerTall + brickHeight * i,
				          0);
			vertex[2].set(roomWidth/2 - 5,
				          -roomHeight + playerTall + (brickHeight - 5) + brickHeight * i,
				          0);
			vertex[3].set(roomWidth/2 - (brickWidth/2),
				          -roomHeight + playerTall + (brickHeight - 5) + brickHeight * i,
				          0);

			drawManager->convertPoint(vertex, 4, position, angle);
			drawManager->fillBox(vertex, color);
		}
	}

	vertex[0].set(-roomWidth / 2, -roomHeight + playerTall, 0);
	vertex[1].set(roomWidth / 2, -roomHeight + playerTall, 0);
	vertex[2].set(roomWidth / 2, playerTall, 0);
	vertex[3].set(-roomWidth / 2, playerTall, 0);
	color.set(0);
	drawManager->convertPoint(vertex, 4, position, angle);
	drawManager->drawBox(vertex, color);
}
void CRoomManager::drawTop()
{
	CDrawManager* drawManager = CDrawManager::getInstance();
	ofVec3f vertex[4];
	ofColor color;
	int interval = 0;
	color.set(5);
	vertex[0].set(roomWidth / 2 - interval, -roomHeight + playerTall, roomWidth / 2 - interval);
	vertex[1].set(roomWidth / 2 - interval, -roomHeight + playerTall, -roomWidth / 2 + interval);
	vertex[2].set(-roomWidth / 2 + interval, -roomHeight + playerTall, -roomWidth / 2 + interval);
	vertex[3].set(-roomWidth / 2 + interval, -roomHeight + playerTall, roomWidth / 2 - interval);
	drawManager->fillBox(vertex, color);

	color.set(40);
	interval = 25;
	vertex[0].set(roomWidth / 2 - interval, -roomHeight + playerTall, roomWidth / 2 - interval);
	vertex[1].set(roomWidth / 2 - interval, -roomHeight + playerTall, -roomWidth / 2 + interval);
	vertex[2].set(-roomWidth / 2 + interval, -roomHeight + playerTall, -roomWidth / 2 + interval);
	vertex[3].set(-roomWidth / 2 + interval, -roomHeight + playerTall, roomWidth / 2 - interval);
	drawManager->fillBox(vertex, color);


	color.set(100);
	interval = 175;
	vertex[0].set(roomWidth / 2 - interval, -roomHeight + playerTall, roomWidth / 2 - interval);
	vertex[1].set(roomWidth / 2 - interval, -roomHeight + playerTall, -roomWidth / 2 + interval);
	vertex[2].set(-roomWidth / 2 + interval, -roomHeight + playerTall, -roomWidth / 2 + interval);
	vertex[3].set(-roomWidth / 2 + interval, -roomHeight + playerTall, roomWidth / 2 - interval);
	drawManager->fillBox(vertex, color);

	color.set(5);
	interval = 200;
	vertex[0].set(roomWidth / 2 - interval, -roomHeight + playerTall, roomWidth / 2 - interval);
	vertex[1].set(roomWidth / 2 - interval, -roomHeight + playerTall, -roomWidth / 2 + interval);
	vertex[2].set(-roomWidth / 2 + interval, -roomHeight + playerTall, -roomWidth / 2 + interval);
	vertex[3].set(-roomWidth / 2 + interval, -roomHeight + playerTall, roomWidth / 2 - interval);
	drawManager->fillBox(vertex, color);

	color.set(25);
	interval = 225;
	vertex[0].set(roomWidth / 2 - interval, -roomHeight + playerTall, roomWidth / 2 - interval);
	vertex[1].set(roomWidth / 2 - interval, -roomHeight + playerTall, -roomWidth / 2 + interval);
	vertex[2].set(-roomWidth / 2 + interval, -roomHeight + playerTall, -roomWidth / 2 + interval);
	vertex[3].set(-roomWidth / 2 + interval, -roomHeight + playerTall, roomWidth / 2 - interval);
	drawManager->fillBox(vertex, color);

	color.set(120);
	interval = 200;
	vertex[0].set(roomWidth / 2, -roomHeight + playerTall, roomWidth / 2);
	vertex[1].set(roomWidth / 2 - interval, -roomHeight + playerTall, roomWidth / 2 - interval);
	drawManager->drawLine(vertex[0], vertex[1], color);
	vertex[0].set(roomWidth / 2, -roomHeight + playerTall, -roomWidth / 2);
	vertex[1].set(roomWidth / 2 - interval, -roomHeight + playerTall, -roomWidth / 2 + interval);
	drawManager->drawLine(vertex[0], vertex[1], color);
	vertex[0].set(-roomWidth / 2, -roomHeight + playerTall, -roomWidth / 2);
	vertex[1].set(-roomWidth / 2 + interval, -roomHeight + playerTall, -roomWidth / 2 + interval);
	drawManager->drawLine(vertex[0], vertex[1], color);
	vertex[0].set(-roomWidth / 2, -roomHeight + playerTall, roomWidth / 2);
	vertex[1].set(-roomWidth / 2 + interval, -roomHeight + playerTall, roomWidth / 2 - interval);
	drawManager->drawLine(vertex[0], vertex[1], color);
}
void CRoomManager::drawFloor()
{
	CDrawManager* drawManager = CDrawManager::getInstance();
	ofVec3f vertex[4];
	ofColor color;

	int tileSize = 50;

	color.set(60);
	vertex[0].set(roomWidth / 2, playerTall, roomWidth / 2);
	vertex[1].set(roomWidth / 2, playerTall, -roomWidth / 2);
	vertex[2].set(-roomWidth / 2, playerTall, -roomWidth / 2);
	vertex[3].set(-roomWidth / 2, playerTall, roomWidth / 2);
	drawManager->fillBox(vertex, color);

	color.set(30, 0, 0);
	for (int i = 0; i < roomWidth / tileSize; i++)
	{
		for (int j = 0; j < roomWidth / tileSize; j++)
		{
			vertex[0].set(-roomWidth / 2 + tileSize * i + 2.5,
				          playerTall,
				          -roomWidth / 2 + tileSize * j + 2.5);
			vertex[1].set(-roomWidth / 2 + tileSize * i + 2.5,
				          playerTall,
				          -roomWidth / 2 + tileSize * j + tileSize - 2.5);
			vertex[2].set(-roomWidth / 2 + tileSize * i + tileSize - 2.5,
				          playerTall,
				          -roomWidth / 2 + tileSize * j + tileSize - 2.5);
			vertex[3].set(-roomWidth / 2 + tileSize * i + tileSize - 2.5,
				          playerTall,
				          -roomWidth / 2 + tileSize * j + 2.5);
			drawManager->fillBox(vertex, color);
		}
	}
}
void CRoomManager::drawDoor(ofVec3f position, float angle)
{
	CDrawManager* drawManager = CDrawManager::getInstance();
	ofVec3f vertex[4];
	ofColor color;

	vertex[0].set(-200, -200, 0);
	vertex[1].set(200, -200, 0);
	vertex[2].set(200, playerTall, 0);
	vertex[3].set(-200, playerTall, 0);

	drawManager->convertPoint(vertex, 4, position, angle);
	color.set(0);
	drawManager->fillBox(vertex, color);
}
void CRoomManager::drawDoorLock(ofVec3f position, float angle)
{
	CDrawManager* drawManager = CDrawManager::getInstance();
	ofVec3f vertex[4];
	ofColor color;

	for (int i = 0; i < 6; i++)
	{
		color.set(40);
		vertex[0].set(-200, -170 + i * 80, 0);
		vertex[1].set(200, -170 + i * 80, 0);
		vertex[2].set(200, -130 + i * 80, 0);
		vertex[3].set(-200, -130 + i * 80, 0);
		drawManager->convertPoint(vertex, 4, position, angle);
		drawManager->fillBox(vertex, color);

		color.set(110);
		vertex[0].set(-200, -165 + i * 80, 0);
		vertex[1].set(200, -165 + i * 80, 0);
		vertex[2].set(200, -135 + i * 80, 0);
		vertex[3].set(-200, -135 + i * 80, 0);
		drawManager->convertPoint(vertex, 4, position, angle);
		drawManager->fillBox(vertex, color);

		color.set(150);
		vertex[0].set(-200, -158 + i * 80, 0);
		vertex[1].set(200, -158 + i * 80, 0);
		vertex[2].set(200, -142 + i * 80, 0);
		vertex[3].set(-200, -142 + i * 80, 0);
		drawManager->convertPoint(vertex, 4, position, angle);
		drawManager->fillBox(vertex, color);
	}
	for (int i = 0; i < 5; i++)
	{
		color.set(40);
		vertex[0].set(-180 + i * 80, -200, 0);
		vertex[1].set(-140 + i * 80, -200, 0);
		vertex[2].set(-140 + i * 80, 300, 0);
		vertex[3].set(-180 + i * 80, 300, 0);
		drawManager->convertPoint(vertex, 4, position, angle);
		drawManager->fillBox(vertex, color);

		color.set(110);
		vertex[0].set(-175 + i * 80, -200, 0);
		vertex[1].set(-145 + i * 80, -200, 0);
		vertex[2].set(-145 + i * 80, 300, 0);
		vertex[3].set(-175 + i * 80, 300, 0);
		drawManager->convertPoint(vertex, 4, position, angle);
		drawManager->fillBox(vertex, color);

		color.set(160);
		vertex[0].set(-168 + i * 80, -200, 0);
		vertex[1].set(-152 + i * 80, -200, 0);
		vertex[2].set(-152 + i * 80, 300, 0);
		vertex[3].set(-168 + i * 80, 300, 0);
		drawManager->convertPoint(vertex, 4, position, angle);
		drawManager->fillBox(vertex, color);
	}
}

void CRoomManager::changeRoom(int x, int y)
{
	Room& room = CMazeManager::getInstance()->getRoom(x, y);
	room.visit = TRUE;
	currentRoom = room;
	currentX = x;
	currentY = y;

	for (int i = 0; i < room.mob_count; i++)
	{
		CMonster monster;
		monster.setPosition(rand() % 2800 - 1400, 0, rand() % 2800 - 1400);
		float angle = (rand() % 360);
		monster.rotate(angle, CObject::AXIS_Y);
		monsters.push_back(monster);
	}
}
CRoomManager::direction CRoomManager::checkPlayerNearRoom()
{
	direction ret = direction::NONE;
	ofVec3f position = m_player.getPosition();
	if (CMazeManager::getInstance()->getRoom(currentX, currentY).mob_count) return ret;
	if (position.z > 1400 || position.z < -1400 || position.x > 1400 || position.x < -1400)
	{
		int a = 0;
		a = 1;
	}

	if (position.z > 1400 && (position.x > -200 && position.x < 200) && currentRoom.right)
	{
		ret = direction::RIGHT;
	}
	if (position.x < -1400 && (position.z > -200 && position.z < 200) && currentRoom.up)
	{
		ret = direction::UP;
	}
	if (position.z < -1400 && (position.x > -200 && position.x < 200) && currentRoom.left)
	{
		ret = direction::LEFT;
	}
	if (position.x > 1400 && (position.z > -200 && position.z < 200) && currentRoom.down)
	{
		ret = direction::DOWN;
	}
	return ret;
}