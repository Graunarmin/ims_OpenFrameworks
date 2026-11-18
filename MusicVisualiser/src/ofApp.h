/*
Project Description:
Johanna Sacher 2026
https://github.com/Graunarmin
Sources: 
*/

#pragma once

#include "ofMain.h"
#include "RemoteControl.h"

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

	private:
		void LoadSamples();
		void AutoPlay();
		void PlaySampleAt(int index);
		void DrawProgressBars();
		void WriteHelpText();
		void DrawFrequencyWheel();
		void DrawSineWaveRadiusSpectrum();
		void DrawSineWaveColorSpectrum();
		void FadeOutBackground();
	
		void UpdateSpeedBy(float amount);
		void UpdateSpeedTo(float &newSpeed);
		void UpdatePanBy(float amount);
		void UpdatePanTo(float &newPan);
	
		void ToggleAutoPlay();
		void UpdateAutoPlayTo(bool &newValue);
		void OnSampleTrackSelected(int &buttonNumber);
		void UpdateVisuStyleTo(int &index);
		void UpdateVisuStyleTo(int index);
		
		float m_currentTime;
		int m_totalSampleCount;
		int m_visualizationIndex;
		
		std::vector<ofSoundPlayer> m_samples;
		std::string m_samplePath;
		int m_nextSampleIndex;
		float m_sampleSpeed;
		float m_samplePan;
	
		float m_autoPlayTempo;
		float m_autoPlayMinTempo;
		float m_autoPlayMaxTempo;
		bool m_autoPlayOn;
		bool m_showProgress;
		
		RemoteControl controller;
	
};
