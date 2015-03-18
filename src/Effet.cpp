#include "Effet.h"

Effet::Effet()
{
    //ctor
    this->cpt = 0.0;
    this->noiseInfluence = 0.0;
    this->noiseScale = 4.0;
}

Effet::~Effet()
{
    //dtor
}


void Effet::setup()
{
    this->shader.load("shader/texFbo.vert", "shader/postRender.frag");
    this->shader2.load("shader/texFbo.vert", "shader/effect/blurHorizontal.frag");

    // CHARGER FBO
    ofFbo::Settings settings;
    settings.width = ofGetWindowWidth();
    settings.height = ofGetWindowHeight();
    settings.internalformat = GL_RGBA32F;
    settings.numSamples = 0;
    settings.useDepth = true;
    settings.useStencil = true;
    settings.depthStencilAsTexture = true;
    this->fbo.allocate(settings);
    //this->fbo.allocate(ofGetWindowWidth(), ofGetWindowHeight(), GL_RGB32F);
    this->fbo.begin(); ofClear(0, 0, 0, 255); this->fbo.end();
    this->fbo2.allocate(settings);
    this->fbo2.begin(); ofClear(0, 0, 0, 255); this->fbo2.end();

    // ENVOI DES VARIABLES CONSTANTES
    this->shader.begin(); this->shader.setUniform2f("resolution", ofGetWindowWidth(), ofGetWindowHeight()); this->shader.end();
    this->shader2.begin(); this->shader2.setUniform2f("resolution", ofGetWindowWidth(), ofGetWindowHeight()); this->shader2.end();
}




void Effet::begin()
{
    this->fbo.begin();
    ofClear(0,0,0,0);
}


void Effet::end()
{
    this->fbo.end();
}



void Effet::draw()
{
    this->cpt += 0.4;

    //this->fbo2.begin();
    //ofClear(0,0,0,0);

    // noise effect
    this->shader.begin();
        this->shader.setUniform1f("cpt", this->cpt);
        this->shader.setUniform1f("noiseInfluence", this->noiseInfluence); // de 0 à 1
        this->shader.setUniform1f("noiseScale", this->noiseScale);
        this->shader.setUniformTexture("fboTexture", this->fbo.getTextureReference(0), 0);
        this->fbo.draw(0, 0);
    this->shader.end();


/*
    this->fbo2.end();


    // 2ND PASS
    this->shader2.begin();
        this->shader2.setUniformTexture("fboTexture", this->fbo.getTextureReference(0), 0);
        this->fbo2.draw(0, 0);
    this->shader2.end();
*/
}
