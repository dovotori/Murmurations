#ifndef EFFET_H
#define EFFET_H

#include "ofMain.h"


class Effet
{
    public:
        Effet();
        virtual ~Effet();
        void setup();
        void begin();
        void end();
        void draw();

        inline void setNoiseInfluence(float value){ this->noiseInfluence = value; };
        inline void setNoiseScale(float value){ this->noiseScale = value; };

        inline float getNoiseInfluence(){ return this->noiseInfluence; };

    protected:
    private:
        ofShader *shaders;
        ofFbo fboPing, fboPong, fboFirst;
        float cpt, noiseInfluence, noiseScale, blur;
        unsigned int passages;
};

#endif // EFFET_H
