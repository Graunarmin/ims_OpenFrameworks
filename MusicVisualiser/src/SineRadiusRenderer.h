//
//  SineRadiusRenderer.h
//  MusicVisualiser
//
//  Created by Johanna Sacher on 20.11.26.
//

#pragma once

#include "ofMain.h"
#include "SineColorRenderer.h"

class SineRadiusRenderer : public SineColorRenderer
{
public:
	SineRadiusRenderer();
	void setup(std::string name, float &mainGuiHeight) override;
	void draw() override;
	
	ofParameter<float> radiusModifier;
	
protected:
	void DrawGui() override;
};
