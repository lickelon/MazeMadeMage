#ifndef _MAZEMADEMAGE_MONSTER_H_
#define _MAZEMADEMAGE_MONSTER_H_
#include "Object.h"
class CMonster : public CObject {
public:
	CMonster();
	CMonster(ofVec3f& position);
	CMonster(ofVec3f& position, ofVec3f& rotation);
	~CMonster();

	void drawSelf();
	void update(ofVec3f player_position);

protected:
	void drawHead(ofVec3f position, float angle);
	void changeDirection(ofVec3f player_position);

private:
	int m_speed;
};
#endif