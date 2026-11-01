//
//  sketches.h
//  mySketch
//
//  Created by Johanna Sacher on 26.06.26.
//
#ifndef SKETCHES_H_
#define SKETCHES_H_

class sketches
{
	public:
		void DrawColorGrid();
		void DrawFunkyLines();
		void AddVertexToPolyline();
		void DrawPolyLine();
private:
	ofColor drawingColor;
	ofPolyline polyline;
};
#endif /* SKETCHES_H_ */
