#pragma once

#include "ofMain.h"
#include "Player.h"
#include "DrawManager.h"
#include "RoomManager.h"
#include "MazeManager.h"

class ofApp : public ofBaseApp{
	enum class STATE { play, menu };

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		float windowWidth, windowHeight;
	private:
		BOOL move_flag;
		int player_direction;

		CRoomManager roomManager;

		STATE current_state;
		STATE changeState();

		void drawCrossHair();
};
