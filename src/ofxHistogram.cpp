#include "ofxHistogram.h"



vector<float> ofxHistogram::getHistogram(ofxCvGrayscaleImage & img, int numBins) {
    vector<float> histogram;
    histogram.resize(numBins);
    
    CvHistogram* hist;
    IplImage *iplImage, **plane;
    
    iplImage = img.getCvImage();
    plane = &iplImage;
    
    int hist_size[] = { numBins };
    float range[] = { 0, 180 };
    float* ranges[] = { range };
    hist = cvCreateHist( 1, hist_size, CV_HIST_ARRAY, ranges, 1 );
    cvCalcHist( plane, hist, 0, 0 );
    cvNormalizeHist( hist, 1.0 );
    
    for (int i=0; i<numBins; i++) {
        histogram[i] = cvQueryHistValue_1D(hist, i);
    }
    cvReleaseHist( &hist );
    return histogram;
}
