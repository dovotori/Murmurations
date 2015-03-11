#include "Echange.h"

Echange::Echange()
{
    //ctor
    this->btnPressed = false;
    this->hideGui = true;
}

Echange::~Echange()
{
    //dtor
    this->reset.removeListener(this, &Echange::buttonPressed);
}


void Echange::setup()
{
    this->receiver.setup(PORT);
    
    this->gui.setDefaultHeaderBackgroundColor( ofColor(100, 200, 255) );
    this->gui.setDefaultBorderColor( ofColor(255) );
    this->gui.setDefaultBackgroundColor( ofColor(50, 100, 155) );
    this->gui.setDefaultFillColor( ofColor(100, 200, 255) );
    this->gui.setup();

    this->gui.add( this->rapportModes.setup( "rapportForces", ofVec4f(1.0, 0.0, 0.0, 0.0), ofVec4f(0.0), ofVec4f(1.0) )  );
    this->gui.add( this->masse.setup( "masse", 2.0, 0.1, 10.0 ) );
    this->gui.add( this->forceMax.setup( "forceMax", 0.1, 0.001, 1.0 ) );
    this->gui.add( this->rayonPath.setup( "rayonPath", 0.04, 0.01, 0.1 ) );
    this->gui.add( this->vitesseGenerale.setup( "vitesseGenerale", 0.005, 0.001, 0.06 ) );
    
    this->gui.add( this->flockingForces.setup( "flockingForces", ofVec3f(0.02, 0.5, 1.0), ofVec3f(0.0), ofVec3f(0.1, 1.0, 2.0) ) );
    this->gui.add( this->sensAttraction.setup( "sensAttraction", true) );
    this->gui.add( this->noiseMagnitude.setup( "noiseMagnitude", 2.0, 1.0, 10.0 ) );
     
    this->gui.add( this->tailleParticule.setup( "tailleParticule", 0.01, 0.001, 0.4 ) );
    this->gui.add( this->rotation.setup( "rotation", ofVec3f(0.0), ofVec3f(0.0), ofVec3f(360.0) ) );
    this->gui.add( this->color.setup( "color", ofColor(200,200,255,70.0), ofColor(0,0), ofColor(255,255)) );
    
    this->gui.add( this->zoom.setup( "zoom", 2.0, 0.8, 4.0 ) );
    
    this->reset.addListener(this, &Echange::buttonPressed);
     
    this->gui.add( this->reset.setup( "reset" ) );
    
}


void Echange::update(Camera *camera, GpuProcess *process, Forme *forme, Background *background)
{
    if(this->hideGui)
    {
        this->updateOsc(camera, process, forme, background);
    } else {
        this->updateGui(camera, process, forme, background);
    }
}



