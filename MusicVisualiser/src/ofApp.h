/*
Project Description:
Johanna Sacher 2026
https://github.com/Graunarmin
Sources: 
*/

#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup() override;
		void update() override;
		void draw() override;
		void exit() override;

		void keyPressed(int key) override;
		void keyReleased(int key) override;
		void mouseMoved(int x, int y ) override;
		void mouseDragged(int x, int y, int button) override;
		void mousePressed(int x, int y, int button) override;
		void mouseReleased(int x, int y, int button) override;
		void mouseScrolled(int x, int y, float scrollX, float scrollY) override;
		void mouseEntered(int x, int y) override;
		void mouseExited(int x, int y) override;
		void windowResized(int w, int h) override;
		void dragEvent(ofDragInfo dragInfo) override;
		void gotMessage(ofMessage msg) override;
	
	void loadSamples();
	
	float autoPlayMinTempo;
	float autoPlayMaxTempo;
	bool autoPlayOn;
	
	
	
	bool showProgress;
	
	ofxPanel gui;
	
	ofParameter<bool> autoplay;
	
	//ofxSlider autoPlayTempo;
	
	//ofParameter<float> minTempo;
	//ofParameter<float> maxTempo;
	
private:
	void AutoPlay();
	void PlaySampleAt(int index);
	void DrawProgressBars();
	void DrawSoundReactiveVisualizer();
	void FadeOutBackground();
	
	int m_totalSampleCount;
	float m_currentTime;
	
	float m_autoPlayTempo;
	
	std::vector<ofSoundPlayer> m_samples;
	std::string m_samplePath;
	int m_nextIndex;
	
};
