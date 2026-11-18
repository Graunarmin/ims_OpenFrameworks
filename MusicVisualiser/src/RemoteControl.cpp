//
//  RemoteControl.cpp
//  MusicVisualiser
//
//  Created by Johanna Sacher on 13.11.26.
//

#include "RemoteControl.h"

RemoteControl::RemoteControl()
{
	std::cout << "Setting up OSC Controls" << std::endl;
	sender.setup("192.168.178.69", 8000);
	receiver.setup(8001);
	message.setAddress("/mv");
}

void RemoteControl::Setup()
{
	
}

void RemoteControl::Update()
{
	while (receiver.hasWaitingMessages())
	{
		ofxOscMessage inputMessage;
		receiver.getNextMessage(inputMessage);
		std::cout << "Osc Input: " << inputMessage.getArgAsFloat(0) << std::endl;
		
		ofxOscMessage feedbackMessage;
		
		auto receivedAdress = inputMessage.getAddress();
		
		if(receivedAdress == "/mv/fader_speed")
		{
			auto speed = inputMessage.getArgAsFloat(0);
			ofNotifyEvent(OnSpeedChanged, speed);
			SendSpeedChangeFeedback(speed);
		}
		else if(receivedAdress == "/mv/dial_pan")
		{
			auto pan = inputMessage.getArgAsFloat(0);
			ofNotifyEvent(OnPanChanged, pan);
			SendPanChangeFeedback(pan);
		}
		else if(receivedAdress == "/mv/auto-play")
		{
			bool autoPlay = inputMessage.getArgAsBool(0);
			ofNotifyEvent(OnAutoPlayChanged, autoPlay);
			SendAutoPlayChangeFeedback(autoPlay);
			
		}
		else if(receivedAdress == "/mv/sample-selection")
		{
			// The buttons send two messages, one on press (true) and one on release (false), but we only want to play the sample once
			if(inputMessage.getArgAsBool(1))
			{
				int sampleIndex = inputMessage.getArgAsInt(0);
				ofNotifyEvent(OnNewSampleSelected, sampleIndex);
				
			}
		}
		else if(receivedAdress == "/mv/visu-style")
		{
			auto index = inputMessage.getArgAsInt(0);
			ofNotifyEvent(OnVisuStyleChanged, index);
			SendVisuChangeFeedback(index);
		}
		else
		{
			std::cout << "Could not identify osc address " << receivedAdress << std::endl;
		}
		
	}
}


void RemoteControl::SendSpeedChangeFeedback(float speedValue)
{
	ofxOscMessage feedbackMessage;

	feedbackMessage.addFloatArg(speedValue);
	feedbackMessage.setAddress("/mv-updated/speed");
	sender.sendMessage(feedbackMessage);
}

void RemoteControl::SendPanChangeFeedback(float panValue)
{
	ofxOscMessage feedbackMessage;

	feedbackMessage.addFloatArg(panValue);
	feedbackMessage.setAddress("/mv-updated/pan");
	sender.sendMessage(feedbackMessage);
}

void RemoteControl::SendAutoPlayChangeFeedback(bool autoPlayValue)
{
	ofxOscMessage feedbackMessage;

	feedbackMessage.addFloatArg(autoPlayValue);
	feedbackMessage.setAddress("/mv-updated/auto-play");
	sender.sendMessage(feedbackMessage);
}

void RemoteControl::SendVisuChangeFeedback(int visuIndex)
{
	ofxOscMessage feedbackMessage;

	feedbackMessage.addFloatArg(visuIndex);
	feedbackMessage.setAddress("/mv-updated/visu-style");
	sender.sendMessage(feedbackMessage);
}
