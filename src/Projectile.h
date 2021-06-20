#ifndef _MAZEMADEMAGE_PROJECTILE_H_
#define _MAZEMADEMAGE_PROJECTILE_H_
#include "Object.h"
class CProjectile : public CObject {
public:
	CProjectile();
	CProjectile(ofVec3f position);
	CProjectile(ofVec3f position, ofVec3f rotation);
	~CProjectile();

	void drawSelf();
	void update();
protected:

private:
	int m_speed;
};
#endif