void Echange::updateOsc(Camera *camera, GpuProcess *process, Forme *forme, Background *background)
{
    
    // OSC boucle sur chaque message
    // peut avoir plusieurs variables associer à un message
    //m.getArgAsInt32(1);
    
    while(this->receiver.hasWaitingMessages())
    {
        ofxOscMessage m;
        this->receiver.getNextMessage(&m);
        string argumentAdresse = m.getAddress();
        
        ////////////////////////////////////////////////////////////////
        //////////////////////////////// PROCESS /////////////////////////
        ////////////////////////////////////////////////////////////////
        if(argumentAdresse == "/max2P5/VitesseMax")
        {
            cout << "VitesseMax: " << m.getArgAsFloat(0)*0.1 << endl;
            process->setVitesseGenerale(m.getArgAsFloat(0)*0.1);
        }
        else if(argumentAdresse == "/max2P5/flockAmplitudes")
        {
            cout << "forces // X: " << m.getArgAsFloat(0) << " // Y: " << m.getArgAsFloat(1) << " // Z: " << m.getArgAsFloat(2) << endl;
            process->setRapportForces(m.getArgAsFloat(0), m.getArgAsFloat(1), m.getArgAsFloat(2), 0.0);
        }
        
        
        
        
        ////////////////////////////////////////////////////////////////
         ///////////////////////// ATTRACTION ///////////////////////////
         ////////////////////////////////////////////////////////////////
        else if(argumentAdresse == "/max2P5/attractionRayon")
        {
            cout << "attractionRayon: " << m.getArgAsFloat(0) << endl;
            process->setRayonAttraction(m.getArgAsFloat(0));
        }
        else if(argumentAdresse == "/max2P5/attractionForce")
        {
            cout << "attractionForce: " << m.getArgAsFloat(0) << endl;
            process->setForceAttraction(m.getArgAsFloat(0));
        }
        else if(argumentAdresse == "/max2P5/attractionSens")
        {
            cout << "attractionSens: " << (m.getArgAsFloat(0)-0.5)*2.0 << endl;
            process->setSensAttraction((m.getArgAsFloat(0)-0.5)*2.0);
        } // entre -1 et 1
        else if(argumentAdresse == "/max2P5/attractionPosition")
        {
            cout << "attractionPosition // X: " << m.getArgAsFloat(0) << " // Y: " << m.getArgAsFloat(1) << " // Z: " << m.getArgAsFloat(2) << endl;
            process->setPosAttraction(m.getArgAsFloat(0), m.getArgAsFloat(1), m.getArgAsFloat(2));
        }
        
        
        
        ////////////////////////////////////////////////////////////////
        //////////////////////////////////// PATH ////////////////////////
        ////////////////////////////////////////////////////////////////
        else if(argumentAdresse == "/max2P5/pathShape"){ cout << m.getArgAsFloat(0) << endl; } //(int)
        
        
        
        
        ////////////////////////////////////////////////////////////////
        //////////////////////////////////// NOISE ///////////////////////
        ////////////////////////////////////////////////////////////////
        else if(argumentAdresse == "/max2P5/noiseMagnitude")
        {
            cout << "noiseMagnitude: " << m.getArgAsFloat(0) << endl;
            process->setMagnitudeNoise(m.getArgAsFloat(0));
        }
        
        
        
        ////////////////////////////////////////////////////////////////
        ///////////////////////// FLOCKING /////////////////////////////
        ////////////////////////////////////////////////////////////////
        else if(argumentAdresse == "/max2P5/flockForces")
        {
            cout << "flockForces // X: " << m.getArgAsFloat(0)*0.4 << " // Y: " << m.getArgAsFloat(1) << " // Z: " << m.getArgAsFloat(2)*2.0 << endl;
            process->setDistanceFlocking(m.getArgAsFloat(0)*0.4, m.getArgAsFloat(1), m.getArgAsFloat(2)*2.0);
        } //(float entre 0 et 1)
        //if(argumentAdresse == "/max2P5/cohesionForce"){ cout << m.getArgAsFloat(0) << endl; } //(float entre 0 et 1)
        //if(argumentAdresse == "/max2P5/separationForce"){ cout << m.getArgAsFloat(0) << endl; } //(float entre 0 et 1)
        //if(argumentAdresse == "/max2P5/pathPattern"){ cout << m.getArgAsFloat(0) << endl; } //(float entre 0 et 1)
        
        else if(argumentAdresse == "/max2P5/flockMagnitudeCohesion"){ cout << m.getArgAsFloat(0) << endl; } //(float entre 0 et 1)
        else if(argumentAdresse == "/max2P5/flockMasse")
        {
            cout << "flockMasse: " << 1.0+(m.getArgAsFloat(0)*4.0) << endl;
            process->setMasse(1.0+(m.getArgAsFloat(0)*4.0));
        } //(float > 1)
        
        
        
        //////////////////////////////////////////////////////////
        //////////////////////// FORME /////////////////////////////
        //////////////////////////////////////////////////////////
        else if(argumentAdresse == "/max2P5/typeRendu")
        {
            int rendu = m.getArgAsInt32(0); if(rendu > 3){ rendu = 3; }
            cout << "typeRendu: " << rendu << endl;
            forme->setRendu(rendu);
        }//(entier)
        else if(argumentAdresse == "/max2P5/birdColor"){
            cout << "birdColor // R: " << m.getArgAsFloat(0) << " // V: " << m.getArgAsFloat(1) << " // B: " << m.getArgAsFloat(2) << " // A: " << m.getArgAsFloat(3) << endl;
            forme->setCouleur(m.getArgAsFloat(0), m.getArgAsFloat(1), m.getArgAsFloat(2), m.getArgAsFloat(3));
        }//(float entre 0 et 1)
        else if(argumentAdresse == "/max2P5/rotationForme")
        {
            cout << "rotation // X: " << m.getArgAsFloat(0)*360.0 << " // Y: " << m.getArgAsFloat(1)*360.0 << " // Z: " << m.getArgAsFloat(2)*360.0 << endl;
            forme->setRotation(m.getArgAsFloat(0)*360.0, m.getArgAsFloat(1)*360.0, m.getArgAsFloat(2)*360.0);
        }
        
        
        
        //////////////////////////////////////////////////////////
        /////////////////////// BACKGROUND ////////////////////////
        //////////////////////////////////////////////////////////
        else if(argumentAdresse == "/max2P5/backgroundAlpha")
        {
            cout << "backgroundAlpha: " << m.getArgAsFloat(0) << endl;
            background->setAlpha(m.getArgAsFloat(0));
        } //(float entre 0 et 1)
        else if(argumentAdresse == "/max2P5/backgroundImg"){ cout << m.getArgAsFloat(0) << endl; } //(entier)
        else if(argumentAdresse == "/max2P5/noiseIntensity"){ cout << m.getArgAsFloat(0) << endl; forme->setNoiseInfluence(0.5); }
        
        
        
        //////////////////////////////////////////////////////////
        ////////////////////////// SCENE //////////////////////////
        //////////////////////////////////////////////////////////
        else if(argumentAdresse == "/max2P5/zoom")
        {
            cout << "zoom: " << 0.1+(m.getArgAsFloat(0)*10.0) << endl;
            camera->setPosition(0.0, 0.0, 0.1+(m.getArgAsFloat(0)*10.0));
        } //(entier)
        else if(argumentAdresse == "/max2P5/cameraAngle")
        {
            cout << "cameraAngle: " << m.getArgAsFloat(0)*200.0 << endl;
            camera->setAngle(m.getArgAsFloat(0)*200.0);
        } //(float > 0.0)
        
    }
    
}




