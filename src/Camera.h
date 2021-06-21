#ifndef _MAZEMADEMAGE_CAMERA_H_
#define _MAZEMADEMAGE_CAMERA_H_

#include "ofMain.h"
#include "Object.h"

class CCamera : public CObject {
public:
	CCamera();
	virtual ~CCamera();

	//카메라가 바라보는 방향을 z축으로 할 때, 상대적인 x축 벡터를 반환
	ofVec3f getRelativeX();
	//카메라가 바라보는 방향을 z축으로 하여 변환된 좌표를 반환
	ofVec3f getRelativeCoordinate(ofVec3f position);
	//변환된 상대죄표를 받아 투영된 위치를 반환
	ofVec2f getProjectedPosition(ofVec3f position);

	void setWindowSize(float windowWidth, float windowHeight);

protected:
	
private:
	float m_FOV;
	float m_windowWidth;
	float m_windowHeight;
};
#endif