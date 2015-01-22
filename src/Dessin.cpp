#include "Dessin.h"

Dessin::Dessin()
{

}

Dessin::~Dessin()
{

}


void Dessin::setup()
{
    
    this->process.setup(1000);
    
}


void Dessin::update()
{
    this->process.update();
    
    
}


void Dessin::draw(Camera* camera)
{
    this->process.draw(camera);
    
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

