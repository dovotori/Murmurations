

#include "GpuProcess.h"



GpuProcess::GpuProcess()
{
    //ctor
    this->vitesseGenerale = 0.005;
    this->rapportForces.set(1.0, 0.0, 0.0, 0.0);

    this->forceAttraction = 1.0;
    this->rayonAttraction = 0.5;
    this->sensAttraction = 1.0;
    this->posAttraction.set(0.5, 0.5, 0.5);

    this->distancesFlocking.set(0.02, 0.1, 0.2);
    this->forcesFlocking.set(1.0, 0.6, 0.4);

    this->magnitudeNoise = 1.0;
    this->masse = 4.0;
    this->forceMax = 0.1;
    this->rayonPath = 0.04;

    this->path = 0;
    this->nbPath = 2;
}

GpuProcess::~GpuProcess()
{
    //dtor

}




void GpuProcess::setup(unsigned int nb)
{
    this->textureRes = nb;
    this->numParticles = this->textureRes * this->textureRes;

    this->setupPosition();
    this->setupVelocity();

    // envoi des variables contantes
    this->updatePos.begin(); this->updatePos.setUniform1i("resolution", (int)this->textureRes); this->updatePos.end();
    this->updateVel.begin(); this->updateVel.setUniform1i("resolution", (int)this->textureRes); this->updateVel.end();
}



void GpuProcess::setupPosition()
{
    // SHADER
    this->updatePos.load("shader/texFbo.vert", "shader/posUpdate.frag");// shader for updating the texture that store the particles position on RG channels

    // CHARGER DANS UNE FBO TEXTURE
    this->posPingPong.allocate(this->textureRes, this->textureRes, GL_RGB32F);
    this->resetPosition(0);
}





void GpuProcess::setupVelocity()
{

    this->updateVel.load("shader/texFbo.vert","shader/velUpdate.frag");
    this->velPingPong.allocate(this->textureRes, this->textureRes, GL_RGB32F);
    this->resetVelocity();
}




/*/////////////// RESET /////////////// */

void GpuProcess::resetPosition(unsigned int mode)
{

    float * pos = new float[this->numParticles*3];

    switch(mode)
    {
        case 0: /// CENTRE ///
            for (int y = 0; y < this->textureRes; y++)
            {
                for (int x = 0; x < this->textureRes; x++)
                {
                    int i = this->textureRes * y + x;
                    pos[i*3 + 0] = 0.5; // est entre 0 et 1
                    pos[i*3 + 1] = 0.5;
                    pos[i*3 + 2] = 0.5;
                }
            }
            break;

        case 1: /// GRID 2D ///
            for (int y = 0; y < this->textureRes; y++)
            {
                for (int x = 0; x < this->textureRes; x++)
                {
                    int i = this->textureRes * y + x;
                    pos[i*3 + 0] = (float)x/(float)this->textureRes;
                    pos[i*3 + 1] = (float)y/(float)this->textureRes;
                    pos[i*3 + 2] = 0.5;
                }
            }
            break;


        case 2: //// CUBE ////
            int cote = floor( pow( this->numParticles, (1.0/3.0) ) );
            int cpt = 0;

            for (int z = 0; z < cote; z++) {
                for (int y = 0; y < cote; y++) {
                    for (int x = 0; x < cote; x++) {

                        pos[cpt*3 + 0] = ofMap(x, 0, cote-1, 0, 1);
                        pos[cpt*3 + 1] = ofMap(y, 0, cote-1, 0, 1);
                        pos[cpt*3 + 2] = ofMap(z, 0, cote-1, 0, 1);
                        cpt++;
                    }
                }
            }
            break;
    }

    this->posPingPong.src->getTextureReference().loadData(pos, this->textureRes, this->textureRes, GL_RGB);
    this->posPingPong.dst->getTextureReference().loadData(pos, this->textureRes, this->textureRes, GL_RGB);
    delete [] pos;
}



void GpuProcess::resetVelocity()
{
    // COOR
    float * vel = new float[this->numParticles*3];
    for (int i = 0; i < this->numParticles; i++){
        vel[i*3 + 0] = ofRandom(-1.0, 1.0);
        vel[i*3 + 1] = ofRandom(-1.0, 1.0);
        vel[i*3 + 2] = 0.0;//ofRandom(-1.0, 1.0);
    }
    this->velPingPong.src->getTextureReference().loadData(vel, this->textureRes, this->textureRes, GL_RGB);
    this->velPingPong.dst->getTextureReference().loadData(vel, this->textureRes, this->textureRes, GL_RGB);
    delete [] vel;
}


/*/////////////// UPDATE /////////////// */


void GpuProcess::update(ofTexture& texNoise)
{
    this->computeGpuVelocity(texNoise);
    this->computeGpuPosition();
}



void GpuProcess::computeGpuVelocity(ofTexture& texNoise)
{
    this->velPingPong.dst->begin();

        ofClear(0);

        this->updateVel.begin();

            this->updateVel.setUniformTexture("prevVelData", this->velPingPong.src->getTextureReference(), 0);   // passing the previus velocity information
            this->updateVel.setUniformTexture("posData", this->posPingPong.src->getTextureReference(), 1);  // passing the position information
            this->updateVel.setUniform4fv("rapportForces", this->rapportForces.getPtr());
            this->updateVel.setUniform1f("masse", this->masse);
            this->updateVel.setUniform1f("forceMax", this->forceMax);
            // flock
            this->updateVel.setUniform3fv("flockDistance", this->distancesFlocking.getPtr());
            this->updateVel.setUniform3fv("flockAmplitude", this->forcesFlocking.getPtr());
            // noise
            this->updateVel.setUniformTexture("texNoise", texNoise, 2);
            this->updateVel.setUniform1f("noiseMagnitude", this->magnitudeNoise);
            // attractor
            this->updateVel.setUniform1f("ramp", this->sensAttraction);
            this->updateVel.setUniform1f("length", this->forceAttraction);
            this->updateVel.setUniform1f("radious", this->rayonAttraction);
            this->updateVel.setUniform3fv("positionAttractor", this->posAttraction.getPtr());
            // path
            this->updateVel.setUniform1f("rayonPath", this->rayonPath);
            this->updateVel.setUniform1i("path", this->path);

            this->velPingPong.src->draw(0, 0); // draw the source velocity texture to be updated

        this->updateVel.end();

    this->velPingPong.dst->end();

    this->velPingPong.swap();
}





void GpuProcess::computeGpuPosition()
{

    this->posPingPong.dst->begin(); // fbo

        ofClear(0);

        this->updatePos.begin(); // shader

            this->updatePos.setUniformTexture("prevPosData", this->posPingPong.src->getTextureReference(), 0); // Précendentes positions
            this->updatePos.setUniformTexture("velData", this->velPingPong.src->getTextureReference(), 1);  // Vitesses
            this->updatePos.setUniform1f("vitesseGenerale", this->vitesseGenerale );
            this->posPingPong.src->draw(0, 0); // draw fbo source dans le fbo destination

        this->updatePos.end();

    this->posPingPong.dst->end();

    this->posPingPong.swap();

}



void GpuProcess::draw()
{
    this->posPingPong.src->draw(580, 0, 100, 100);
    this->velPingPong.src->draw(700, 0, 100, 100);
}
