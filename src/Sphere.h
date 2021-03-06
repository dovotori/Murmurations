
#ifndef __MurmurationsGPU_Angle__Sphere__
#define __MurmurationsGPU_Angle__Sphere__

#include "ofMain.h"
#include "Camera.h"


class Sphere
{
public:
    Sphere();
    virtual ~Sphere();
    void setup();
    void draw(Camera *camera);

    inline ofTexture& getTexture(){ return this->fbo.getTextureReference(); };
    inline ofTexture& getTexScreen(){ return this->texScreen; };
    inline int getNbPoint(){ return this->nbPoints; };
    inline int getTextureRes(){ return this->textureRes; };

protected:
private:
    void setupClassic();
    void setupGeodesic(const unsigned int depth);
    void subdivide(ofVec3f &v1, ofVec3f  &v2, ofVec3f  &v3, const unsigned int depth);
    void generateTexture();

    ofVboMesh mesh;
    ofShader shader;
    ofMatrix4x4 model;
    float cpt;
    ofFbo fbo;
    int textureRes, nbPoints;
    ofTexture texScreen;

};

#endif
