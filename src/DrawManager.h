#ifndef _MAZEMADEMAGE_DRAWMANAGER_H_
#define _MAZEMADEMAGE_DRAWMANAGER_H_
#include "ofMain.h"
#include "Camera.h"

class CDrawManager {
private:
	static CDrawManager* instance;
	CDrawManager();
	~CDrawManager();

public:
	static CDrawManager* getInstance();
	static CDrawManager* getInstance(CCamera camera);

	void drawBox(ofVec3f vertex[4], ofColor color);
	void drawLine(ofVec3f vertex1, ofVec3f vertex2, ofColor color);
	void fillBox(ofVec3f vertex[4], ofColor color);
	void fillPoligon(ofVec3f vertex[3], ofColor color);

	void convertPoint(ofVec3f* vertex, int vertex_num, ofVec3f position, float angle);

	void setCamera(CCamera camera);
private:
	CCamera m_camera;
};
#endif