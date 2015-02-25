#include "Echange.h"

Echange::Echange()
{
    //ctor
    this->btnPressed = false;
}

Echange::~Echange()
{
    //dtor
}


void Echange::setup()
{
    this->receiver.setup(PORT);
    this->gui.setup();
    this->gui.add(this->rapportModes.setup( "rapportForces", ofVec4f(1.0, 0.0, 0.0, 0.0), ofVec4f(0.0), ofVec4f(1.0) )  );
    this->gui.add(this->masse.setup( "masse", 2.0, 0.1, 10.0 ) );
    this->gui.add(this->forceMax.setup( "forceMax", 0.1, 0.001, 1.0 ) );
    this->gui.add(this->rayonPath.setup( "rayonPath", 0.04, 0.01, 0.1 ) );
    this->gui.add(this->vitesseGenerale.setup( "vitesseGenerale", 0.005, 0.001, 0.06 ) );
    this->gui.add(this->flockingForces.setup( "flockingForces", ofVec3f(0.1, 0.5, 0.8), ofVec3f(0.0), ofVec3f(1.0) ) );
    
    this->gui.add(this->tailleParticule.setup( "tailleParticule", 0.005, 0.005, 0.04 ) );
    this->gui.add(this->rotation.setup( "rotation", ofVec3f(0.0), ofVec3f(0.0), ofVec3f(360.0) ) );
    this->gui.add(this->color.setup("color", ofColor(100,100,140), ofColor(0,0), ofColor(255,255)));
    this->reset.addListener(this, &Echange::buttonPressed);
    
    this->gui.add(this->reset.setup("reset"));
}


