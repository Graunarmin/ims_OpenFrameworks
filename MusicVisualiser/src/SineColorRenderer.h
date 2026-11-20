//
//  SineColorRenderer.h
//  MusicVisualiser
//
//  Created by Johanna Sacher on 20.11.26.
//

#pragma once

#include "ofMain.h"
#include "VisualizationRenderer.h"

class SineColorRenderer : public VisualizationRenderer
{
public:
	SineColorRenderer();
	void setup(std::string name) override;
	void draw() override;
	
	ofParameter<float> amplitude;
	ofParameter<float> distance;
	ofParameter<int> numberOfRibbons;
	ofParameter<int> ribbonStart;
};
