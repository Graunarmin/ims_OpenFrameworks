//
//  VisualizationRenderer.h
//  MusicVisualiser
//
//  Created by Johanna Sacher on 20.11.26.
//

#pragma once
#include "ofMain.h"
#include "ofParameter.h"

class VisualizationRenderer
{
public:
	VisualizationRenderer();
	
	virtual void setup(std::string name, float &mainGuiHeight);
	virtual void draw();
	
	ofParameterGroup parameters;
	ofParameter<int> bandsToGet;
	
protected:
	virtual void DrawGui();
	
};
