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
    this->gui.add( this->vitesseGenerale.setup( "vitesseGenerale", 0.005, 0.001, 0.06 ) );
    this->gui.add( this->tailleParticule.setup( "tailleParticule", 0.01, 0.001, 0.1 ) );
    this->gui.add( this->distanceLigne.setup( "distanceLigne", 0.05, 0.001, 0.1 ) );
    this->gui.add( this->rotation.setup( "rotation", ofVec3f(0.0, 0.0, 2.0), ofVec3f(-2.0), ofVec3f(2.0) ) );
    this->gui.add( this->color.setup( "color", ofColor(255,255,255,255.0), ofColor(0,0), ofColor(255,255)) );
    this->gui.add( this->typeBackground.setup("typeBackground", 0, 0, 2));
    this->gui.add( this->opacityBackground.setup( "opacityBackground", 0.5, 0.0, 1.0 ) );

    this->gui.add( this->flockingForces.setup( "flockingForces", ofVec3f(0.06, 0.5, 1.0), ofVec3f(0.0), ofVec3f(0.1, 1.0, 2.0) ) );
    this->gui.add( this->sensAttraction.setup( "sensAttraction", true) );
    this->gui.add( this->rayonPath.setup( "rayonPath", 0.04, 0.001, 0.4 ) );
    this->gui.add( this->pathShape.setup("pathShape", 0, 0, 1));
    this->gui.add( this->noiseMagnitude.setup( "noiseMagnitude", 2.0, 1.0, 10.0 ) );

    this->reset.addListener(this, &Echange::buttonPressed);

    this->gui.add( this->reset.setup( "reset" ) );

}


void Echange::update(Camera *camera, GpuProcess *process, Forme *forme, Background *background, Effet *effet, Ligne *ligne)
{
    if(this->hideGui)
    {
        this->updateOsc(camera, process, forme, background, effet, ligne);
    } else {
        this->updateGui(camera, process, forme, background, effet, ligne);
    }
}



