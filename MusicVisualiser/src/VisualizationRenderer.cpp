//
//  VisualizationRenderer.cpp
//  MusicVisualiser
//
//  Created by Johanna Sacher on 20.11.26.
//

#include "VisualizationRenderer.h"

VisualizationRenderer::VisualizationRenderer()
{
	
}

void VisualizationRenderer::setup(std::string name)
{
	parameters.setName(name);
	parameters.add(bandsToGet.set("Bands to get", 512, 64, 512));
}

void VisualizationRenderer::draw(){ }