void Echange::updateGui(Camera *camera, GpuProcess *process, Forme *forme, Background *background)
{
    
    process->setRapportForces(this->rapportModes->x, this->rapportModes->y, this->rapportModes->z, this->rapportModes->w);
    process->setMasse(this->masse);
    process->setForceMax(this->forceMax);
    process->setRayonPath(this->rayonPath);
    process->setVitesseGenerale(this->vitesseGenerale);
    if(this->sensAttraction){ process->setSensAttraction(1.0); }else{ process->setSensAttraction(-1.0); }
    process->setDistanceFlocking(this->flockingForces->x, this->flockingForces->y, this->flockingForces->z);
    process->setMagnitudeNoise(this->noiseMagnitude);
    
    forme->setTaille(this->tailleParticule);
    forme->setRotation(this->rotation->x, this->rotation->y, this->rotation->z);
    ofColor c; c.set(this->color); forme->setCouleur((float)c.r/255.0, (float)c.g/255.0, (float)c.b/255.0, (float)c.a/255.0);
    
    if(this->btnPressed){ process->resetPosition(0); process->resetVelocity(); this->btnPressed = false; }
    
    camera->setPosition(0.0, 0.0, this->zoom);
    
}




void Echange::draw()
{
    if(!this->hideGui){ this->gui.draw(); }
}



void Echange::buttonPressed(){ this->btnPressed = true; }