void Echange::updateOsc(Camera *camera, GpuProcess *process, Forme *forme, Background *background, Effet *effet, Ligne *ligne)
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
        //////////////////////////////// GENERAL /////////////////////////
        ////////////////////////////////////////////////////////////////
        if(argumentAdresse == "/max2P5/speedMax")
        {
            cout << "speedMax: " << m.getArgAsFloat(0)*0.1 << endl;
            process->setVitesseGenerale(m.getArgAsFloat(0)*0.1);
        }
        else if(argumentAdresse == "/max2P5/forceRatio") // FLOCK / PATH / NOISE / ATTRACTOR
        {
            cout << "forceRatio // Flock: " << m.getArgAsFloat(0) << " // Path: " << m.getArgAsFloat(1) << " // Noise: " << m.getArgAsFloat(2) << " // Attractor: " << m.getArgAsFloat(3) << endl;
            process->setRapportForces(m.getArgAsFloat(0), m.getArgAsFloat(1), m.getArgAsFloat(2), m.getArgAsFloat(3));
        }
        else if(argumentAdresse == "/max2P5/birdMass")
        {
            cout << "flockMasse: " << 1.0+(m.getArgAsFloat(0)*4.0) << endl;
            process->setMasse(1.0+(m.getArgAsFloat(0)*4.0));
        } //(float > 1)
        else if(argumentAdresse == "/max2P5/forceMax")
        {
            cout << "forceMax: " << 1.0+(m.getArgAsFloat(0)*4.0) << endl;
            process->setForceMax(m.getArgAsFloat(0));
        } //(float > 1)
        else if(argumentAdresse == "/max2P5/birdSize")
        {
            cout << "birdSize: " << 0.001+(m.getArgAsFloat(0)*0.08) << endl;
            forme->setTaille(0.001+(m.getArgAsFloat(0)*0.08));
        } //(float > 1)
        else if(argumentAdresse == "/max2P5/cameraZoom")
        {
            cout << "cameraZoom: " << (m.getArgAsFloat(0)-0.5)*20.0 << endl;
            camera->setZoomRotation((m.getArgAsFloat(0)-0.5)*20.0);
        } //(entier)
        else if(argumentAdresse == "/max2P5/cameraAngle")
        {
            cout << "cameraAngle: " << m.getArgAsFloat(0)*200.0 << endl;
            camera->setAngle(m.getArgAsFloat(0)*200.0);
        } //(float > 0.0)
        else if(argumentAdresse == "/max2P5/birdShape")
        {
            int rendu = m.getArgAsInt32(0); if(rendu > forme->getNbRendu()-1){ rendu = 0; }
            cout << "birdShape: " << rendu << endl;
            forme->setRendu(rendu);
        }//(entier)
        else if(argumentAdresse == "/max2P5/birdColor"){
            cout << "birdColor // R: " << m.getArgAsFloat(0) << " // V: " << m.getArgAsFloat(1) << " // B: " << m.getArgAsFloat(2) << " // A: " << m.getArgAsFloat(3) << endl;
            forme->setCouleur(m.getArgAsFloat(0), m.getArgAsFloat(1), m.getArgAsFloat(2), m.getArgAsFloat(3));
        }//(float entre 0 et 1)
        else if(argumentAdresse == "/max2P5/cameraPosition")
        {
            cout << "cameraPosition // X: " << m.getArgAsFloat(0)*360.0 << " // Y: " << m.getArgAsFloat(1)*360.0 << endl;
            //forme->setRotation(m.getArgAsFloat(0)*360.0, m.getArgAsFloat(1)*360.0, m.getArgAsFloat(2)*360.0);
            camera->setAnglesRotation(m.getArgAsFloat(0)*360.0, m.getArgAsFloat(1)*360.0);
        }
        else if(argumentAdresse == "/max2P5/space")
        {
            cout << "space // X: " << m.getArgAsFloat(0) << " // Y: " << m.getArgAsFloat(1) << " // Z: " << m.getArgAsFloat(2) << endl;
            process->setSpaceSize(m.getArgAsFloat(0), m.getArgAsFloat(1), m.getArgAsFloat(2));
        }





        ////////////////////////////////////////////////////////////////
         ///////////////////////// ATTRACTION ///////////////////////////
         ////////////////////////////////////////////////////////////////
        else if(argumentAdresse == "/max2P5/attractionRadius")
        {
            cout << "attractionRayon: " << m.getArgAsFloat(0) << endl;
            process->setRayonAttraction(m.getArgAsFloat(0));
        }
        else if(argumentAdresse == "/max2P5/attractionForce")
        {
            cout << "attractionForce: " << m.getArgAsFloat(0) << endl;
            process->setForceAttraction(m.getArgAsFloat(0));
        }
        else if(argumentAdresse == "/max2P5/attractionWay")
        {
            cout << "attractionSens: " << (m.getArgAsFloat(0)-0.5) * 2.0 << endl;
            process->setSensAttraction((m.getArgAsFloat(0)-0.5) * 2.0);
        } // entre -1 et 1
        else if(argumentAdresse == "/max2P5/attractionPosition")
        {
            cout << "attractionPosition // X: " << m.getArgAsFloat(0) << " // Y: " << m.getArgAsFloat(1) << " // Z: " << m.getArgAsFloat(2) << endl;
            process->setPosAttraction(m.getArgAsFloat(0), m.getArgAsFloat(1), m.getArgAsFloat(2));
        }
        else if(argumentAdresse == "/max2P5/attractorForceMax")
        {
            cout << "attractorForceMax: " << m.getArgAsFloat(0) << endl;
            process->setAttractorForceMax(m.getArgAsFloat(0));
        }



        ////////////////////////////////////////////////////////////////
        //////////////////////////////////// PATH ////////////////////////
        ////////////////////////////////////////////////////////////////
        else if(argumentAdresse == "/max2P5/pathShape")
        {
            int shape = m.getArgAsInt32(0); if(shape > process->getNbPath()-1){ shape = process->getNbPath()-1; } if(shape < 0){ shape = 0; }
            cout << "pathShape: " << shape << endl;
            process->setPath(shape);
        } //(int)
        else if(argumentAdresse == "/max2P5/pathRadius")
        {
            cout << "pathRadius: " << m.getArgAsFloat(0)*0.2 << endl;
            process->setRayonPath(m.getArgAsFloat(0)*0.2);
        }
        else if(argumentAdresse == "/max2P5/pathForceMax")
        {
            cout << "pathForceMax: " << m.getArgAsFloat(0) << endl;
            process->setPathForceMax(m.getArgAsFloat(0));
        }




        ////////////////////////////////////////////////////////////////
        //////////////////////////////////// NOISE ///////////////////////
        ////////////////////////////////////////////////////////////////
        else if(argumentAdresse == "/max2P5/noiseMagnitude")
        {
            cout << "noiseMagnitude: " << m.getArgAsFloat(0) << endl;
            process->setMagnitudeNoise(m.getArgAsFloat(0));
        }
        else if(argumentAdresse == "/max2P5/noiseDirection")
        {
            cout << "noiseDirection // X: " << (m.getArgAsFloat(0)-0.5)*2.0 << " // Y: " << (m.getArgAsFloat(1)-0.5)*2.0 << " // Z: " << (m.getArgAsFloat(2)-0.5)*2.0 << endl;
            process->setNoiseDirection((m.getArgAsFloat(0)-0.5)*2.0, (m.getArgAsFloat(1)-0.5)*2.0, (m.getArgAsFloat(2)-0.5)*2.0);
        }


        ////////////////////////////////////////////////////////////////
        ///////////////////////// FLOCKING /////////////////////////////
        ////////////////////////////////////////////////////////////////
        else if(argumentAdresse == "/max2P5/flockForces")
        {
            cout << "flockForces // X: " << m.getArgAsFloat(0) << " // Y: " << m.getArgAsFloat(1)*0.5 << " // Z: " << m.getArgAsFloat(2)*0.2 << " // A: " << m.getArgAsFloat(3)*4.0 << endl;
            process->setForcesFlocking(m.getArgAsFloat(0), m.getArgAsFloat(1)*0.5, m.getArgAsFloat(2)*0.2, m.getArgAsFloat(3)*4.0);
        } //(float entre 0 et 1)
        else if(argumentAdresse == "/max2P5/flockDistances")
        {
            cout << "flockDistances // X: " << m.getArgAsFloat(0)*0.4 << " // Y: " << m.getArgAsFloat(1) << " // Z: " << m.getArgAsFloat(2)*2.0 << " // A: " << m.getArgAsFloat(3)*0.5 << endl;
            process->setDistancesFlocking(m.getArgAsFloat(0)*0.4, m.getArgAsFloat(1), m.getArgAsFloat(2)*2.0, m.getArgAsFloat(3)*0.5);
        } //(float entre 0 et 1)
        else if(argumentAdresse == "/max2P5/flockingForceMax")
        {
            cout << "flockingForceMax: " << m.getArgAsFloat(0) << endl;
            process->setFlockingForceMax(m.getArgAsFloat(0));
        }




        //////////////////////////////////////////////////////////
        /////////////////////// BACKGROUND ////////////////////////
        //////////////////////////////////////////////////////////
        else if(argumentAdresse == "/max2P5/backgroundAlpha")
        {
            cout << "backgroundAlpha: " << m.getArgAsFloat(0) << endl;
            background->setAlpha(m.getArgAsFloat(0));
        } //(float entre 0 et 1)
        else if(argumentAdresse == "/max2P5/backgroundImg")
        {
            int numImg = m.getArgAsInt32(0);
            if(numImg < 0 || numImg > 2){ numImg = 0; } else { background->setImage(numImg); }
            cout << "backgroundImg: " << numImg << endl;
        } //(entier)
        else if(argumentAdresse == "/max2P5/backgroundNoise")
        {
            cout << "backgroundNoise: " << m.getArgAsFloat(0) << endl;
            background->setNoiseInfluence(m.getArgAsFloat(0));
            background->setNoiseScale(m.getArgAsFloat(0));
        }



    }

}




