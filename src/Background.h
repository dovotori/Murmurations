
#ifndef __MurmurationsGPU7__Background__
#define __MurmurationsGPU7__Background__

#include "ofMain.h"
#include "Camera.h"

class Background
{
    
public:
    Background();
    virtual ~Background();
    void setup();
    void update();
    void draw();
    
    inline void setAlpha(float value){ this->alpha = value; };
    inline void setImage(unsigned int value){ if(value > -1 && value < this->nbImages){ this->currentImage = value; } else { this->currentImage = 0; } };
    
protected:
private:
    ofMesh screen;
    ofShader shader;
    ofImage *image;
    unsigned int nbImages, currentImage;
    float alpha;

    
};

#endif 
