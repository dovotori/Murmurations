#ifndef ECHANGE_H
#define ECHANGE_H

#include "ofMain.h"
#include "ofxOsc.h"

#include "Camera.h"
#include "GpuProcess.h"
#include "Forme.h"
#include "Background.h"

#define PORT 12000

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

};

#endif // ECHANGE_H
