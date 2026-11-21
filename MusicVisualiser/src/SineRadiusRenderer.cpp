//
//  SineRadiusRenderer.cpp
//  MusicVisualiser
//
//  Created by Johanna Sacher on 20.11.26.
//
#include "SineRadiusRenderer.h"

SineRadiusRenderer::SineRadiusRenderer(){}

void SineRadiusRenderer::setup(std::string name, float &mainGuiHeight)
{
	VisualizationRenderer::setup(name, mainGuiHeight);
	
	parameters.add(amplitude.set("Amplitude", 100, 1, 400));
	parameters.add(distance.set("Distance", 50, 0, 500));
	parameters.add(numberOfRibbons.set("Ribbons", 1, 1, 11));
	parameters.add(ribbonStart.set("Start at", 0, -11, 0));
	parameters.add(radiusModifier.set("Radius", 0.2, 0, 1));
	
}

void SineRadiusRenderer::draw()
{
	float time = ofGetElapsedTimef();
	auto val = ofSoundGetSpectrum(bandsToGet);
	auto screenHeight = ofGetHeight();
	
	int circlesPerBand = glm::ceil(screenHeight/bandsToGet) + 1;
	bool evenNumberOfCircles = circlesPerBand % 2 == 0;
	int halfTheCircles = glm::floor(circlesPerBand/2);
	int stepsToMiddle = glm::ceil(circlesPerBand / 2);
	
	int bandCounter = 0;
	
	for(int ribbon = ribbonStart; ribbon < (numberOfRibbons - ribbonStart); ribbon++)
	{
		for(int p = 0; p < screenHeight; p += circlesPerBand)
		{
			auto shiftedIndex = (bandCounter - bandsToGet/5) % bandsToGet;
			
			for (int i = 0; i < circlesPerBand; i++)
			{
				ofSetColor(127 + 127 * sin((p+i) * 0.02 + time + ribbon),
						   127 + 127 * sin((p+i) * 0.021 + time + ribbon),
						   127 + 127 * sin((p+i) * 0.022 + time + ribbon));
				
				// Interpolation between the radii so the change is a bit smoother
				float lerpedRadius;
				
				if(!evenNumberOfCircles)
				{
					float step = ((i % stepsToMiddle) + 1) / stepsToMiddle;
					if(i < halfTheCircles)
					{
						lerpedRadius = ofLerp(val[shiftedIndex-1], val[shiftedIndex], step);
					}
					else if(i > halfTheCircles)
					{
						lerpedRadius = ofLerp(val[shiftedIndex], val[shiftedIndex + 1], step);
					}
					else
					{
						lerpedRadius = val[shiftedIndex];
					}
				}
				else
				{
					if(i < halfTheCircles -1)
					{
						lerpedRadius = ofLerp(val[shiftedIndex - 1], val[shiftedIndex], (i+1) / stepsToMiddle);
					}
					else if(i > halfTheCircles + 1)
					{
						lerpedRadius = ofLerp(val[shiftedIndex], val[shiftedIndex + 1], (i % stepsToMiddle) / stepsToMiddle);
					}
					else
					{
						lerpedRadius = val[shiftedIndex];
					}
				}
				
			
				ofDrawCircle(ofGetWidth()/2 + amplitude * sin((p + i) * 0.01 + time) + ribbon * distance,
							 (p + i),
							 50 + 20 * sin((lerpedRadius * bandCounter + bandCounter) * radiusModifier + time + ribbon));
			}
			bandCounter += 1;
		}
	}
}

void SineRadiusRenderer::DrawGui(){}
