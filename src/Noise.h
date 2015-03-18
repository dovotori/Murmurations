#ifndef __MurmurationsGPU_Lien__Noise__
#define __MurmurationsGPU_Lien__Noise__

#include "ofMain.h"

class Noise {
public:
    Noise();
    virtual ~Noise();
    void setup(unsigned int taille);
    void draw();
    
    inline ofTexture& getTexture(){ return this->image.getTextureReference(); };
    
protected:
private:
    ofFbo image;
    unsigned int largeur;
};

#endif