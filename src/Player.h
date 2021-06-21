#ifndef _MAZEMADEMAGE_Player_H_
#define _MAZEMADEMAGE_Player_H_
#include "Object.h"
#include "Camera.h"
class CPlayer : public CObject {
public:
	CPlayer();
	~CPlayer();

	static const int FRONT = 1;
	static const int LEFT = 2;
	static const int BACK = 4;
	static const int RIGHT = 8;

	void move(ofVec3f movement);
	void rotate(float angle, ofVec3f axis);
	void setPosition(ofVec3f position);
	void setRotation(ofVec3f rotation);

	void keyboardInput(int key);
	void mouseInput(float dx, float dy);

	CCamera& getCamera();

protected:

private:
	CCamera m_camera;

	int m_sensitivity;
	int m_speed;
};
#endif