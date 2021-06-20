#ifndef _MAZEMADEMAGE_MAZEMANAGER_H_
#define _MAZEMADEMAGE_MAZEMANAGER_H_
#include "ofMain.h"
#include "Room.h"

class CMazeManager {
private:
	static CMazeManager* instance;
	CMazeManager();
	~CMazeManager();

public:
	static CMazeManager* getInstance();
	Room& getRoom(int x, int y);
	void generateMaze();
	void drawMinimap();
	void drawCurrent(ofVec2f coord, float angle);

protected:
	void initMaze();
	BOOL getMovable(int x, int y);

private:
	Room m_maze[4][4];
	int m_width;
	int m_height;
	int m_minimapSize;
};
#endif