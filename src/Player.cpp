#include "Player.h"

CPlayer::CPlayer()
{
	m_sensitivity = 30;
	m_speed = 20;
}
CPlayer::~CPlayer()
{

}

void CPlayer::move(ofVec3f movement)
{
	CObject::move(movement);
	m_camera.move(movement);
}
void CPlayer::rotate(float angle, ofVec3f axis)
{
	CObject::rotate(angle, axis);
	m_camera.rotate(angle, axis);
}
void CPlayer::setPosition(ofVec3f position)
{
	CObject::setPosition(position);
	m_camera.setPosition(position);
}
void CPlayer::setRotation(ofVec3f rotation)
{
	CObject::setRotation(rotation);
	m_camera.setRotation(rotation);
}

void CPlayer::keyboardInput(int input)
{
	ofVec3f direction;
	ofVec3f temp;
	if (input & FRONT)
	{
		temp = m_camera.getRotation();
		temp.y = 0;
		temp.normalize();
		direction += temp;
	}
	if (input & LEFT)
	{
		temp = m_camera.getRelativeX();
		temp.normalize();
		direction += -temp;
	}
	if (input & BACK)
	{
		temp = m_camera.getRotation();
		temp.y = 0;
		temp.normalize();
		direction += -temp;
	}
	if (input & RIGHT)
	{
		temp = m_camera.getRelativeX();
		temp.normalize();
		direction += temp;
	}
	
	direction.normalize();
	move(direction * m_speed);
}
void CPlayer::mouseInput(float dx, float dy)
{
	ofVec3f relativeX(m_camera.getRotation().z, 0, -m_camera.getRotation().x);
	rotate(dy * m_sensitivity / 1000, relativeX);
	rotate(dx * m_sensitivity / 1000, CObject::AXIS_Y);
}

CCamera& CPlayer::getCamera()
{
	return m_camera;
}
int CPlayer::getSensitivity()
{
	return m_sensitivity;
}