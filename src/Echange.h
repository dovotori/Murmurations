#ifndef ECHANGE_H
#define ECHANGE_H

#include "ofMain.h"
#include "ofxOsc.h"

#include "Camera.h"
#include "GpuProcess.h"
#include "Forme.h"
#include "Background.h"

#define PORT 12000
#define NB_VAR_MAX 34

class Echange
{
    public:
        Echange();
        virtual ~Echange();
        void setup();
        void update(Camera *camera, GpuProcess *process, Forme *forme, Background *background);

    protected:
    private:
        ofxOscReceiver receiver;
        float variables[NB_VAR_MAX];
        unsigned int nbVariables;

};

#endif // ECHANGE_H
