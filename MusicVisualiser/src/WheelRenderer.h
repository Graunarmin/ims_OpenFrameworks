//
//  WheelRenderer.h
//  MusicVisualiser
//
//  Created by Johanna Sacher on 20.11.26.
//
#pragma once

#include "ofMain.h"
#include "VisualizationRenderer.h"


class WheelRenderer : public VisualizationRenderer
{
	public:
		WheelRenderer();
		void setup(std::string name, float &mainGuiHeight) override;
		
		void draw() override;
		
		ofParameter<int> barWidth;
		ofParameter<int> barLength;
	
	protected:
	void DrawGui() override;
};
