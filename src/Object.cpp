#include "Object.h"

CObject::CObject()
{
	m_position.set(0, 0, 0);
	m_rotation.set(0, 0, 1);
}
CObject::CObject(ofVec3f& position)
{
	m_position = position;
	m_rotation.set(0, 0, 1);
}
CObject::CObject(ofVec3f& position, ofVec3f& rotation)
{
	m_position = position;
	m_rotation = rotation;
}
CObject::~CObject()
{

}

void CObject::move(ofVec3f movement)
{
	m_position += movement;
}
void CObject::rotate(float angle, ofVec3f axis)
{
	m_rotation.rotate(angle, axis);
}

void CObject::setPosition(ofVec3f position)
{
	m_position = position;
}

void CObject::setRotation(ofVec3f rotation)
{
	m_rotation = rotation;
}
void CObject::setPosition(float x, float y, float z)
{
	m_position.set(x, y, z);
}
void CObject::setRotation(float x, float y, float z)
{
	m_rotation.set(x, y, z);
}
ofVec3f& CObject::getPosition()
{
	return m_position;
}
ofVec3f& CObject::getRotation()
{
	return m_rotation;
}

const ofVec3f CObject::AXIS_X(1, 0, 0);
const ofVec3f CObject::AXIS_Y(0, 1, 0);
const ofVec3f CObject::AXIS_Z(0, 0, 1);