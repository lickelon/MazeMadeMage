#include "Camera.h"

CCamera::CCamera()
{
	m_FOV = 45;
	setPosition(0, 0, 0);
	setRotation(0, 0, 1);
	m_windowWidth = 0;
	m_windowHeight = 0;
}

CCamera::~CCamera()
{

}
ofVec3f& CCamera::getRelativeX()
{
	ofVec3f relativeX(getRotation().z, 0, -getRotation().x);
	return relativeX;
}
ofVec3f& CCamera::getRelativeCoordinate(ofVec3f& position)
{
	//1. 카메라의 position에 맞춰 상대위치를 구한다
	ofVec3f relative_position = position - getPosition();
	//2. 카메라의 rotate에 맞춰 회전된 상대좌표를 구한다.
	ofVec3f relative_coordinate = relative_position;

	ofVec3f horizontal = { getRotation().x, 0, getRotation().z };
	float vertical_angle = getRotation().angle(horizontal);
	if (getRotation().y < 0)
	{
		vertical_angle *= -1;
	}
	ofVec3f relativeX = getRelativeX();
	relative_coordinate.rotate(-vertical_angle, relativeX);

	float horizontal_angle = horizontal.angle(CObject::AXIS_Z);
	if (horizontal.x < 0)
	{
		horizontal_angle *= -1;
	}
	relative_coordinate.rotate(-horizontal_angle, CObject::AXIS_Y);

	return relative_coordinate;
}
	
ofVec2f& CCamera::getProjectedPosition(ofVec3f& position)
{
	ofVec2f projected;
	float d = 1 / tanf(m_FOV * PI / 180);
	if (position.z > 0)
	{
		projected.x = position.x / (position.z / d);
		projected.y = position.y / (position.z / d);

		projected *= m_windowWidth / 2;

		projected.x += m_windowWidth / 2;
		projected.y += m_windowHeight / 2;
	}
	else if (position.z == 0)
	{
		projected.x = position.x * d;
		projected.y = position.y * d;

		projected *= m_windowWidth / 2;

		projected.x += m_windowWidth / 2;
		projected.y += m_windowHeight / 2;
	}
	else
	{
		projected.x = position.x / (position.z / d);
		projected.y = position.y / (position.z / d);

		projected *= -m_windowWidth / 2;

		projected.x += m_windowWidth / 2;
		projected.y += m_windowHeight / 2;
	}
	return projected;
}

void CCamera::setWindowSize(float windowWidth, float windowHeight)
{
	m_windowWidth = windowWidth;
	m_windowHeight = windowHeight;
}