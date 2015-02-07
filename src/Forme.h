#ifndef FORME_H
#define FORME_H

#include "ofMain.h"
#include "Camera.h"


/*
 RENDU
 0 FORME A PARTIR D'UN POINT
 1 LIGNES
 2 POINTS
 */

class Forme
{
    public:
        Forme();
        virtual ~Forme();
        void setup(unsigned int nb = 1);
        void draw(Camera *camera, ofTexture& texPos);
    
        inline void setRendu(unsigned int rendu) {
            this->rendu = rendu;
            switch(rendu) {
                case 1:
                    this->mesh.setMode(OF_PRIMITIVE_LINES);
                    break;
                default:
                    this->mesh.setMode(OF_PRIMITIVE_POINTS);
                    break;
            }
        };
        inline void setNoiseInfluence(float value){ this->noiseInfluence = value; };
        inline float getNoiseInfluence(){ return this->noiseInfluence; };
        inline void addRotation(float value){ this->rotation += value; };
    
    protected:
    private:

        ofMatrix4x4 model;
        ofShader *shader;
        ofShader postShader;
        ofVboMesh mesh;
        ofFbo fbo;

        unsigned int textureRes;
        unsigned int rendu;
        float cpt;
        float noiseInfluence;
        float rotation;

};

#endif // FORME_H
