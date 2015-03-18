#ifndef ECHANGE_H
#define ECHANGE_H

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxGui.h"

#include "Camera.h"
#include "GpuProcess.h"
#include "Forme.h"
#include "Background.h"
#include "Effet.h"
#include "Ligne.h"


#define PORT 12000

class Echange
{
    public:
        Echange();
        virtual ~Echange();
        void setup();
        void update(Camera *camera, GpuProcess *process, Forme *forme, Background *background, Effet *effet, Ligne *ligne);
        void draw();

        inline void toggleGui(){ this->hideGui = !this->hideGui; };

        void buttonPressed();

    protected:
    private:

        void updateGui(Camera *camera, GpuProcess *process, Forme *forme, Background *background, Effet *effet, Ligne *ligne);
        void updateOsc(Camera *camera, GpuProcess *process, Forme *forme, Background *background, Effet *effet, Ligne *ligne);

        ofxOscReceiver receiver;

        bool hideGui;
        ofxPanel gui;
        ofxFloatSlider masse, forceMax, rayonPath, vitesseGenerale, tailleParticule, noiseMagnitude, distanceLigne, opacityBackground;
        ofxVec3Slider flockingForces, rotation;
        ofxVec4Slider rapportModes;
        ofxColorSlider color;
        ofxToggle sensAttraction;
    	ofxButton reset; bool btnPressed;
    	ofxIntSlider typeBackground, pathShape;
};

#endif // ECHANGE_H
