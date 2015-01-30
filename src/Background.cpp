#include "Background.h"

Background::Background()
{
    //ctor
}


Background::~Background()
{
    //dtor
}


void Background::setup()
{
    this->alpha = M_PI / 2.0;
    
    this->shader.load("shader/textureFlat");
    
    this->screen.setMode(OF_PRIMITIVE_TRIANGLES);
    
    this->screen.addVertex(ofVec3f(-1.0, 1.0, 0.0));
    this->screen.addVertex(ofVec3f(-1.0, -1.0, 0.0));
    this->screen.addVertex(ofVec3f(1.0, 1.0, 0.0));
    
    this->screen.addVertex(ofVec3f(-1.0, -1.0, 0.0));
    this->screen.addVertex(ofVec3f(1.0, 1.0, 0.0));
    this->screen.addVertex(ofVec3f(1.0, -1.0, 0.0));
    
    this->screen.addTexCoord(ofVec2f(0.0, 0.0));
    this->screen.addTexCoord(ofVec2f(0.0, 1.0));
    this->screen.addTexCoord(ofVec2f(1.0, 0.0));
    
    this->screen.addTexCoord(ofVec2f(0.0, 1.0));
    this->screen.addTexCoord(ofVec2f(1.0, 0.0));
    this->screen.addTexCoord(ofVec2f(1.0, 1.0));
    
    
    // CHARGER FBO
    ofImage image;
    image.loadImage("image/background_1.jpg");
    this->fbo.allocate(ofGetWindowWidth(), ofGetWindowHeight(), GL_RGB32F);
    this->fbo.begin();
        ofClear(0, 0, 0, 255);
        image.draw(0, 0);
    this->fbo.end();
}


void Background::update()
{
}


void Background::draw()
{
    this->alpha += 0.01;
    
    this->shader.begin();
        this->shader.setUniform1f("alpha", this->alpha);
        this->shader.setUniformTexture("tex", this->fbo.getTextureReference(0), 0);
        this->shader.setUniform2f("resolution", ofGetWindowWidth(), ofGetWindowHeight());
        this->screen.draw();
    this->shader.end();
    
    //this->fbo.draw(0, 0);
}

