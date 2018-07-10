#include "ofxHistogram.h"



vector<float> ofxHistogram::getHistogram(ofxCvGrayscaleImage & img, int numBins) {
    vector<float> histogram;
    histogram.resize(numBins);
    
    CvHistogram* hist;
    IplImage *iplImage, **plane;
    
    iplImage = img.getCvImage();
    plane = &iplImage;
    
    int hist_size[] = { numBins };
    float range[] = { 0, 256 };
    float* ranges[] = { range };
    hist = cvCreateHist( 1, hist_size, CV_HIST_ARRAY, ranges, 1 );
    cvCalcHist( plane, hist );
    cvNormalizeHist( hist, 1.0 );
    
    for (int i=0; i<numBins; i++) {
        histogram[i] = (float)cvGetReal1D(hist->bins, i);
    }
    cvReleaseHist( &hist );
    return histogram;
}

vector<vector<vector<float> > > ofxHistogram::getHistogram3d(ofImage & img, int numBins) {
    ofxCvColorImage rgb;
    if (img.getPixels().getNumChannels() == 1) {
        ofxCvGrayscaleImage gray;
        gray.setFromPixels(img.getPixels());
        rgb = gray;
    }
    else {
        rgb.setFromPixels(img.getPixels());
    }
    return getHistogram3d(rgb, numBins);
}

vector<vector<vector<float> > > ofxHistogram::getHistogram3d(ofxCvColorImage & img, int numBins) {
    vector<vector<vector<float> > > histogram;
    for (int ir=0; ir<numBins; ir++) {
        vector<vector<float > > hist1;
        for (int ig=0; ig<numBins; ig++) {
            vector<float> hist2;
            hist2.resize(numBins);
            hist1.push_back(hist2);
        }
        histogram.push_back(hist1);
    }
    ofxCvGrayscaleImage r, g, b;
    r.setFromPixels(img.getPixels().getChannel(0));
    g.setFromPixels(img.getPixels().getChannel(1));
    b.setFromPixels(img.getPixels().getChannel(2));
    CvHistogram* hist;
    IplImage *iplImage, **plane;
    IplImage* planes[] = {r.getCvImage(), g.getCvImage(), b.getCvImage()};
    int hist_size[] = { numBins, numBins, numBins };
    float range[] = { 0, 255 };
    float* ranges[] = { range, range, range };
    hist = cvCreateHist( 3, hist_size, CV_HIST_ARRAY, ranges, 1 );
    cvCalcHist( planes, hist, 0, 0 );
    cvNormalizeHist( hist, 1.0 );
    for (int ir=0; ir<numBins; ir++) {
        for (int ig=0; ig<numBins; ig++) {
            for (int ib=0; ib<numBins; ib++) {
                histogram[ir][ig][ib] = cvGetReal3D(hist, ir, ig, ib);
            }
        }
    }    
    return histogram;
}