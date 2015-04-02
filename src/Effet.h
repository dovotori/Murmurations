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


    protected:
    private:
        ofShader *shaders;
        ofFbo fboPing, fboPong, fboFirst;
        float blur;
        unsigned int passages;
};

#endif // EFFET_H
