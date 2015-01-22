#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // PARAMETRES OPENGL
    ofSetFrameRate(40);
    //ofSetVerticalSync(false);
    //ofEnableDepthTest(); // si actif ca desactive le blend mode c'est chiant
    //ofEnableAlphaBlending();
    //ofSetBackgroundAuto(false); // empeche le rafraichissement des buffer automatique (dissine en superposant)
    ofDisableArbTex(); // pour utiliser sampler2D dans les shaders
    
    this->camera.setup();
    this->camera.setPosition(0, 0, 100);
    this->camera.setNearFar(1.0, 200.0);
    
    this->dessin.setup();
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    this->dessin.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(ofColor(0));
    
    this->dessin.draw(&this->camera);
    
    stringstream ss;
    ss << ofGetFrameRate() << " fps";
    ofDrawBitmapString(ss.str(), ofPoint( 10, ofGetWindowHeight()-10 ) );
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
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



