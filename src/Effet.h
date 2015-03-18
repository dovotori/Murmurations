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
        ofShader shader, shader2;
        ofFbo fbo, fbo2;
        float cpt, noiseInfluence, noiseScale;
};

#endif // EFFET_H
