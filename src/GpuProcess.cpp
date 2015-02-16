

#include "GpuProcess.h"



GpuProcess::GpuProcess()
{
    //ctor
}

GpuProcess::~GpuProcess()
{
    //dtor

}




void GpuProcess::setup(unsigned int nb)
{
    this->vitesseGenerale = 0.005;
    this->numParticles = nb;
    this->comportement = 0;

    this->textureRes = (int)sqrt((float)this->numParticles);      // Definir la resolution de la texture en fonction du nombre de particules
    this->numParticles = this->textureRes * this->textureRes;     // Redefinir le nombre de particules (pas de gachis)

    cout << "nombre de particules: " << this->numParticles << endl;
    cout << "resolution de la texture: " << this->textureRes << endl;

    this->setupPosition();
    this->setupVelocity();

}



void GpuProcess::setupPosition()
{
    // SHADER
    this->updatePos.load("shader/basic.vert", "shader/posUpdate.frag");// shader for updating the texture that store the particles position on RG channels

    // CHARGER DANS UNE FBO TEXTURE
    this->posPingPong.allocate(this->textureRes, this->textureRes, GL_RGB32F);
    this->resetPosition();
}





void GpuProcess::setupVelocity()
{
    // SHADER
    this->updateVel = new ofShader[4];
    this->updateVel[0].load("shader/basic.vert","shader/velUpdate_flock.frag");
    this->updateVel[1].load("shader/basic.vert","shader/velUpdate_noise.frag");
    this->updateVel[2].load("shader/basic.vert","shader/velUpdate_attractor.frag");
    this->updateVel[3].load("shader/basic.vert","shader/velUpdate_path.frag");

    // COOR
    float * vel = new float[this->numParticles*3];
    for (int i = 0; i < this->numParticles; i++){
        vel[i*3 + 0] = ofRandom(-1.0, 1.0);
        vel[i*3 + 1] = ofRandom(-1.0, 1.0);
        vel[i*3 + 2] = ofRandom(-1.0, 1.0);
    }
    //  CHARGER DANS UNE FBO TEXTURE
    this->velPingPong.allocate(this->textureRes, this->textureRes,GL_RGB32F);
    this->velPingPong.src->getTextureReference().loadData(vel, this->textureRes, this->textureRes, GL_RGB);
    this->velPingPong.dst->getTextureReference().loadData(vel, this->textureRes, this->textureRes, GL_RGB);
    delete [] vel;
}




/*/////////////// RESET /////////////// */

void GpuProcess::resetPosition()
{
    // COOR
    float * pos = new float[this->numParticles*3];
    for (int x = 0; x < this->textureRes; x++){
        for (int y = 0; y < this->textureRes; y++){
            int i = this->textureRes * y + x;

            pos[i*3 + 0] = 0.5; //ofMap(x, 0, this->textureRes, 0, 1); //ofRandom(0.0, 1.0); // couleur est entre 0 et 1
            pos[i*3 + 1] = 0.5; //ofMap(y, 0, this->textureRes, 0, 1); //ofRandom(0.0, 1.0);
            pos[i*3 + 2] = 0.5; //ofRandom(0.0, 1.0);
        }
    }


    /*
    //// CUBE ////
    int cote = floor( pow( this->numParticles, (1.0/3.0) ) );
    cout << cote << endl;
    int cpt = 0;

    for (int z = 0; z < cote; z++) {
        for (int y = 0; y < cote; y++) {
            for (int x = 0; x < cote; x++) {

                pos[cpt*3 + 0] = ofMap(x, 0, cote, 0, 1);
                pos[cpt*3 + 1] = ofMap(y, 0, cote, 0, 1);
                pos[cpt*3 + 2] = ofMap(z, 0, cote, 0, 1);
                cpt++;
            }
        }
    }
    */

    this->posPingPong.src->getTextureReference().loadData(pos, this->textureRes, this->textureRes, GL_RGB);
    this->posPingPong.dst->getTextureReference().loadData(pos, this->textureRes, this->textureRes, GL_RGB);
    delete [] pos;
}




/*/////////////// UPDATE /////////////// */


void GpuProcess::update()
{

    this->computeGpuVelocity();
    this->computeGpuPosition();

}



void GpuProcess::computeGpuVelocity()
{
    this->velPingPong.dst->begin();

        ofClear(0);

        this->updateVel[this->comportement].begin();

            this->updateVel[this->comportement].setUniformTexture("prevVelData", this->velPingPong.src->getTextureReference(), 0);   // passing the previus velocity information
            this->updateVel[this->comportement].setUniformTexture("posData", this->posPingPong.src->getTextureReference(), 1);  // passing the position information
            this->updateVel[this->comportement].setUniform1i("resolution", (int)this->textureRes);
            this->updateVel[this->comportement].setUniform1f("distanceSeparation", 0.2);
            this->updateVel[this->comportement].setUniform1f("distanceAlignement", 0.6);
            this->updateVel[this->comportement].setUniform1f("distanceCohesion", 1.0);

            this->velPingPong.src->draw(0, 0); // draw the source velocity texture to be updated

        this->updateVel[this->comportement].end();

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
            this->updatePos.setUniform1f("timestep", this->vitesseGenerale );
            this->updatePos.setUniform1i("resolution", (int)this->textureRes);
            this->posPingPong.src->draw(0, 0); // draw fbo source dans le fbo destination

        this->updatePos.end();

    this->posPingPong.dst->end();

    this->posPingPong.swap();
}






