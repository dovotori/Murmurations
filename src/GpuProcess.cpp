

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
    this->particleSize = 1.0f;
    this->timeStep = 0.005f;
    this->numParticles = nb;
    
    this->width = ofGetWindowWidth();
    this->height = ofGetWindowHeight();

    this->textureRes = (int)sqrt((float)this->numParticles);      // Definir la resolution de la texture en fonction du nombre de particules
    this->numParticles = this->textureRes * this->textureRes;     // Redefinir le nombre de particules (pas de gachis)
    cout << "nombre de particules: " << this->numParticles << endl;
    cout << "resolution de la texture: " << this->textureRes << endl;
    
    this->setupPosition();
    this->setupVelocity();
    this->setupRender();
    
    
    this->cpt = 0.0;
    this->model.makeIdentityMatrix();
    
    
}



void GpuProcess::setupPosition()
{
    // SHADER
    this->updatePos.load("shader/basic.vert", "shader/posUpdate.frag");// shader for updating the texture that store the particles position on RG channels

    // COOR
    float * pos = new float[this->numParticles*3];
    for (int x = 0; x < this->textureRes; x++){
        for (int y = 0; y < this->textureRes; y++){
            int i = this->textureRes * y + x;
            
            pos[i*3 + 0] = 0.5;//ofRandom(0.0, 1.0); // couleur est entre 0 et 1
            pos[i*3 + 1] = 0.5;//ofRandom(0.0, 1.0);
            pos[i*3 + 2] = 0.5;//ofRandom(0.0, 1.0);
        }
    }
    // CHARGER DANS UNE FBO TEXTURE
    this->posPingPong.allocate(this->textureRes, this->textureRes, GL_RGB32F);
    this->posPingPong.src->getTextureReference().loadData(pos, this->textureRes, this->textureRes, GL_RGB);
    this->posPingPong.dst->getTextureReference().loadData(pos, this->textureRes, this->textureRes, GL_RGB);
    delete [] pos;
}





void GpuProcess::setupVelocity()
{
    // SHADER
    this->updateVel.load("shader/basic.vert","shader/velUpdate.frag"); // shader for updating the texture that store the particles velocity on RG channels

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




void GpuProcess::setupRender()
{
    // SHADER
    //this->updateRender.setGeometryInputType(GL_POINTS);
    //this->updateRender.setGeometryOutputType(GL_TRIANGLE_STRIP);
    //this->updateRender.setGeometryOutputCount(6);
    this->updateRender.load("shader/render.vert", "shader/render.frag", "shader/render.geom");
    
    // CHARGER FBO
    this->renderFBO.allocate(this->width, this->height, GL_RGB32F);
    this->renderFBO.begin();
        ofClear(0, 0, 0, 255);
    this->renderFBO.end();
    
    // CREER MESH
    this->mesh.setMode(OF_PRIMITIVE_POINTS);
    for(int x = 0; x < this->textureRes; x++){
        for(int y = 0; y < this->textureRes; y++){
            this->mesh.addVertex(ofVec3f(x,y));
            this->mesh.addTexCoord(ofVec2f(x, y));
        }
    }

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
    
        this->updateVel.begin();
    
            this->updateVel.setUniformTexture("prevVelData", this->velPingPong.src->getTextureReference(), 0);   // passing the previus velocity information
            this->updateVel.setUniformTexture("posData", this->posPingPong.src->getTextureReference(), 1);  // passing the position information
            this->updateVel.setUniform1i("resolution", (int)this->textureRes);
            this->updateVel.setUniform1f("timestep", (float)this->timeStep);
            this->updateVel.setUniform1f("distanceSeparation", 0.2);
            this->updateVel.setUniform1f("distanceAlignement", 0.6);
            this->updateVel.setUniform1f("distanceCohesion", 1.0);
            this->velPingPong.src->draw(0, 0); // draw the source velocity texture to be updated
        
        this->updateVel.end();
    this->velPingPong.dst->end();
    
    this->velPingPong.swap();
}





void GpuProcess::computeGpuPosition()
{
    
    // With the velocity calculated updates the position
    this->posPingPong.dst->begin(); // fbo
    
        ofClear(0);
    
        this->updatePos.begin(); // shader
        
            this->updatePos.setUniformTexture("prevPosData", this->posPingPong.src->getTextureReference(), 0); // Précendentes positions
            this->updatePos.setUniformTexture("velData", this->velPingPong.src->getTextureReference(), 1);  // Vitesses
            this->updatePos.setUniform1f("timestep", (float)this->timeStep );
            this->updatePos.setUniform1i("resolution", (int)this->textureRes);
            this->posPingPong.src->draw(0, 0); // draw fbo source dans le fbo destination
        
        this->updatePos.end();
    
    this->posPingPong.dst->end();
    
    this->posPingPong.swap();
}







/*/////////////// DRAW /////////////// */



void GpuProcess::draw(Camera* camera)
{
    this->renderTextureScene(camera);
    this->renderFBO.draw(0,0);
    //this->posPingPong.dst->draw(0, 0);
}



void GpuProcess::renderTextureScene(Camera* camera)
{
    this->cpt += 0.4;
    this->model.makeIdentityMatrix();
    this->model.rotate(this->cpt, 1.0, 1.0, 0.0);
    

    this->renderFBO.begin();
    
        ofClear(0,0,0,0);
    
        this->updateRender.begin();
        
            this->updateRender.setUniformTexture("posTex", this->posPingPong.dst->getTextureReference(), 0);
            this->updateRender.setUniform1f("resolution", (float)this->textureRes);
            this->updateRender.setUniform3f("screen", 100.0, 100.0, 100.0); // taille de l'espace 3D des particules
            this->updateRender.setUniformMatrix4f("model", this->model);
            this->updateRender.setUniformMatrix4f("view", camera->getViewMatrix());
            this->updateRender.setUniformMatrix4f("projection", camera->getProjectionMatrix());
    
            ofPushStyle();
            
            this->mesh.draw();
            
            glEnd();
            
        this->updateRender.end();
    
    this->renderFBO.end();
    
    ofPopStyle();
}







