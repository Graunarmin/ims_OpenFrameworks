//
//  SineColorRenderer.cpp
//  MusicVisualiser
//
//  Created by Johanna Sacher on 20.11.26.
//
#include "SineColorRenderer.h"

SineColorRenderer::SineColorRenderer(){}

void SineColorRenderer::setup(std::string name)
{
	VisualizationRenderer::setup(name);
	
	parameters.add(amplitude.set("Amplitude", 100, 1, 400));
	parameters.add(distance.set("Distance", 50, 0, 500));
	parameters.add(numberOfRibbons.set("Ribbons", 3, 1, 15));
	parameters.add(ribbonStart.set("Start at", -2, -15, 0));
	
}

void SineColorRenderer::draw()
{
	float time = ofGetElapsedTimef();
	//int bandsToGet = 512;
	auto val = ofSoundGetSpectrum(bandsToGet);
	auto screenHeight = ofGetHeight();
	
	int circlesPerBand = glm::ceil(screenHeight/bandsToGet) + 1;
	
	int bandCounter = 0;
	
	for(int ribbon = ribbonStart; ribbon < (numberOfRibbons + ribbonStart); ribbon++)
	{
		for(int p = 0; p < screenHeight; p += circlesPerBand)
		{
			//shifting the index so the lower frequencys are not cut off at the top but are rather starting around 1/4 of the screen height (from the top down)
			auto shiftedIndex = (bandCounter - bandsToGet/4) % bandsToGet;
			
			for (int i = 0; i < circlesPerBand; i++)
			{
				ofSetColor(127 + 127 * sin(bandCounter * (val[shiftedIndex] + 0.01) + time),
						   127 + 127 * sin(bandCounter * (val[shiftedIndex] + 0.011) + time),
						   127 + 127 * sin(bandCounter * (val[shiftedIndex] + 0.012) + time));
				
				//live changes: how many ribbons (x), x starting point, amplitude, distance
				//int amplitude = 100;
				//int distance = 200;
				ofDrawCircle(ofGetWidth()/2 + amplitude * ribbon * sin((p + i) * 0.01 + time) + ribbon * distance,
							 (p + i),
							 50 + 30 * sin((p + i) * 0.005 + time + ribbon));
				
			}
			bandCounter += 1;
		}
	}
}

