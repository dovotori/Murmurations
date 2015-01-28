

#ifndef __MurmurationsGPU__GpuProcess__
#define __MurmurationsGPU__GpuProcess__

#include "ofMain.h"
#include "Camera.h"
#include "PingPongBuffer.h"




class GpuProcess
{
public:
    GpuProcess();
    virtual ~GpuProcess();
    void setup(unsigned int nb = 1);
    void update();
    
    inline ofTexture& getPosTexture(){ return this->posPingPong.dst->getTextureReference(); };
    
protected:
private:
    ofShader    updatePos;
    ofShader    updateVel;
    
    pingPongBuffer posPingPong;
    pingPongBuffer velPingPong;
    
    float   timeStep;
    float   particleSize;
    
    int     numParticles;
    int     textureRes;
    
    void setupPosition();
    void setupVelocity();
    
    void computeGpuPosition();
    void computeGpuVelocity();
    
};

#endif