void Echange::update(Camera *camera, GpuProcess *process, Forme *forme, Background *background)
{
    // OSC boucle sur chaque message
    // peut avoir plusieurs variables associer à un message
    //m.getArgAsInt32(1);
    
    while(this->receiver.hasWaitingMessages())
    {
        ofxOscMessage m;
        this->receiver.getNextMessage(&m);
        string argumentAdresse = m.getAddress();
        
        /*//// PROCESS /////*/
        if(argumentAdresse == "/max2P5/vitesseMax"){ cout << m.getArgAsFloat(0) << endl; process->setMaxSpeed(1.0);}
        
        /*//// ATTRACTION /////*/
        if(argumentAdresse == "/max2P5/attractionForce"){ cout << m.getArgAsFloat(0) << endl; process->setForceAttraction(1.0); }
        if(argumentAdresse == "/max2P5/attractionSens"){ cout << m.getArgAsFloat(0) << endl; process->setSensAttraction(1.0); }
        if(argumentAdresse == "/max2P5/attractionPosX"){ cout << m.getArgAsFloat(0) << endl; process->setPosAttraction(0.5, 0.5, 0.5); }
        if(argumentAdresse == "/max2P5/attractionPosY"){ cout << m.getArgAsFloat(0) << endl; }
        if(argumentAdresse == "/max2P5/attractionPosZ"){ cout << m.getArgAsFloat(0) << endl; }
        
        /*//// PATH /////*/
        if(argumentAdresse == "/max2P5/pathShape"){ cout << m.getArgAsFloat(0) << endl; } //(int)
        
        /*//// NOISE /////*/
        if(argumentAdresse == "/max2P5/noiseMagnitude"){ cout << m.getArgAsFloat(0) << endl; process->setMagnitudeNoise(1.0); }
        
        
        /*//// FLOCKING /////*/
        if(argumentAdresse == "/max2P5/flockDistanceSeparation"){ cout << m.getArgAsFloat(0) << endl; process->setDistanceFlocking(0.2, 0.6, 1.0); } //(float entre 0 et 1)
        if(argumentAdresse == "/max2P5/flockingForce"){ cout << m.getArgAsFloat(0) << endl; process->setDistanceFlocking(m.getArgAsFloat(0), m.getArgAsFloat(1), m.getArgAsFloat(2)); } //(float entre 0 et 1)
        //if(argumentAdresse == "/max2P5/cohesionForce"){ cout << m.getArgAsFloat(0) << endl; } //(float entre 0 et 1)
        //if(argumentAdresse == "/max2P5/separationForce"){ cout << m.getArgAsFloat(0) << endl; } //(float entre 0 et 1)
        //if(argumentAdresse == "/max2P5/pathPattern"){ cout << m.getArgAsFloat(0) << endl; } //(float entre 0 et 1)
        
        if(argumentAdresse == "/max2P5/flockMagnitudeCohesion"){ cout << m.getArgAsFloat(0) << endl; } //(float entre 0 et 1)
        if(argumentAdresse == "/max2P5/flockMasse"){ cout << m.getArgAsFloat(0) << endl; } //(float > 1)
        
        /*//// FORME /////*/
        
        if(argumentAdresse == "/max2P5/typeRendu"){ cout << m.getArgAsFloat(0) << endl; forme->setRendu(1); }//(entier)
        if(argumentAdresse == "/max2P5/birdColorR"){ cout << m.getArgAsFloat(0) << endl; forme->setCouleur(1.0, 1.0, 1.0,1.0); }//(float entre 0 et 1)
        if(argumentAdresse == "/max2P5/birdColorV"){ cout << m.getArgAsFloat(0) << endl; }
        if(argumentAdresse == "/max2P5/birdColorB"){ cout << m.getArgAsFloat(0) << endl; }
        if(argumentAdresse == "/max2P5/birdColorA"){ cout << m.getArgAsFloat(0) << endl; }
        if(argumentAdresse == "/max2P5/rotationFormeX"){ cout << m.getArgAsFloat(0) << endl; forme->setRotation(0.0, 0.0, 10.0); }
        if(argumentAdresse == "/max2P5/rotationFormeY"){ cout << m.getArgAsFloat(0) << endl; }
        if(argumentAdresse == "/max2P5/rotationFormeZ"){ cout << m.getArgAsFloat(0) << endl; }
        
        /*//// BACKGROUND /////*/
        if(argumentAdresse == "/max2P5/backgroundAlpha"){ cout << m.getArgAsFloat(0) << endl; background->setAlpha(0.5); } //(float entre 0 et 1)
        if(argumentAdresse == "/max2P5/backgroundImg"){ cout << m.getArgAsFloat(0) << endl; } //(entier)
        if(argumentAdresse == "/max2P5/noiseIntensity"){ cout << m.getArgAsFloat(0) << endl; forme->setNoiseInfluence(0.5); }
        
        /*//// SCENE /////*/
        if(argumentAdresse == "/max2P5/zoom"){ cout << m.getArgAsFloat(0) << endl; camera->setPosition(0.0, 0.0, 100.0); } //(entier)
        if(argumentAdresse == "/max2P5/cameraAngle"){ cout << m.getArgAsFloat(0) << endl; camera->setAngle(40.0); } //(float > 0.0)
        
        
    }
    
    /////////////////////// G/U/I ///////////////////////
    process->setRapportForces(this->rapportModes->x, this->rapportModes->y, this->rapportModes->z, this->rapportModes->w);
    process->setMasse(this->masse);
    process->setForceMax(this->forceMax);
    process->setRayonPath(this->rayonPath);
    process->setVitesseGenerale(this->vitesseGenerale);
    process->setDistanceFlocking(this->flockingForces->x, this->flockingForces->y, this->flockingForces->z);
    
    forme->setTaille(this->tailleParticule);
    forme->setRotation(this->rotation->x, this->rotation->y, this->rotation->z);
    ofColor c; c.set(this->color); forme->setCouleur((float)c.r/255.0, (float)c.g/255.0, (float)c.b/255.0, (float)c.a/255.0);
    
    if(this->btnPressed){ process->resetPosition(0); process->resetVelocity(); this->btnPressed = false; }
}


void Echange::draw()
{
    this->gui.draw();
}



void Echange::buttonPressed(){ this->btnPressed = true; }




