/*
Project Description:
Johanna Sacher 2026
https://github.com/Graunarmin
Sources:
 Daniel Buzzo: https://github.com/danbz/art-and-code/blob/master/openFrameworks/music-for-homemade-airports/src/ofApp.cpp
 Sound Samples: https://reverbmachine.com/blog/deconstructing-brian-eno-music-for-airports
 To fix the OS-X Problem where ofGetSoundSpectrum was not implemented: https://forum.openframeworks.cc/t/ofsoundgetspectrum-not-implemented-on-this-platform-on-osx/45398/4
*/

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetBackgroundColor(13, 17, 22);
	m_totalSampleCount = 8;
	loadSamples();
	
	autoPlayOn = true;
	m_autoPlayTempo = 0;
	showProgress = true;
	autoPlayMinTempo = 4000;
	autoPlayMaxTempo = 6000;
	m_currentTime = ofGetSystemTimeMillis();
	
	ofSetBackgroundAuto(false); // the screen won't be cleared anymore
	
}

//--------------------------------------------------------------
// update() is always called before draw() so ... every frame I guess?
void ofApp::update()
{
	if(autoPlayOn)
	{
		AutoPlay();
	}
}

//--------------------------------------------------------------
// draw() is called after update()
void ofApp::draw()
{
	FadeOutBackground();
	ofSetColor(255);
	
	if(showProgress)
	{
		DrawProgressBars();
	}
	DrawSoundReactiveVisualizer();
	
}

//--------------------------------------------------------------
void ofApp::exit(){

}

void ofApp::loadSamples()
{
	m_samples.clear();
	
	for(int i = 0; i < m_totalSampleCount; i++)
	{
		ofSoundPlayer sample;
		m_samplePath = std::format("Piano_cut/Eno-Piano-0{}_cut.wav", i+1);
		std::cout << "loading " << m_samplePath << std::endl;
		sample.load(m_samplePath);
		sample.setMultiPlay(true); //MultiPlay allows for multiple instances of the same sample to play at the same time, so you can start the same sample again, even while another instance of it is still playing.
		m_samples.push_back(sample);
	}
}
	
void ofApp::DrawProgressBars()
{
	for (int i = 0; i < m_totalSampleCount; i++) {
		if(m_samples[i].isPlaying())
		{
			ofDrawRectangle(90, (i*20) + 7, //starting point x,y
							ofMap(m_samples[i].getPosition(), 0, 1, 20, ofGetWidth()-110), //width
							18); //height
			ofDrawBitmapStringHighlight("sample " + ofToString(i + 1 ) + ":",
										10, (i+1) * 20);
		}
		else
		{
			ofDrawBitmapString("sample " + ofToString(i + 1 ) + ":",
							   10, (i+1) * 20);
		}
	}
}
	
void ofApp::AutoPlay()
{
	if(ofGetSystemTimeMillis() > m_currentTime + m_autoPlayTempo)
	{
		m_nextIndex = ofRandom(m_totalSampleCount);
		m_samples[m_nextIndex].play();
		m_currentTime = ofGetSystemTimeMillis();
		m_autoPlayTempo = ofRandom(autoPlayMinTempo, autoPlayMaxTempo);
	}
}

void ofApp::PlaySampleAt(int index)
{
	if(m_samples.size() >= index + 1)
	{
		m_samples[index].play();
	}
	else
	{
		std::cout << index << " is not a valid sample in the current selection";
	}
}

void ofApp::DrawSoundReactiveVisualizer()
{
	int barWidth = 80;
	int barLength = 300;
	float bandsToGet = 256;
	float width = (float) (5*128)/bandsToGet;
	
	auto val = ofSoundGetSpectrum(bandsToGet);
	
	for(int i = 0; i < bandsToGet; i++)
	{
		// mapping sound to color isn't as easy as I thought. Maybe later.
		//ofDrawRectangle(100 + i * width, ofGetHeight()-100, width, -(val[i] * 200));
		
		ofPushMatrix();
		ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
		ofRotateDeg(360/bandsToGet * i);
		
		ofColor drawingColor;
		drawingColor.setHsb(255/bandsToGet * i, 255, 255, 50);
		ofSetColor(drawingColor);
		ofDrawRectangle(50, -barWidth/2, val[i] * barLength, barWidth/2);
		
		ofPopMatrix();
	}
}

void ofApp::FadeOutBackground()
{
	ofSetColor(0, 0, 0, 10);
	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	switch (key) {
		case 'f':
			ofToggleFullscreen();
			break;
			
		case '1':
			PlaySampleAt(0);
			break;
		case '2':
			PlaySampleAt(1);
			break;
		case '3':
			PlaySampleAt(2);
			break;
		case '4':
			PlaySampleAt(3);
			break;
		case '5':
			PlaySampleAt(4);
			break;
		case '6':
			PlaySampleAt(5);
			break;
		case '7':
			PlaySampleAt(6);
			break;
		case '8':
			PlaySampleAt(7);
			break;
		case '9':
			PlaySampleAt(8);
			break;
		
		case 'a':
			autoPlayOn = !autoPlayOn;
			break;
		case 'g':
			showProgress = !showProgress;
			
		default:
			break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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
	
