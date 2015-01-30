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
void Dessin::keyReleased(int key){

    if(key == 48) { // 0
        cout << "Flocking active" << endl;
        this->process.setComportement(0);
    } else if(key == 49) { // 1
        cout << "Pong active" << endl;
        this->process.setComportement(1);
    }
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

