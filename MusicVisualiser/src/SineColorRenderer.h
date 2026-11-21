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
		void setup(std::string name, float &mainGuiHeight) override;
		void draw() override;
		
		ofParameter<float> amplitude;
		ofParameter<float> distance;
		ofParameter<int> numberOfRibbons;
		ofParameter<int> ribbonStart;
		
	// Optional: Add modifiers for color (rgb) and a reset button
	
protected:
	void DrawGui() override;
};
