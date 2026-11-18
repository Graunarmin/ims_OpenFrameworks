//  RemoteControl.h
//  MusicVisualiser
//
//  Created by Johanna Sacher on 13.11.26.
//

#pragma once
#include "ofMain.h"
#include <iostream>
#include "ofxOsc.h"

class RemoteControl
{
public:
	RemoteControl();
	
	void Setup();
	void Update();
	
	ofEvent<float> OnSpeedChanged;
	ofEvent<float> OnPanChanged;
	ofEvent<bool> OnAutoPlayChanged;
	ofEvent<int> OnNewSampleSelected;
	ofEvent<int> OnVisuStyleChanged;
	
	void SendSpeedChangeFeedback(float speedValue);
	void SendPanChangeFeedback(float panValue);
	void SendVisuChangeFeedback(int visuIndex);
	void SendAutoPlayChangeFeedback(bool autoPlayValue);
	
private:
	
	
	ofxOscSender sender;
	
	ofxOscReceiver receiver;
	ofxOscMessage message;

};
