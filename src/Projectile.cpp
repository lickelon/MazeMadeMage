#include "Projectile.h"
#include "DrawManager.h"

CProjectile::CProjectile()
{
	CObject();
	m_speed = 70;
}
CProjectile::CProjectile(ofVec3f position)
{
	CObject();
	setPosition(position);
	m_speed = 70;
}
CProjectile::CProjectile(ofVec3f position, ofVec3f rotation)
{
	CObject();
	setPosition(position);
	rotation.y = -rotation.y;
	setRotation(rotation);
	m_speed = 70;
}
CProjectile::~CProjectile()
{

}

void CProjectile::drawSelf()
{
	ofVec3f position = getPosition();
	ofVec3f rotation(getRotation().x, 0, getRotation().z);
	float angle = rotation.angle(CObject::AXIS_Z);
	if (rotation.x < 0)
	{
		angle *= -1;
	}
	
	CDrawManager* drawManager = CDrawManager::getInstance();
	ofVec3f vertex[4];
	ofColor color;
	color.set(150, 248, 248, 100);

	vertex[0].set(60, -60, 60);
	vertex[1].set(60, -50, 60);
	vertex[2].set(-55, -40, 55);
	vertex[3].set(-55, -50, 55);
	drawManager->convertPoint(vertex, 4, getPosition(), angle);
	drawManager->fillBox(vertex, color);

	vertex[0].set(-55, -50, 55);
	vertex[1].set(-55, -40, 55);
	vertex[2].set(-50, -30, -50);
	vertex[3].set(-50, -40, -50);
	drawManager->convertPoint(vertex, 4, getPosition(), angle);
	drawManager->fillBox(vertex, color);

	vertex[0].set(-50, -40, -50);
	vertex[1].set(-50, -30, -50);
	vertex[2].set(45, -20, -45);
	vertex[3].set(45, -30, -45);
	drawManager->convertPoint(vertex, 4, getPosition(), angle);
	drawManager->fillBox(vertex, color);

	vertex[0].set(45, -30, -45);
	vertex[1].set(45, -20, -45);
	vertex[2].set(40, -10, 40);
	vertex[3].set(40, -20, 40);
	drawManager->convertPoint(vertex, 4, getPosition(), angle);
	drawManager->fillBox(vertex, color);

	color.set(190, 248, 248, 100);

	vertex[0].set(40, -20, 40);
	vertex[1].set(40, -10, 40);
	vertex[2].set(-35, 0, 35);
	vertex[3].set(-35, -10, 35);
	drawManager->convertPoint(vertex, 4, getPosition(), angle);
	drawManager->fillBox(vertex, color);

	vertex[0].set(-35, -10, 35);
	vertex[1].set(-35, 0, 35);
	vertex[2].set(-30, 10, -30);
	vertex[3].set(-30, 0, -30);
	drawManager->convertPoint(vertex, 4, getPosition(), angle);
	drawManager->fillBox(vertex, color);

	vertex[0].set(-30, 0, -30);
	vertex[1].set(-30, 10, -30);
	vertex[2].set(25, 20, -25);
	vertex[3].set(25, 10, -25);
	drawManager->convertPoint(vertex, 4, getPosition(), angle);
	drawManager->fillBox(vertex, color);

	vertex[0].set(25, 10, -25);
	vertex[1].set(25, 20, -25);
	vertex[2].set(20, 30, 20);
	vertex[3].set(20, 20, 20);
	drawManager->convertPoint(vertex, 4, getPosition(), angle);
	drawManager->fillBox(vertex, color);

	color.set(230, 248, 248, 100);

	vertex[0].set(20, 20, 20);
	vertex[1].set(20, 30, 20);
	vertex[2].set(-15, 40, 15);
	vertex[3].set(-15, 30, 15);
	drawManager->convertPoint(vertex, 4, getPosition(), angle);
	drawManager->fillBox(vertex, color);

	vertex[0].set(-15, 30, 15);
	vertex[1].set(-15, 40, 15);
	vertex[2].set(-10, 50, -10);
	vertex[3].set(-10, 40, -10);
	drawManager->convertPoint(vertex, 4, getPosition(), angle);
	drawManager->fillBox(vertex, color);

	vertex[0].set(-10, 40, -10);
	vertex[1].set(-10, 50, -10);
	vertex[2].set(5, 60, -5);
	vertex[3].set(5, 50, -5);
	drawManager->convertPoint(vertex, 4, getPosition(), angle);
	drawManager->fillBox(vertex, color);

	vertex[0].set(5, 50, -5);
	vertex[1].set(5, 60, -5);
	vertex[2].set(0, 70, 0);
	vertex[3].set(0, 60, 0);
	drawManager->convertPoint(vertex, 4, getPosition(), angle);
	drawManager->fillBox(vertex, color);
}

void CProjectile::update()
{
	ofVec3f position = getPosition();
	ofVec3f rotation = getRotation();
	rotation.normalize();
	move(rotation * m_speed);
}