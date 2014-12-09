#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

class ofxHistogram
{
public:
    vector<float> getHistogram(ofxCvGrayscaleImage & img, int numBins);

};

