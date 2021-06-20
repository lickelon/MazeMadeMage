#ifndef _MAZEMADEMAGE_ROOM_H_
#define _MAZEMADEMAGE_ROOM_H_
#include "ofMain.h"
struct Room {
	BOOL up;
	BOOL left;
	BOOL down;
	BOOL right;

	BOOL visit;

	int mob_count;
};
#endif;