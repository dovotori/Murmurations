

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
    void setup(unsigned int nb);
    void update(ofTexture& texNoise);
    void resetPosition(unsigned int mode);
    void resetVelocity();
    inline void drawDebugTexture(){ this->velPingPong.dst->draw(0, 0); };

    inline ofTexture& getPosTexture(){ return this->posPingPong.dst->getTextureReference(); };
    inline ofTexture& getVelTexture(){ return this->velPingPong.dst->getTextureReference(); };
    
    inline void setMaxSpeed(float value){ this->maxSpeed = value; };
    inline void setVitesseGenerale(float value){ this->vitesseGenerale = value; };
    
    inline void setDistanceFlocking(float x, float y, float z){ this->distanceFlocking.set(x, y, z); };
    inline void setRapportForces(float x, float y, float z, float w){ this->rapportForces.set(x, y, z, w); };
    
    inline void setSensAttraction(float value){ this->sensAttraction = value; };
    inline void setForceAttraction(float value){ this->forceAttraction = value; };
    inline void setRayonAttraction(float value){ this->rayonAttraction = value; };
    inline void setPosAttraction(float x, float y, float z){ this->posAttraction.set(x,y,z); };
    
    inline void setMagnitudeNoise(float value){ this->magnitudeNoise = value; };
    inline void setMasse(float value){ this->masse = value; };
    inline void setForceMax(float value){ this->forceMax = value; };
    inline void setRayonPath(float value){ this->rayonPath = value; };
    inline void setPath(unsigned int value){ if(value < this->nbPath){ this->path = value; } else { this->path = 0; } };


protected:
private:
    void setupPosition();
    void setupVelocity();

    void computeGpuPosition();
    void computeGpuVelocity(ofTexture& texNoise);

    ofShader updatePos;
    ofShader updateVel;

    pingPongBuffer posPingPong;
    pingPongBuffer velPingPong;

    int     numParticles;
    int     textureRes;
    
    float vitesseGenerale, maxSpeed;
    
    float forceAttraction, rayonAttraction, sensAttraction;
    ofVec3f posAttraction;
    
    ofVec3f distanceFlocking;
    ofVec4f rapportForces;
    
    float magnitudeNoise, masse, forceMax, rayonPath;
    
    unsigned int path, nbPath;

};

#endif
