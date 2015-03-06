#include "Dessin.h"


Dessin::Dessin()
{

}

Dessin::~Dessin()
{

}


void Dessin::setup()
{
    this->noise.setup(256);
    this->process.setup(NB, this->noise.getTexture());
    this->forme.setup(NB);
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
    this->forme.draw(camera, this->process.getPosTexture(), this->process.getVelTexture());
    this->echange.draw();
}


//--------------------------------------------------------------
void Dessin::keyPressed(int key){
    //if(key == 104){ this->echange.toggleGui(); } // h
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

