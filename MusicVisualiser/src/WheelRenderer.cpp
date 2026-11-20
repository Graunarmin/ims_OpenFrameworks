//
//  WheelRenderer.cpp
//  MusicVisualiser
//
//  Created by Johanna Sacher on 20.11.26.
//
#include "WheelRenderer.h"

WheelRenderer::WheelRenderer(){}

void WheelRenderer::setup(std::string name)
{
	VisualizationRenderer::setup(name);
	
}

void WheelRenderer::draw()
{
	float bandsToGet = 512;
	//float exactBarWidth = (2 * acos(0.0) * 50) / bandsToGet;
	float barWidth = 40;
	int barLength = 400;
	
	auto val = ofSoundGetSpectrum(bandsToGet);
	
	for(int i = 0; i < bandsToGet; i++)
	{
		// mapping sound to color isn't as easy as I thought. Maybe later.
		//ofDrawRectangle(100 + i * width, ofGetHeight()-100, width, -(val[i] * 200));
		
		ofPushMatrix();
		ofTranslate(ofGetWidth()/2, ofGetHeight()/2); // translate the origin to the middle of the window
		ofRotateDeg(360/bandsToGet * i); // rotate around the (newly set) origin
		
		ofColor drawingColor;
		drawingColor.setHsb(255/bandsToGet * i, 255, 255, 50);
		ofSetColor(drawingColor);
		ofDrawRectangle(50, -barWidth/2, val[i] * barLength, barWidth/2);
		
		ofPopMatrix();
	}
}
