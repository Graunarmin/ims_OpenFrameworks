//
//  sketches.cpp
//  mySketch
//
//  Created by Johanna Sacher on 26.06.26.
//

#include "ofMain.h"
#include "sketches.h"




void sketches::DrawColorGrid()
{
		for (int y = 0; y < ofGetHeight(); y += 20)
	{
		for (int x = 0; x < ofGetWidth(); x += 20)
		{
			drawingColor.setHsb(ofMap(x, 0, ofGetWidth(), 0, 255),
								ofMap(y, 0, ofGetHeight(), 0, 255),
								ofMap(ofGetMouseY(), 0, ofGetHeight(), 0, 255)
								);
			ofSetColor(drawingColor);
			ofDrawRectangle(x, y, 20, 20);
		}
	}
}

void sketches::DrawFunkyLines()
{
	drawingColor.set(251, 70, 76);
	ofSetColor(drawingColor);
	ofSetLineWidth(2);
	ofDrawLine(100, 100, 400, 400);
	ofSetLineWidth(8);
	ofDrawLine(400, 400, 200, 500);
}

void sketches::DrawPolyLine()
{
	polyline.draw();
}

void sketches::AddVertexToPolyline()
{
	polyline.addVertex(ofRandom(ofGetWidth()),
							  ofRandom(ofGetHeight())
							  );
}
