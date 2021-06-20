#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("Maze Made Mage");
	ofSetFrameRate(60);
	ofBackground(255, 255, 255);
	windowWidth = ofGetWidth();
	windowHeight = ofGetHeight();
	ofSetWindowPosition((ofGetScreenWidth() - windowWidth) / 2, (ofGetScreenHeight() - windowHeight) / 2);
	ofHideCursor();
	SetCursorPos(ofGetScreenWidth() / 2, ofGetScreenHeight() / 2);
	roomManager.getPlayer().getCamera().setWindowSize(windowWidth, windowHeight);

	ofSetColor(0);
	ofSetLineWidth(5);

	ofSetEscapeQuitsApp(false);

	move_flag = false;

	srand(time(NULL));
}

//--------------------------------------------------------------
void ofApp::update(){
	if (player_direction)
	{
		roomManager.keyboardInput(player_direction);
	}
	roomManager.processObjects();
}

//--------------------------------------------------------------
void ofApp::draw(){
	CDrawManager* drawManager = CDrawManager::getInstance();
	drawManager->setCamera(roomManager.getPlayer().getCamera());
	
	roomManager.drawRoom();
	roomManager.drawObjects();

	drawCrossHair();

	CMazeManager::getInstance()->drawMinimap();
	ofVec3f rotation = roomManager.getPlayer().getRotation();
	rotation.y = 0;
	float angle = rotation.angle(CObject::AXIS_Z);
	if (rotation.x < 0)
	{
		angle *= -1;
	}
	CMazeManager::getInstance()->drawCurrent(roomManager.getRoomCoord(), angle);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key)
	{
	case 'w':
		player_direction |= CPlayer::FRONT;
		break;
	case 'a':
		player_direction |= CPlayer::LEFT;
		break;
	case 's':
		player_direction |= CPlayer::BACK;
		break;
	case 'd':
		player_direction |= CPlayer::RIGHT;
		break;
	case OF_KEY_ESC:
		changeState();
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	switch (key)
	{
	case 'w':
		player_direction &= 15 ^ CPlayer::FRONT;
		break;
	case 'a':
		player_direction &= 15 ^ CPlayer::LEFT;
		break;
	case 's':
		player_direction &= 15 ^ CPlayer::BACK;
		break;
	case 'd':
		player_direction &= 15 ^ CPlayer::RIGHT;
		break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
	switch (current_state)
	{
		case STATE::play:
		{
			SetCursorPos(ofGetScreenWidth() / 2, ofGetScreenHeight() / 2);
			float dx = x - windowWidth / 2;
			float dy = y - windowHeight / 2;

			roomManager.mouseInput(dx, dy);
			break;
		}
		case STATE::menu:
		{
			//커서가 가리키는 버튼 가져오기
			break;
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	switch (button)
	{
	case OF_MOUSE_BUTTON_1:
		roomManager.mouseClicked();
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

	switch (current_state)
	{
		case STATE::play:
		{
			SetCursorPos(ofGetScreenWidth() / 2, ofGetScreenHeight() / 2);
			break;
		}
		case STATE::menu:
		{
			//커서가 가리키는 버튼 가져오기
			break;
		}
	}
	//SetCursorPos(x, y);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

ofApp::STATE ofApp::changeState()
{
	if (current_state == STATE::play)
	{
		current_state = STATE::menu;
		ofShowCursor();
	}
	else if (current_state == STATE::menu)
	{
		current_state = STATE::play;
		ofHideCursor();
	}
	return current_state;
}

void ofApp::drawCrossHair()
{
	ofSetColor(255);
	ofSetLineWidth(3);
	ofDrawLine(windowWidth / 2 - 10.5, windowHeight / 2, windowWidth / 2 + 10.5, windowHeight / 2);
	ofDrawLine(windowWidth / 2, windowHeight / 2 - 10.5, windowWidth / 2, windowHeight / 2 + 10.5);
	ofSetColor(0);
	ofSetLineWidth(2);
	ofDrawLine(windowWidth / 2 - 10, windowHeight / 2, windowWidth / 2 + 10, windowHeight / 2);
	ofDrawLine(windowWidth / 2, windowHeight / 2 - 10, windowWidth / 2, windowHeight / 2 + 10);
}