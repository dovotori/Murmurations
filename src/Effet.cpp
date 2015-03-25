#include "Effet.h"

Effet::Effet()
{
    //ctor
    this->cpt = 0.0;
    this->noiseInfluence = 0.0;
    this->noiseScale = 4.0;
    this->passages = 5;
    this->blur = 4.0;
}

Effet::~Effet()
{
    //dtor
    delete [] this->shaders;
}


void Effet::setup()
{
    this->shaders = new ofShader[this->passages];
    this->shaders[0].load("shader/texFbo.vert", "shader/postRender.frag");
    this->shaders[1].load("shader/texFbo.vert", "shader/effect/bright.frag");
    this->shaders[2].load("shader/texFbo.vert", "shader/effect/blurVertical.frag");
    this->shaders[3].load("shader/texFbo.vert", "shader/effect/blurHorizontal.frag");
    this->shaders[4].load("shader/texFbo.vert", "shader/effect/assemblage.frag");

    // CHARGER FBO
    ofFbo::Settings settings;
    settings.width = ofGetWindowWidth();
    settings.height = ofGetWindowHeight();
    settings.internalformat = GL_RGBA32F;
    //settings.numSamples = 0;
    settings.useDepth = true;
    settings.useStencil = true;
    settings.depthStencilAsTexture = true;
    
    this->fboFirst.allocate(ofGetWindowWidth(), ofGetWindowHeight(), GL_RGBA32F);
    this->fboPing.allocate(ofGetWindowWidth(), ofGetWindowHeight(), GL_RGBA32F);
    this->fboPong.allocate(ofGetWindowWidth(), ofGetWindowHeight(), GL_RGBA32F);
    //this->fbo.allocate(settings);
    //this->fbo.begin(); ofClear(0, 0, 0, 255); this->fbo.end();
    //this->fbo2.allocate(settings);
    //this->fbo2.begin(); ofClear(0, 0, 0, 255); this->fbo2.end();

    // ENVOI DES VARIABLES CONSTANTES
    for(unsigned int i = 0; i < this->passages; i++)
    {
        this->shaders[i].begin(); this->shaders[i].setUniform2f("resolution", ofGetWindowWidth(), ofGetWindowHeight()); this->shaders[i].end();
    }
}




void Effet::begin()
{
    this->fboFirst.begin();
    ofClear(0,0,0,0);
}


void Effet::end()
{
    this->fboFirst.end();
}



void Effet::draw()
{
    this->cpt += 0.4;
    
    // noise effect
    //this->fboPong.begin();
      //  ofClear(0,0,0,0);
        this->shaders[0].begin();
            this->shaders[0].setUniform1f("cpt", this->cpt);
            this->shaders[0].setUniform1f("noiseInfluence", this->noiseInfluence); // de 0 à 1
            this->shaders[0].setUniform1f("noiseScale", this->noiseScale);
            this->shaders[0].setUniformTexture("fboTexture", this->fboFirst.getTextureReference(0), 0);
            this->fboFirst.draw(0, 0);
        this->shaders[0].end();
    //this->fboPong.end();
    
    /*
    // 2ND PASS
    this->fboPing.begin();
        ofClear(0,0,0,0);
        this->shaders[1].begin();
            this->shaders[1].setUniformTexture("fboTexture", this->fboPong.getTextureReference(0), 0);
            this->fboPong.draw(0, 0);
        this->shaders[1].end();
    this->fboPing.end();
    
    // 3ND PASS
    this->fboPong.begin();
        ofClear(0,0,0,0);
        this->shaders[2].begin();
            this->shaders[2].setUniform1f("blurness", this->blur);
            this->shaders[2].setUniformTexture("fboTexture", this->fboPing.getTextureReference(0), 0);
            this->fboPing.draw(0, 0);
        this->shaders[2].end();
    this->fboPong.end();
    
    // 4TH PASS
    this->fboPing.begin();
        ofClear(0,0,0,0);
        this->shaders[3].begin();
            this->shaders[3].setUniform1f("blurness", this->blur);
            this->shaders[3].setUniformTexture("fboTexture", this->fboPong.getTextureReference(0), 0);
            this->fboPong.draw(0, 0);
        this->shaders[3].end();
    this->fboPing.end();
    
    // 4TH PASS
    this->shaders[4].begin();
        this->shaders[4].setUniformTexture("fboTexture", this->fboFirst.getTextureReference(0), 0);
        this->shaders[4].setUniformTexture("fboTexture2", this->fboPing.getTextureReference(0), 1);
        this->fboFirst.draw(0, 0);
    this->shaders[4].end();
    */
}
