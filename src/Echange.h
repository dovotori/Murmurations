#ifndef ECHANGE_H
#define ECHANGE_H

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxGui.h"

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
        void draw();
    
        void buttonPressed();

    protected:
    private:
        ofxOscReceiver receiver;
    
        ofxPanel gui;
        ofxFloatSlider masse, forceMax, rayonPath, vitesseGenerale, tailleParticule;
        ofxVec3Slider flockingForces, rotation;
        ofxVec4Slider rapportModes;
        ofxColorSlider color;
    	ofxButton reset; bool btnPressed;
};

#endif // ECHANGE_H
