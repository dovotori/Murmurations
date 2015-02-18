

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
    inline void setMaxSpeed(float value){ this->maxSpeed = value; };
    
    inline void setDistanceFlocking(float x, float y, float z){ this->distanceFlocking.set(x, y, z); };
    inline void setMagnitudeFlocking(float x, float y, float z){ this->magnitudeFlocking.set(x, y, z); };
    
    inline void setSensAttraction(float value){ this->sensAttraction = value; };
    inline void setForceAttraction(float value){ this->forceAttraction = value; };
    inline void setRayonAttraction(float value){ this->rayonAttraction = value; };
    inline void setPosAttraction(float x, float y, float z){ this->posAttraction.set(x,y,z); };
    
    inline void setMagnitudeNoise(float value){ this->magnitudeNoise = value; };


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

    int     numParticles;
    int     textureRes;
    unsigned int comportement;
    
    float vitesseGenerale, maxSpeed;
    
    float forceAttraction, rayonAttraction, sensAttraction;
    ofVec3f posAttraction;
    
    ofVec3f distanceFlocking, magnitudeFlocking;
    
    float magnitudeNoise;

};

#endif
