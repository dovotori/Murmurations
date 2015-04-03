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
    
    float scale = 0.004;
    
    for(int y = 0; y < taille; y++)
    {
        for(int x = 0; x < taille; x++)
        {
            int i = taille * y + x;
            pos[i*3] = ofNoise((float)x*scale);
            pos[i*3 + 1] = ofNoise((float)y*scale);
            pos[i*3 + 2] = ofNoise((float)(y+x)*scale);
        }
    }
    this->image.allocate(taille, taille, GL_RGB);
    this->image.getTextureReference().loadData(pos, taille, taille, GL_RGB);
    delete [] pos;
    
}



void Noise::draw()
{
    //this->image.draw(0, 0);
}