#include "Dessin.h"

#define NB 1000

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
    this->background.setup();
    
}


void Dessin::update()
{
    
    this->process.update();
    
}


void Dessin::draw(Camera* camera)
{
    this->background.draw();
    this->forme.draw(camera, this->process.getPosTexture());
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

