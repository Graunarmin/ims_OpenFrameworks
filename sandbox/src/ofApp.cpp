/*
Project Description:
Johanna Sacher 2026
https://github.com/Graunarmin
Sources: 
*/

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	PlayerIcon.load("character-icons/character_femaleAdventurer_walk1.png");
	player.Setup(&PlayerIcon, 3, 5);
}

//--------------------------------------------------------------
void ofApp::update()
{
	player.Update();
}

//--------------------------------------------------------------
void ofApp::draw()
{
	player.Draw();
}

//--------------------------------------------------------------
void ofApp::exit(){

}

bool ofApp::LoadImages(std::string dirName)
{
	int numberOfIcons = characterIconsDirectory.listDir(dirName);
	characterIconsDirectory.sort();
	
	if(numberOfIcons <= 0) return false;
	
	for (size_t i = 0; i < characterIconsDirectory.size(); i++)
	{
		std::string filePath = characterIconsDirectory.getPath(i);
		icons.push_back(ofImage());
		icons.back().load(filePath);
	}
	return true;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	switch (key) {
		case OF_KEY_LEFT:
			player.LeftPressed = true;
			break;
		case OF_KEY_RIGHT:
			player.RightPressed = true;
			break;
		case OF_KEY_DOWN:
			player.DownPressed = true;
			break;
		case OF_KEY_UP:
			player.UpPressed = true;
			break;
		case OF_KEY_SPACE:
			player.SpacePressed = true;
			break;
		case 'f':
			ofToggleFullscreen();
			break;
		default:
			break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
	switch (key) {
		case OF_KEY_LEFT:
			player.LeftPressed = false;
			break;
		case OF_KEY_RIGHT:
			player.RightPressed = false;
			break;
		case OF_KEY_DOWN:
			player.DownPressed = false;
			break;
		case OF_KEY_UP:
			player.UpPressed = false;
			break;
		/*case OF_KEY_SPACE:
			player.SpacePressed = false;
			break;*/
		default:
			break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
