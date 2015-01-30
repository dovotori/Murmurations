
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
    
protected:
private:
    ofMesh screen;
    ofShader shader;
    ofFbo fbo;
    
    float alpha;

    
};

#endif 