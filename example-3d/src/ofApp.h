#pragma once

#include "ofMain.h"
#include "ofxHistogram.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		
    ofxHistogram histogram;
    ofImage img;
    vector<vector<vector<float> > > hist;
    int numBins;
};
