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
    this->forme.draw(camera, this->process.getPosTexture());
}


//--------------------------------------------------------------
void Dessin::keyPressed(int key){
    /*
     if(key == 356) { // gauche
        cout << "Rotation +" << endl;
        //this->forme.addRotation(10.0);
    } else if(key == 358) { // droite
        cout << "Rotation -" << endl;
        //this->forme.addRotation(-10.0);
    }*/
}

//--------------------------------------------------------------
void Dessin::keyReleased(int key){
    /*
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
    } else if(key == 52) { // 4
            cout << "Comportement Path actif" << endl;
            this->process.setComportement(3);

    } else if(key == 97) { // a
        cout << "Rendu Ligne actif" << endl;
        this->forme.setRendu(1);
    } else if(key == 122) { // z
        cout << "Rendu Point actif" << endl;
        this->forme.setRendu(2);
    } else if(key == 101) { // e
        cout << "Rendu Forme actif" << endl;
        this->forme.setRendu(0);
    } else if(key == 114) { // r
        cout << "Rendu Crazy actif" << endl;
        this->forme.setRendu(3);
    } else if(key == 116) { // t
        cout << "Rendu Image actif" << endl;
        this->forme.setRendu(4);

    } else if(key == 127) { // delete
        cout << "Reset position" << endl;
        this->process.resetPosition();
    } else if(key == 110) { // n
        if(this->forme.getNoiseInfluence() == 0.0){ this->forme.setNoiseInfluence(0.5); cout << "Noise influence: " << 0.5 << endl; }
        else if (this->forme.getNoiseInfluence() == 0.5){ this->forme.setNoiseInfluence(1.0); cout << "Noise influence: " << 1.0 << endl; }
        else if (this->forme.getNoiseInfluence() == 1.0){ this->forme.setNoiseInfluence(2.0); cout << "Noise influence: " << 2.0 << endl; }
        else if (this->forme.getNoiseInfluence() == 2.0){ this->forme.setNoiseInfluence(0.0); cout << "Noise influence: " << 0.0 << endl; }

    }
    //*/
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