void Echange::updateGui(Camera *camera, GpuProcess *process, Forme *forme, Background *background, Effet *effet, Ligne *ligne)
{

    process->setRapportForces(this->rapportModes->x, this->rapportModes->y, this->rapportModes->z, this->rapportModes->w);
    process->setMasse(this->masse);
    process->setForceMax(this->forceMax);
    process->setRayonPath(this->rayonPath);
    process->setVitesseGenerale(this->vitesseGenerale);
    process->setPath(this->pathShape);
    if(this->sensAttraction){ process->setSensAttraction(1.0); } else { process->setSensAttraction(-1.0); }
    process->setDistancesFlocking(this->flockingForces->x, this->flockingForces->y, this->flockingForces->z, 0.0);
    process->setMagnitudeNoise(this->noiseMagnitude);
    ligne->setDistance(this->distanceLigne);
    background->setImage(this->typeBackground);
    background->setAlpha(this->opacityBackground);

    forme->setTaille(this->tailleParticule);
    forme->setRotation(this->rotation->x, this->rotation->y, this->rotation->z);
    ofColor c; c.set(this->color); forme->setCouleur((float)c.r/255.0, (float)c.g/255.0, (float)c.b/255.0, (float)c.a/255.0);

    if(this->btnPressed){ process->resetPosition(0); process->resetVelocity(); this->btnPressed = false; }

    //camera->rotation(ofVec2f(this->rotation->x, this->rotation->y), this->rotation->z);

}




void Echange::draw()
{
    if(!this->hideGui){ this->gui.draw(); }
}



void Echange::buttonPressed(){ this->btnPressed = true; }




