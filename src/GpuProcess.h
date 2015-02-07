

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
    void resetPosition();

    inline ofTexture& getPosTexture(){ return this->posPingPong.dst->getTextureReference(); };
    inline void setComportement(unsigned int comportement){ this->comportement = comportement; };

protected:
private:
    void setupPosition();
    void setupVelocity();

    void computeGpuPosition();
    void computeGpuVelocity();

    ofShader updatePos;
    ofShader* updateVel;

    pingPongBuffer posPingPong;
    pingPongBuffer velPingPong;

    float   vitesseGenerale;
    int     numParticles;
    int     textureRes;
    unsigned int comportement;

};

#endif
