#include "DrawManager.h"
CDrawManager* CDrawManager::instance = NULL;
CDrawManager::CDrawManager()
{

}
CDrawManager::~CDrawManager()
{

}
CDrawManager* CDrawManager::getInstance()
{
	if (instance == NULL) instance = new CDrawManager();
	return instance;
}

void CDrawManager::drawBox(ofVec3f vertex[4], ofColor color)
{
	for (int i = 0; i < 4; i++)
	{
		drawLine(vertex[i], vertex[(i + 1) % 4], color);
	}
}

void CDrawManager::drawLine(ofVec3f vertex1, ofVec3f vertex2, ofColor color)
{
	ofVec3f relative1 = m_camera.getRelativeCoordinate(vertex1);
	ofVec3f relative2 = m_camera.getRelativeCoordinate(vertex2);

	if (relative1.z < 0 && relative2.z < 0)
	{
		return;
	}

	if (relative1.z < 0)
	{
		ofVec3f temp = relative1;
		relative1 = relative2;
		relative2 = temp;
	}

	if (relative2.z < 0)
	{
		if (relative2.z - relative1.z == 0) return;
		float ratio = relative1.z / (relative2.z - relative1.z);
		ofVec3f new_point;
		new_point = relative1 - (relative2 - relative1) * ratio;
		relative2 = new_point;
	}
	ofVec2f projection1 = m_camera.getProjectedPosition(relative1);
	ofVec2f projection2 = m_camera.getProjectedPosition(relative2);
	ofSetColor(color);
	ofDrawLine(projection1, projection2);

}

void CDrawManager::fillBox(ofVec3f vertex[4], ofColor color)
{
	ofVec3f poligon[3];

	poligon[0] = vertex[0];
	poligon[1] = vertex[1];
	poligon[2] = vertex[2];
	fillPoligon(poligon, color);

	poligon[0] = vertex[2];
	poligon[1] = vertex[3];
	poligon[2] = vertex[0];
	fillPoligon(poligon, color);
}

void CDrawManager::fillPoligon(ofVec3f vertex[3], ofColor color)
{
	vertex[0] = m_camera.getRelativeCoordinate(vertex[0]);
	vertex[1] = m_camera.getRelativeCoordinate(vertex[1]);
	vertex[2] = m_camera.getRelativeCoordinate(vertex[2]);

	//변환한 z 좌표에 대해 내림차순으로 정렬
	for (int i = 0; i < 2; i++)
	{
		for (int j = i + 1; j < 3; j++)
		{
			if (vertex[i].z < vertex[j].z)
			{
				ofVec3f temp = vertex[i];
				vertex[i] = vertex[j];
				vertex[j] = temp;
			}
		}
	}

	//세 점 모두 플레이어 뒤에 존재하는 경우
	if (vertex[0].z < 0) return;
	//두 점이 플레이어 뒤에 존재하는 경우
	else if (vertex[1].z < 0)
	{
		float ratio = vertex[0].z / (vertex[1].z - vertex[0].z);
		ofVec3f new_point;
		new_point = vertex[0] - (vertex[1] - vertex[0]) * ratio;
		vertex[1] = new_point;

		ratio = vertex[0].z / (vertex[2].z - vertex[0].z);
		new_point = vertex[0] - (vertex[2] - vertex[0]) * ratio;
		vertex[2] = new_point;

		ofVec2f projection[3];
		projection[0] = m_camera.getProjectedPosition(vertex[0]);
		projection[1] = m_camera.getProjectedPosition(vertex[1]);
		projection[2] = m_camera.getProjectedPosition(vertex[2]);
		ofSetColor(color);
		ofDrawTriangle(projection[0], projection[1], projection[2]);
	}
	//한 점만 플레이어 뒤에 존재하는 경우
	else if (vertex[2].z < 0)
	{
		ofVec3f box[4];
		box[0] = vertex[0];
		box[1] = vertex[1];

		float ratio = vertex[0].z / (vertex[2].z - vertex[0].z);
		ofVec3f new_point = vertex[0] - (vertex[2] - vertex[0]) * ratio;
		box[2] = new_point;

		ratio = vertex[1].z / (vertex[2].z - vertex[1].z);
		new_point = vertex[1] - (vertex[2] - vertex[1]) * ratio;
		box[3] = new_point;

		ofVec2f projection[3];
		projection[0] = m_camera.getProjectedPosition(box[0]);
		projection[1] = m_camera.getProjectedPosition(box[1]);
		projection[2] = m_camera.getProjectedPosition(box[2]);
		ofSetColor(color);
		ofDrawTriangle(projection[0], projection[1], projection[2]);

		projection[0] = m_camera.getProjectedPosition(box[3]);
		projection[1] = m_camera.getProjectedPosition(box[1]);
		projection[2] = m_camera.getProjectedPosition(box[2]);
		ofSetColor(color);
		ofDrawTriangle(projection[0], projection[1], projection[2]);
		return;
	}
	//모두 플레이어의 앞에 존재하는 경우
	else
	{
		ofVec2f projection[3];
		projection[0] = m_camera.getProjectedPosition(vertex[0]);
		projection[1] = m_camera.getProjectedPosition(vertex[1]);
		projection[2] = m_camera.getProjectedPosition(vertex[2]);
		ofSetColor(color);
		ofDrawTriangle(projection[0], projection[1], projection[2]);
	}
}

void CDrawManager::convertPoint(ofVec3f* vertex, int vertex_num, ofVec3f position, float angle)
{
	for (int i = 0; i < vertex_num; i++)
	{
		vertex[i].rotate(angle, CObject::AXIS_Y);
		vertex[i] += position;
	}
}

void CDrawManager::setCamera(CCamera camera)
{
	m_camera = camera;
}