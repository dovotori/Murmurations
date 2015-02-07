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
    //this->background.setup();

}


void Dessin::update()
{

    this->process.update();

}


void Dessin::draw(Camera* camera)
{
    //this->background.draw();
    this->forme.draw(camera, this->process.getPosTexture());
}


//--------------------------------------------------------------
void Dessin::keyReleased(int key){

    cout << "key: " << key << endl;
    if(key == 49) { // 1
        cout << "Comportement Flocking actif" << endl;
        this->process.setComportement(0);
    } else if(key == 50) { // 2
        cout << "Comportement Noise actif" << endl;
        this->process.setComportement(1);
    } else if(key == 51) { // 3
            cout << "Comportement Attraction actif" << endl;
            this->process.setComportement(2);

    } else if(key == 97) { // a
        cout << "Rendu Ligne actif" << endl;
        this->forme.setRendu(1);
    } else if(key == 122) { // z
        cout << "Rendu Point actif" << endl;
        this->forme.setRendu(2);
    } else if(key == 101) { // e
        cout << "Rendu Forme actif" << endl;
        this->forme.setRendu(0);
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

