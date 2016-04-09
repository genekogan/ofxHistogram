#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    numBins = 8;
    img.load("american-flag-0088.jpg");
    hist = histogram.getHistogram3d(img, numBins);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofSetColor(255);
    img.draw(0, 0, 300, 200);
    ofTranslate(20, 240);
    
    float tileSize = 30;
    
    for (int r=0; r<numBins; r++) {
        ofPushMatrix();
        ofTranslate((r % 4) * (numBins * tileSize + 20), floor(r / 4) * (numBins * tileSize + 20));
        for (int g=0; g<numBins; g++) {
            for (int b=0; b<numBins; b++) {
                ofSetColor(256 * r / numBins, 256 * g / numBins, 256 * b / numBins);
                ofDrawRectangle(tileSize * g, tileSize * b, tileSize, tileSize);
                string s = ofToString(floor(100*hist[r][g][b]));
                ofSetColor(255);
                ofDrawBitmapString(s, tileSize * g+2, tileSize * (b+0.5));
            }
        }
        ofPopMatrix();
    }
}
