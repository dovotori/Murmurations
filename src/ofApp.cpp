#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    // PARAMETRES OPENGL
    ofSetFrameRate(40);
    ofEnableAlphaBlending();
    ofDisableArbTex(); // pour utiliser sampler2D dans les shaders
    //ofSetVerticalSync(false);
    //ofEnableDepthTest(); // si actif ca desactive le blend mode c'est chiant
    //ofSetBackgroundAuto(false); // empeche le rafraichissement des buffer automatique (dissine en superposant)

    this->camera.setup();
    this->camera.setPosition(0.0, 0.0, 4.0);
    this->camera.setNearFar(1.0, 400.0);

    this->dessin.setup();

}

//--------------------------------------------------------------
void ofApp::update(){

    this->dessin.update(&this->camera);
}

//--------------------------------------------------------------
void ofApp::draw(){

    //ofBackgroundGradient(ofColor(180), ofColor(100));
    ofBackground(ofColor(0));

    this->dessin.draw(&this->camera);

    stringstream ss;
    ss << endl << ofGetFrameRate() << " fps";
    ofDrawBitmapString(ss.str(), ofPoint( 10, ofGetWindowHeight()-20 ) );

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    this->dessin.keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    this->dessin.keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}



