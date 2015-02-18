#include "Echange.h"

Echange::Echange()
{
    //ctor
}

Echange::~Echange()
{
    //dtor
}


void Echange::setup()
{
    this->receiver.setup(PORT);
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
        
        if(argumentAdresse == "/max2P5/comportement"){ cout << m.getArgAsFloat(0) << endl; process->setComportement(0); }
        if(argumentAdresse == "/max2P5/vitesseMax"){ cout << m.getArgAsFloat(0) << endl; process->setMaxSpeed(1.0);}
        
        if(argumentAdresse == "/max2P5/attractionForce"){ cout << m.getArgAsFloat(0) << endl; process->setForceAttraction(1.0); }
        if(argumentAdresse == "/max2P5/attractionSens"){ cout << m.getArgAsFloat(0) << endl; process->setSensAttraction(1.0); }
        if(argumentAdresse == "/max2P5/attractionPosX"){ cout << m.getArgAsFloat(0) << endl; process->setPosAttraction(0.5, 0.5, 0.5); }
        if(argumentAdresse == "/max2P5/attractionPosY"){ cout << m.getArgAsFloat(0) << endl; }
        if(argumentAdresse == "/max2P5/attractionPosZ"){ cout << m.getArgAsFloat(0) << endl; }
        
        if(argumentAdresse == "/max2P5/pathShape"){ cout << m.getArgAsFloat(0) << endl; } //(int)
        
        if(argumentAdresse == "/max2P5/noiseMagnitude"){ cout << m.getArgAsFloat(0) << endl; process->setMagnitudeNoise(1.0); }
        
        if(argumentAdresse == "/max2P5/flockDistanceSeparation"){ cout << m.getArgAsFloat(0) << endl; process->setDistanceFlocking(0.2, 0.6, 1.0); } //(float entre 0 et 1)
        if(argumentAdresse == "/max2P5/flockDistanceAlignement"){ cout << m.getArgAsFloat(0) << endl; } //(float entre 0 et 1)
        if(argumentAdresse == "/max2P5/flockDistanceCohesion"){ cout << m.getArgAsFloat(0) << endl; } //(float entre 0 et 1)
        if(argumentAdresse == "/max2P5/flockMagnitudeSeparation"){ cout << m.getArgAsFloat(0) << endl; } //(float entre 0 et 1)
        if(argumentAdresse == "/max2P5/flockMagnitudeAlignement"){ cout << m.getArgAsFloat(0) << endl; } //(float entre 0 et 1)
        if(argumentAdresse == "/max2P5/flockMagnitudeCohesion"){ cout << m.getArgAsFloat(0) << endl; } //(float entre 0 et 1)
        if(argumentAdresse == "/max2P5/flockMasse"){ cout << m.getArgAsFloat(0) << endl; } //(float > 1)
        
        if(argumentAdresse == "/max2P5/tailleEspaceX"){ cout << m.getArgAsFloat(0) << endl; forme->setEspace(40.0, 40.0, 40.0); } //(float entre 0 et 1000)
        if(argumentAdresse == "/max2P5/tailleEspaceY"){ cout << m.getArgAsFloat(0) << endl; } //(float entre 0 et 1000)
        if(argumentAdresse == "/max2P5/tailleEspaceZ"){ cout << m.getArgAsFloat(0) << endl; } //(float entre 0 et 1000)
        
        if(argumentAdresse == "/max2P5/typeRendu"){ cout << m.getArgAsFloat(0) << endl; forme->setRendu(1); }//(entier)
        if(argumentAdresse == "/max2P5/birdColorR"){ cout << m.getArgAsFloat(0) << endl; forme->setCouleur(1.0, 0.4, 0.6); }//(float entre 0 et 1)
        if(argumentAdresse == "/max2P5/birdColorV"){ cout << m.getArgAsFloat(0) << endl; }
        if(argumentAdresse == "/max2P5/birdColorB"){ cout << m.getArgAsFloat(0) << endl; }
        if(argumentAdresse == "/max2P5/birdColorA"){ cout << m.getArgAsFloat(0) << endl; }
        
        if(argumentAdresse == "/max2P5/backgroundAlpha"){ cout << m.getArgAsFloat(0) << endl; background->setAlpha(0.5); } //(float entre 0 et 1)
        if(argumentAdresse == "/max2P5/backgroundImg"){ cout << m.getArgAsFloat(0) << endl; } //(entier)
        
        if(argumentAdresse == "/max2P5/rotationFormeX"){ cout << m.getArgAsFloat(0) << endl; forme->setRotation(0.0, 0.0, 10.0); }
        if(argumentAdresse == "/max2P5/rotationFormeY"){ cout << m.getArgAsFloat(0) << endl; }
        if(argumentAdresse == "/max2P5/rotationFormeZ"){ cout << m.getArgAsFloat(0) << endl; }
        if(argumentAdresse == "/max2P5/zoom"){ cout << m.getArgAsFloat(0) << endl; camera->setPosition(0.0, 0.0, 100.0); } //(entier)
        if(argumentAdresse == "/max2P5/cameraAngle"){ cout << m.getArgAsFloat(0) << endl; camera->setAngle(40.0); } //(float > 0.0)
        
        if(argumentAdresse == "/max2P5/noiseIntensity"){ cout << m.getArgAsFloat(0) << endl; forme->setNoiseInfluence(0.5); }
    }
    
    
    
    
    
    
    
    
    
}







