#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    // PARAMETRES OPENGL
    ofSetWindowTitle("Murmurations");
    ofSetFrameRate(40);
    ofEnableAlphaBlending();
    ofDisableArbTex(); // pour utiliser sampler2D dans les shaders
    //ofSetVerticalSync(false);
    //ofEnableDepthTest(); // si actif ca desactive le blend mode c'est chiant
    //ofSetBackgroundAuto(false); // empeche le rafraichissement des buffer automatique (dissine en superposant)

    this->camera.setup();
    this->camera.setPosition(0.0, 0.0, 2.0);
    this->camera.setNearFar(0.1, 1000.0);

    this->dessin.setup();

    this->isFullscreen = false;

    //ofSetWindowPosition(ofGetScreenWidth()/2-ofGetWindowWidth()/2, ofGetScreenHeight()/2-ofGetWindowHeight()/2);
    ofSetWindowPosition(0, 0);

}

//--------------------------------------------------------------
void ofApp::update(){

    this->dessin.update(&this->camera);
}

//--------------------------------------------------------------
void ofApp::draw(){

    //ofBackgroundGradient(ofColor(180), ofColor(100));
    ofBackground(ofColor(0.0));

    this->dessin.draw(&this->camera);

    stringstream ss;
    ss << endl << "[f] fullscreen // [h] GUI native ou OSC // fps " << ofGetFrameRate();
    ofDrawBitmapString(ss.str(), ofPoint( 10, ofGetWindowHeight()-20 ) );


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    this->dessin.keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == 102) // f
    {
        if(!this->isFullscreen)
        {
            ofSetFullscreen(true);
        } else {
            ofSetFullscreen(false);
        }
        this->isFullscreen = !this->isFullscreen;
    }

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



