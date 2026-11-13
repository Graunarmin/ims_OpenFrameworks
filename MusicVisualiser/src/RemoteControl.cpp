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
	Speed = 1;
	Pan = 0;
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
			Speed = inputMessage.getArgAsFloat(0);
			
			feedbackMessage.clear();
			feedbackMessage.addFloatArg(Speed);
			feedbackMessage.setAddress("/mv-updated/speed");
			sender.sendMessage(feedbackMessage);
			
			std::cout << "New speed: " << Speed << std::endl;
		}
		else if(receivedAdress == "/mv/dial_pan")
		{
			Pan = inputMessage.getArgAsFloat(0);
			
			feedbackMessage.clear();
			feedbackMessage.addFloatArg(Pan);
			feedbackMessage.setAddress("/mv-updated/pan");
			sender.sendMessage(feedbackMessage);
			
			std::cout << "New pan: " << Pan << std::endl;
		}
		else
		{
			std::cout << "Could not identify osc address " << receivedAdress << std::endl;
		}
		
	}
}
