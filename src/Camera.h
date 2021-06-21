#ifndef _MAZEMADEMAGE_CAMERA_H_
#define _MAZEMADEMAGE_CAMERA_H_

#include "ofMain.h"
#include "Object.h"

class CCamera : public CObject {
public:
	CCamera();
	virtual ~CCamera();

	//ī�޶� �ٶ󺸴� ������ z������ �� ��, ������� x�� ���͸� ��ȯ
	ofVec3f getRelativeX();
	//ī�޶� �ٶ󺸴� ������ z������ �Ͽ� ��ȯ�� ��ǥ�� ��ȯ
	ofVec3f getRelativeCoordinate(ofVec3f position);
	//��ȯ�� �����ǥ�� �޾� ������ ��ġ�� ��ȯ
	ofVec2f getProjectedPosition(ofVec3f position);

	void setWindowSize(float windowWidth, float windowHeight);

protected:
	
private:
	float m_FOV;
	float m_windowWidth;
	float m_windowHeight;
};
#endif