#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

#include <opencv2/core/core.hpp>

using std::cout;
using std::endl;
using namespace cv;


class ofxHistogram
{
public:
    vector<float> getHistogram(ofxCvGrayscaleImage & img, int numBins);
    vector<vector<vector<float> > > getHistogram3d(ofxCvColorImage & image, int numBins);
    vector<vector<vector<float> > > getHistogram3d(ofImage & img, int numBins);
};

