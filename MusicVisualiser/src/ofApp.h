/*
Project Description:
Johanna Sacher 2026
https://github.com/Graunarmin
Sources: 
*/

#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxDropdown.h"
#include "RemoteControl.h"
#include "VisualizationRenderer.h"
#include "WheelRenderer.h"
#include "SineColorRenderer.h"
#include "SineRadiusRenderer.h"

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
		
		//void RemoveOldGuiParamaters();
	
		/// \brief Adds the given amount to the current speed and sends an update to the remote control, to update the osc-interface.
		/// Callback function for key presses.
		void UpdateSpeedBy(float amount);
		
		/// \brief Sets the speed to the given value.
		/// Callback function for changes from RemoteControl (via OSC).
		void UpdateSpeedTo(float &newSpeed);
	
		/// \brief Sends an update via OSC with the new speed.
		/// Callback function for gui changes concerning speed, to update the osc-interface
		void NotifyOscOnSpeedChange(float &newSpeed);
	
		/// \brief Adds the given amount to the current pan and sends an update to the remote control, to update the osc-interface.
		/// Callback function for key presses.
		void UpdatePanBy(float amount);
	
		/// \brief Sets the pan value to the given amount.
		/// Callback function for changes from RemoteControl (via OSC).
		void UpdatePanTo(float &newPan);
		
		/// \brief Sends an update via OSC with the new pan.
		/// Callback function for gui changes concerning pan, to update the osc-interface.
		void NotifyOscOnPanChange(float &newPan);
	
		/// \brief Sets the index of the visualization to the given index and also updates the gui respectively.
		void UpdateVisuStyleTo(int &index);
	
		/// \brief Calls UpdateVisuStyleTo() and additionaly sends an update to the remote control, to update the osc-interface.
		void OnVisuStyleChangedManual(int index);
	
		/// \brief Callback function for changes in the gui concerning the visualization-sytle. Calls OnVisuStyleChangedManual() because that one cannot receive a reference but this one must -.-
		void OnGuiVisuStyleChanged(int &index);
	
		/// \brief Toggles autoplay to the opposite of it's current value and sends an update to the remote control, to update the osc-interface.
		/// Callback function for key presses.
		void ToggleAutoPlay();

		/// \brief Sets autoplay to the given value.
		/// Callback function for changes from RemoteControl (via OSC).
		void UpdateAutoPlayTo(bool &newValue);

		/// \brief Calls PlaySampleAt() with the given number - 1.
		/// Callback function for selections via RemoteControl (via OSC).
		void OnSampleTrackSelected(int &buttonNumber);
			
		float m_currentTime;
		int m_totalSampleCount;
		int m_visualizationIndex;
		//int m_previousVisu;
		//bool m_visuGuiUpdated;
		
		std::vector<ofSoundPlayer> m_samples;
		std::string m_samplePath;
		int m_nextSampleIndex;
		ofParameter<float> m_sampleSpeed;
		ofParameter<float> m_samplePan;
		
		float m_autoPlayTempo;
		float m_autoPlayMinTempo;
		float m_autoPlayMaxTempo;
		ofxToggle m_autoPlayOn;
		bool m_showProgress;
		bool m_showGui;
		bool m_showHelp;
		
		ofxPanel gui;
		ofxPanel wheelPanel;
		ofxPanel sineRadiusPanel;
		ofxPanel sineColorPanel;
		ofParameterGroup parameters;
		std::unique_ptr<ofxIntDropdown> visuStylesDropdown;
			
		RemoteControl controller;
		WheelRenderer rendererWheel;
		SineRadiusRenderer rendererRadius;
		SineColorRenderer rendererColor;
	
		int m_progressX;
		int m_helpX;
		int m_helpYbottomOffset;
	
};
