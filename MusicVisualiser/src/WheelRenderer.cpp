//
//  WheelRenderer.cpp
//  MusicVisualiser
//
//  Created by Johanna Sacher on 20.11.26.
//
#include "WheelRenderer.h"

WheelRenderer::WheelRenderer()
{}

void WheelRenderer::setup(std::string name, float &mainGuiHeight)
{
	VisualizationRenderer::setup(name, mainGuiHeight);

	parameters.add(barWidth.set("Bar width", 40, 1, 100));
	parameters.add(barLength.set("Bar length", 400, 50, 1000));
	
}

void WheelRenderer::draw()
{
	float btG = this -> bandsToGet; // I'm not sure why, but here this has to be a float
	
	auto val = ofSoundGetSpectrum(btG);
	
	for(int i = 0; i < btG; i++)
	{
		ofPushMatrix();
		ofTranslate(ofGetWidth()/2, ofGetHeight()/2); // translate the origin to the middle of the window
		ofRotateDeg(360/btG * i); // rotate around the (newly set) origin
		
		ofColor drawingColor;
		drawingColor.setHsb(255/btG * i, 255, 255, 50);
		ofSetColor(drawingColor);
		ofDrawRectangle(50, -barWidth/2, val[i] * barLength, barWidth/2);
		
		ofPopMatrix();
	}
}

void WheelRenderer::DrawGui()
{
	//panel.draw();
}
