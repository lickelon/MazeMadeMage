#include "Monster.h"
#include "DrawManager.h"

CMonster::CMonster()
{
	CObject();
	m_speed = 10;
}

CMonster::CMonster(ofVec3f& position)
{
	CObject();
	setPosition(position);
	m_speed = 10;
}

CMonster::CMonster(ofVec3f& position, ofVec3f& rotation)
{
	CObject();
	setPosition(position);
	setRotation(rotation);
	m_speed = 10;
}

CMonster::~CMonster()
{

}
void CMonster::drawSelf()
{
	ofVec3f position = getPosition();
	ofVec3f rotation(getRotation().x, 0, getRotation().z);
	float angle = rotation.angle(CObject::AXIS_Z);
	if (rotation.x < 0)
	{
		angle *= -1;
	}

	drawHead(position, angle);
}
void CMonster::update(ofVec3f player_position)
{
	changeDirection(player_position);
	ofVec3f rotation = getRotation();
	rotation.normalize();
	move(rotation * m_speed);
}
void CMonster::drawHead(ofVec3f position, float angle)
{
	CDrawManager* drawManager = CDrawManager::getInstance();
	ofVec3f vertex[4];
	ofColor color;
	color.set(59, 98, 47, 100);

	vertex[0].set(125, 50, 125);
	vertex[1].set(125, 300, 125);
	vertex[2].set(-125, 300, 125);
	vertex[3].set(-125, 50, 125);
	drawManager->convertPoint(vertex, 4, getPosition(), angle);
	drawManager->fillBox(vertex, color);

	vertex[0].set(125, 50, 125);
	vertex[1].set(125, 300, 125);
	vertex[2].set(125, 300, -125);
	vertex[3].set(125, 50, -125);
	drawManager->convertPoint(vertex, 4, getPosition(), angle);
	drawManager->fillBox(vertex, color);

	vertex[0].set(125, 50, -125);
	vertex[1].set(125, 300, -125);
	vertex[2].set(-125, 300, -125);
	vertex[3].set(-125, 50, -125);
	drawManager->convertPoint(vertex, 4, getPosition(), angle);
	drawManager->fillBox(vertex, color);

	vertex[0].set(-125, 50, 125);
	vertex[1].set(-125, 300, 125);
	vertex[2].set(-125, 300, -125);
	vertex[3].set(-125, 50, -125);
	drawManager->convertPoint(vertex, 4, getPosition(), angle);
	drawManager->fillBox(vertex, color);

	vertex[0].set(125, 50, 125);
	vertex[1].set(-125, 50, 125);
	vertex[2].set(-125, 50, -125);
	vertex[3].set(125, 50, -125);
	drawManager->convertPoint(vertex, 4, getPosition(), angle);
	drawManager->fillBox(vertex, color);

	vertex[0].set(125, 300, 125);
	vertex[1].set(-125, 300, 125);
	vertex[2].set(-125, 300, -125);
	vertex[3].set(125, 300, -125);
	drawManager->convertPoint(vertex, 4, getPosition(), angle);
	drawManager->fillBox(vertex, color);

	color.set(30, 12, 12, 100);

	vertex[0].set(-93.75, 143.75, 125);
	vertex[1].set(-93.75, 206.25, 125);
	vertex[2].set(-31.25, 206.25, 125);
	vertex[3].set(-31.25, 143.75, 125);
	drawManager->convertPoint(vertex, 4, getPosition(), angle);
	drawManager->fillBox(vertex, color);

	vertex[0].set(93.75, 143.75, 125);
	vertex[1].set(93.75, 206.25, 125);
	vertex[2].set(31.25, 206.25, 125);
	vertex[3].set(31.25, 143.75, 125);
	drawManager->convertPoint(vertex, 4, getPosition(), angle);
	drawManager->fillBox(vertex, color);
}

void CMonster::changeDirection(ofVec3f player_position)
{
	ofVec3f position = getPosition();
	ofVec3f rotation = player_position - getPosition();

	setRotation(rotation);
}