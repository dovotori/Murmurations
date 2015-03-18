#include "Noise.h"

Noise::Noise()
{
}


Noise::~Noise()
{
}


void Noise::setup(unsigned int taille)
{
    this->largeur = taille;
    float * pos = new float[taille * taille * 3];
    for(int y = 0; y < taille; y++)
    {
        for(int x = 0; x < taille; x++)
        {
            int i = taille * y + x;
            pos[i*3] = ofNoise((float)x*0.06);
            pos[i*3 + 1] = ofNoise((float)y*0.06);
            pos[i*3 + 2] = ofNoise((float)(y+x)*0.06);
        }
    }
    this->image.allocate(taille, taille, GL_RGB);
    this->image.getTextureReference().loadData(pos, taille, taille, GL_RGB);
    delete [] pos;
    
}



void Noise::draw()
{
    this->image.draw(ofGetWindowWidth()-this->largeur-2, 2);
}