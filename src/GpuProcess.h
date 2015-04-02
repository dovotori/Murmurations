

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
    void draw();
    inline void drawDebugTexture(){ this->velPingPong.dst->draw(0, 0); };

    inline ofTexture& getPosTexture(){ return this->posPingPong.dst->getTextureReference(); };
    inline ofTexture& getVelTexture(){ return this->velPingPong.dst->getTextureReference(); };

    inline void setMaxSpeed(float value){ this->maxSpeed = value; };
    inline void setVitesseGenerale(float value){ this->vitesseGenerale = value; };
    inline void setRapportForces(float x, float y, float z, float w){ this->rapportForces.set(x, y, z, w); };

    inline void setDistancesFlocking(float x, float y, float z, float w){ this->distancesFlocking.set(x, y, z, w); };
    inline void setForcesFlocking(float x, float y, float z, float w){ this->forcesFlocking.set(x, y, z, w); };

    inline void setSensAttraction(float value){ this->sensAttraction = value; };
    inline void setForceAttraction(float value){ this->forceAttraction = value; };
    inline void setRayonAttraction(float value){ this->rayonAttraction = value; };
    inline void setPosAttraction(float x, float y, float z){ this->posAttraction.set(x,y,z); };

    inline void setMagnitudeNoise(float value){ this->magnitudeNoise = value; };
    inline void setMasse(float value){ this->masse = value; };
    inline void setFlockingForceMax(float value){ this->forcesMax.x = value; };
    inline void setPathForceMax(float value){ this->forcesMax.y = value; };
    inline void setAttractorForceMax(float value){ this->forcesMax.z = value; };
    inline void setForceMax(float value){ this->forcesMax.w = value; };
    inline void setRayonPath(float value){ this->rayonPath = value; };
    void setPath(unsigned int value);

    inline unsigned int getNbPath(){ return this->nbPath; };

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
    ofVec4f rapportForces;

    float forceAttraction, rayonAttraction, sensAttraction;
    ofVec3f posAttraction;

    ofVec4f distancesFlocking, forcesFlocking, forcesMax;

    float magnitudeNoise, masse, rayonPath;

    unsigned int path, nbPath, pathNbPoints;

};

#endif
