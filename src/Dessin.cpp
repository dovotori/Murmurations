#include "Dessin.h"


Dessin::Dessin()
{

}

Dessin::~Dessin()
{

}


void Dessin::setup()
{
    unsigned int closestTextureRes = (int)sqrt((float)NB);
    unsigned int closestPowerOfTwo = pow(2, ceil(log(closestTextureRes) / log(2)));
    cout << "Texture resolution: " << closestPowerOfTwo << endl;
    cout << "Nombre de particules: " << closestPowerOfTwo*closestPowerOfTwo << endl;

    this->noise.setup(256);
    this->process.setup(closestPowerOfTwo);
    this->forme.setup(closestPowerOfTwo);
    this->background.setup();
    this->echange.setup();
    this->ligne.setup(closestPowerOfTwo);
    this->effet.setup();
}


void Dessin::update(Camera* camera)
{
    this->process.update(this->noise.getTexture());
    this->echange.update(camera, &this->process, &this->forme, &this->background, &this->effet, &this->ligne);
    //this->ligne.update(this->process.getPosTexture());
}


void Dessin::draw(Camera* camera)
{
    this->background.draw();
    this->effet.begin();
        this->forme.draw(camera, this->process.getPosTexture(), this->process.getVelTexture());
        //this->ligne.draw(camera);
    this->effet.end();

    this->effet.draw();
    this->echange.draw();
    this->process.draw();
}


//--------------------------------------------------------------
void Dessin::keyPressed(int key){
    if(key == 104){ this->echange.toggleGui(); } // h
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

