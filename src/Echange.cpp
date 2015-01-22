#include "Echange.h"

Echange::Echange()
{
    //ctor
}

Echange::~Echange()
{
    //dtor
}


void Echange::setup()
{
    this->nbVariables = 3;
    for(int i = 0; i < NB_VAR_MAX; i++){ this->variables[i] = 0.0; this->isDraw[i] = false; }
    receiver.setup(PORT);
    this->click = false;
}


void Echange::update()
{
    ofxOscMessage m;
    receiver.getNextMessage(&m);


    string adresse = m.getAddress();
    this->nbVariables = m.getNumArgs();

    for(int i = 0; i < this->nbVariables; i++)
    {

        if(i < NB_VAR_MAX)
        {
            string argumentType = m.getArgTypeName(i);


            if(m.getAddress() == "/tfg/posX"){
                this->variables[0] = m.getArgAsFloat(i);
            }

            if(m.getAddress() == "/tfg/posY"){
                this->variables[1] = m.getArgAsFloat(i);
            }

            if(m.getAddress() == "/tfg/mousePressed"){
                if(m.getArgAsInt32(i) == 0){ this->click = true; } else { this->click = false; }
                cout << m.getArgAsInt32(i) << endl;
            }

            /*
            if(m.getArgType(i) == OFXOSC_TYPE_INT32){
                //ofToString(m.getArgAsInt32(i));
            }
            else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
                //ofToString(m.getArgAsFloat(i));
                this->variables[i] = m.getArgAsFloat(i);
            }
            else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
                //m.getArgAsString(i);
            }*/

        }
    }







}


void Echange::draw()
{

    cout << "nombre de variables:" << this->nbVariables << endl;

}


float* Echange::getVar()
{

    return this->variables;

}






