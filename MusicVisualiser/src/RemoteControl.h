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
	
	ofxOscSender sender;
	
	ofxOscReceiver receiver;
	ofxOscMessage message;
	
	float Speed;
	float Pan;
};
