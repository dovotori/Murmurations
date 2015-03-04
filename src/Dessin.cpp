#include "Dessin.h"


Dessin::Dessin()
{

}

Dessin::~Dessin()
{

}


void Dessin::setup()
{

    this->process.setup(NB);
    this->forme.setup(NB);
    this->sphere.setup();
    this->background.setup();
    this->echange.setup();
    
}


void Dessin::update(Camera* camera)
{

    this->process.update();
    this->echange.update(camera, &this->process, &this->forme, &this->background);
    
}


void Dessin::draw(Camera* camera)
{
    this->background.draw();
    this->forme.draw(camera, this->process.getPosTexture(), this->process.getVelTexture(), this->sphere.getTexture());
    this->echange.draw();
    
}


//--------------------------------------------------------------
void Dessin::keyPressed(int key){
    
}

//--------------------------------------------------------------
void Dessin::keyReleased(int key){
    
}

//--------------------------------------------------------------
void Dessin::mouseDragged(int x, int y){
}

//--------------------------------------------------------------
void Dessin::mousePressed(){
}

//--------------------------------------------------------------
void Dessin::mouseReleased(){
}

