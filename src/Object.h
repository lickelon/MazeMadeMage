#ifndef _MAZEMADEMAGE_Object_H_
#define _MAZEMADEMAGE_Object_H_
#include "ofMain.h"

class CObject {
public:
	static const ofVec3f AXIS_X;
	static const ofVec3f AXIS_Y;
	static const ofVec3f AXIS_Z;

	CObject();
	CObject(ofVec3f& position);
	CObject(ofVec3f& position, ofVec3f& rotation);
	virtual ~CObject();

	void move(ofVec3f movement);
	void rotate(float angle, ofVec3f axis);

	void setPosition(ofVec3f position);
	void setRotation(ofVec3f rotation);
	void setPosition(float x, float y, float z);
	void setRotation(float x, float y, float z);

	ofVec3f& getPosition();
	ofVec3f& getRotation();

protected:

private:
	ofVec3f m_position;
	ofVec3f m_rotation;
};
#endif